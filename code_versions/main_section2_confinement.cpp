#include <iostream>
using namespace std;
#include <fstream>
#include <cmath>
#include <string>
#include <direct.h>

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

const int FLOW_COUNT = 2;
const int ALPHA_COUNT = 3;
const int DIAMETER_COUNT = 4;
const int THETA_BIN_COUNT = 180;
const int KSI_BIN_COUNT = 1000;
const long PRODUCTION_STEP_COUNT = 10000000L;
const long QUICK_TEST_STEP_COUNT = 200000L;

const long double KSI_BIN_WIDTH = 0.001L;
const long double SURFACE_CLEARANCE_LIMIT = 0.05L;
const char *PRODUCTION_OUTPUT_DIR = "section2_confinement_surface_clearance_outputs";
const char *QUICK_OUTPUT_DIR = "section2_confinement_surface_clearance_quickcheck";

enum FlowType
{
    LINEAR_FLOW = 0,
    POISEUILLE_FLOW = 1
};

long double DeltaB, Btrans, LB, Dchannel, Alpha, pi;
long double zc, teta, qsi;
long activeStepCount;
string outputDir;
long grain1, grain2, grain3;

long statAll[FLOW_COUNT][ALPHA_COUNT][DIAMETER_COUNT][THETA_BIN_COUNT];
long statSurface[FLOW_COUNT][ALPHA_COUNT][DIAMETER_COUNT][THETA_BIN_COUNT];
long statCenter[FLOW_COUNT][ALPHA_COUNT][DIAMETER_COUNT][THETA_BIN_COUNT];
long statKsiFull[FLOW_COUNT][ALPHA_COUNT][DIAMETER_COUNT][KSI_BIN_COUNT];

float ran2(long *idum)
{
    int j;
    long k;
    static long idum2=123456789;
    static long iy=0;
    static long iv[NTAB];
    float temp;

    if (*idum <= 0)
    {
        if(-(*idum)<1) *idum=1;
        else *idum=-(*idum);

        idum2=(*idum);
        for(j=NTAB+7;j>=0;j--)
        {
            k=(*idum)/IQ1;
            *idum=IA1*((*idum-k)*IQ1)-IR1*k;
            if(*idum<0) *idum+=IM1;
            if(j<NTAB) iv[j] = *idum;
        }
        iy=iv[0];
    }

    k=(*idum)/IQ1;
    *idum=IA1*((*idum-k)*IQ1)-IR1*k;
    if(*idum<0) *idum+=IM1;

    k=idum2/IQ2;
    idum2=IA2*((idum2-k)*IQ2)-IR2*k;
    if(idum2<0) idum2+=IM2;

    j=iy/NDIV;
    iy=iv[j]-idum2;
    iv[j]=*idum;

    if(iy<1) iy+=IMM1;

    if((temp=AM*iy) > RNMX) return RNMX;
    else return temp;
}

void ResetRandomSeeds()
{
    grain1=-1;
    grain2=-3;
    grain3=-2;
}

void NormalizeTheta()
{
    while(teta<=-pi/2) teta+=pi;
    while(teta>pi/2) teta-=pi;
}

long double ThetaLimit()
{
    long double ratio;

    ratio=Dchannel/LB;
    if(ratio>=1.0L) return pi/2;
    if(ratio<=0.0L) return 0.0L;

    return asinl(ratio);
}

long double HalfVerticalExtent()
{
    return 0.5L*LB*fabsl(sinl(teta));
}

void ApplyWallConstraints(long double restitution)
{
    long double limit;
    long double excess;
    long double sign;
    long double h;
    long double minZ;
    long double maxZ;

    NormalizeTheta();

    limit=ThetaLimit();
    if(fabsl(teta)>limit)
    {
        sign=(teta>=0.0L) ? 1.0L : -1.0L;
        excess=fabsl(teta)-limit;
        teta=sign*(limit-restitution*excess);

        if(fabsl(teta)>limit)
        {
            teta=sign*limit;
        }
    }

    h=HalfVerticalExtent();
    if(h>Dchannel/2.0L)
    {
        sign=(teta>=0.0L) ? 1.0L : -1.0L;
        teta=sign*limit;
        h=Dchannel/2.0L;
    }

    minZ=h;
    maxZ=Dchannel-h;

    if(zc<minZ)
    {
        zc=minZ+restitution*(minZ-zc);
        if(zc>maxZ) zc=minZ;
    }

    if(zc>maxZ)
    {
        zc=maxZ-restitution*(zc-maxZ);
        if(zc<minZ) zc=maxZ;
    }

    if(zc<0.0L) zc=0.0L;
    if(zc>Dchannel) zc=Dchannel;
}

void BrowRot()
{
    long double Brot1;
    float Sts1;

    Brot1=DeltaB;
    Sts1=ran2(&grain3);

    if(Sts1>0.5)
    {
        Brot1=-Brot1;
    }

    teta=teta+Brot1;
}

void BrowTrans()
{
    float Sts;

    Btrans=DeltaB*LB/3.0L;
    Sts=ran2(&grain2);

    if(Sts>0.5)
    {
        Btrans=-Btrans;
    }

    zc=zc+Btrans;
}

long double LocalAlpha(int flowType)
{
    long double normalizedZ;

    if(flowType==LINEAR_FLOW)
    {
        return Alpha;
    }

    normalizedZ=zc/Dchannel;

    if(normalizedZ<0.0L) normalizedZ=0.0L;
    if(normalizedZ>1.0L) normalizedZ=1.0L;

    return Alpha*(1.0L-2.0L*normalizedZ);
}

void DynRot(int flowType)
{
    long double Brot;
    long double alphaLocal;

    alphaLocal=LocalAlpha(flowType);
    Brot=alphaLocal*sinl(teta)*sinl(teta)*DeltaB*DeltaB/2.0L;
    teta=teta-Brot;
}

int ThetaBin()
{
    long num;

    num=(long)floorl((teta*180.0L/pi)+90.0L);

    if(num<0) num=0;
    if(num>=THETA_BIN_COUNT) num=THETA_BIN_COUNT-1;

    return (int)num;
}

int KsiBin()
{
    long num;

    num=(long)floorl(qsi/KSI_BIN_WIDTH);

    if(num<0) num=0;
    if(num>=KSI_BIN_COUNT) num=KSI_BIN_COUNT-1;

    return (int)num;
}

long double WallClearance()
{
    long double h;
    long double lowerGap;
    long double upperGap;

    h=HalfVerticalExtent();
    lowerGap=zc-h;
    upperGap=Dchannel-zc-h;

    if(lowerGap<0.0L) lowerGap=0.0L;
    if(upperGap<0.0L) upperGap=0.0L;

    if(lowerGap<upperGap) return lowerGap;
    return upperGap;
}

long double ReducedWallClearance()
{
    if(Dchannel<=0.0L) return 0.0L;
    return WallClearance()/Dchannel;
}

int IsSurfaceLayer()
{
    if(ReducedWallClearance()<=SURFACE_CLEARANCE_LIMIT) return 1;
    return 0;
}

int IsCenterLayer()
{
    if(ReducedWallClearance()>SURFACE_CLEARANCE_LIMIT) return 1;
    return 0;
}

void ResetHistograms(int flowIndex,int alphaIndex,int diameterIndex)
{
    int i;

    for(i=0;i<THETA_BIN_COUNT;i++)
    {
        statAll[flowIndex][alphaIndex][diameterIndex][i]=0;
        statSurface[flowIndex][alphaIndex][diameterIndex][i]=0;
        statCenter[flowIndex][alphaIndex][diameterIndex][i]=0;
    }

    for(i=0;i<KSI_BIN_COUNT;i++)
    {
        statKsiFull[flowIndex][alphaIndex][diameterIndex][i]=0;
    }
}

long HistogramTotal(long hist[],int count)
{
    int i;
    long total;

    total=0;

    for(i=0;i<count;i++)
    {
        total+=hist[i];
    }

    return total;
}

long double ThetaMax(long hist[THETA_BIN_COUNT])
{
    int i;
    int maxIndex;

    if(HistogramTotal(hist,THETA_BIN_COUNT)==0) return 0.0L;

    maxIndex=0;
    for(i=1;i<THETA_BIN_COUNT;i++)
    {
        if(hist[i]>hist[maxIndex])
        {
            maxIndex=i;
        }
    }

    return -89.5L+maxIndex;
}

void WriteThetaHistogram(const string &filename,long hist[THETA_BIN_COUNT])
{
    int i;
    long total;
    long double thetaCenter;
    long double probability;
    ofstream fout(filename.c_str());

    fout.precision(12);
    total=HistogramTotal(hist,THETA_BIN_COUNT);

    for(i=0;i<THETA_BIN_COUNT;i++)
    {
        thetaCenter=-89.5L+i;
        probability=0.0L;

        if(total>0)
        {
            probability=(long double)hist[i]/total;
        }

        fout<<thetaCenter<<"\t"<<probability<<endl;
    }

    fout.close();
}

void WriteKsiHistogram(const string &filename,long hist[KSI_BIN_COUNT])
{
    int i;
    long total;
    long double ksiCenter;
    long double probability;
    ofstream fout(filename.c_str());

    fout.precision(12);
    total=HistogramTotal(hist,KSI_BIN_COUNT);

    for(i=0;i<KSI_BIN_COUNT;i++)
    {
        ksiCenter=(i+0.5L)*KSI_BIN_WIDTH;
        probability=0.0L;

        if(total>0)
        {
            probability=(long double)hist[i]/total;
        }

        fout<<ksiCenter<<"\t"<<probability<<endl;
    }

    fout.close();
}

string MakeFilename(
    const char *quantity,
    const char *region,
    const char *flowName,
    const char *alphaLabel,
    const char *diameterLabel)
{
    string filename;

    filename=outputDir;
    filename+="\\";
    filename+=quantity;
    filename+="_";
    filename+=region;
    filename+="_";
    filename+=flowName;
    filename+="_";
    filename+=alphaLabel;
    filename+="_";
    filename+=diameterLabel;
    filename+=".txt";

    return filename;
}

void MouvBaton(
    long double restitutionRotation,
    long double restitutionTranslation,
    int flowIndex,
    int alphaIndex,
    int diameterIndex)
{
    long N;
    int thetaBin;
    int ksiBin;

    N=0;
    zc=Dchannel/2.0L;
    teta=0.0L;
    ApplyWallConstraints(restitutionTranslation);

    do
    {
        DynRot(flowIndex);
        ApplyWallConstraints(restitutionRotation);

        BrowRot();
        ApplyWallConstraints(restitutionRotation);

        BrowTrans();
        ApplyWallConstraints(restitutionTranslation);

        qsi=zc/Dchannel;
        thetaBin=ThetaBin();
        ksiBin=KsiBin();

        statAll[flowIndex][alphaIndex][diameterIndex][thetaBin]++;
        statKsiFull[flowIndex][alphaIndex][diameterIndex][ksiBin]++;

        if(IsSurfaceLayer())
        {
            statSurface[flowIndex][alphaIndex][diameterIndex][thetaBin]++;
        }

        if(IsCenterLayer())
        {
            statCenter[flowIndex][alphaIndex][diameterIndex][thetaBin]++;
        }

        N++;
    }
    while(N!=activeStepCount);
}

int main(int argc,char *argv[])
{
    int flowIndex;
    int alphaIndex;
    int diameterIndex;

    long double alphaValues[ALPHA_COUNT]={0.0L,5.0L,100.0L};
    const char *alphaLabels[ALPHA_COUNT]={
        "alpha_0",
        "alpha_5",
        "alpha_100"
    };

    long double diameterRatios[DIAMETER_COUNT]={1.0L,0.75L,0.5L,0.25L};
    const char *diameterLabels[DIAMETER_COUNT]={
        "DoverLB_1",
        "DoverLB_0p75",
        "DoverLB_0p5",
        "DoverLB_0p25"
    };

    const char *flowNames[FLOW_COUNT]={
        "linear",
        "poiseuille_full"
    };

    ofstream summary;
    long samplesAll;
    long samplesSurface;
    long samplesCenter;
    long double surfaceFraction;

    LB=880e-9L;
    pi=acosl(-1.0L);
    DeltaB=0.03L;

    activeStepCount=PRODUCTION_STEP_COUNT;
    outputDir=PRODUCTION_OUTPUT_DIR;

    if(argc>1)
    {
        if(string(argv[1])=="quick")
        {
            activeStepCount=QUICK_TEST_STEP_COUNT;
            outputDir=QUICK_OUTPUT_DIR;
        }
    }

    _mkdir(outputDir.c_str());

    summary.open((outputDir+"\\theta_max_section2.txt").c_str());
    summary.precision(12);
    summary<<"# flow\talpha\tD_over_LB\ttheta_limit_deg\ttheta_max_all\ttheta_max_surface\ttheta_max_center\tsamples_all\tsamples_surface\tsamples_center\tsurface_fraction\tactive_steps\tsurface_definition"<<endl;

    for(flowIndex=0;flowIndex<FLOW_COUNT;flowIndex++)
    {
        for(alphaIndex=0;alphaIndex<ALPHA_COUNT;alphaIndex++)
        {
            Alpha=alphaValues[alphaIndex];

            for(diameterIndex=0;diameterIndex<DIAMETER_COUNT;diameterIndex++)
            {
                Dchannel=diameterRatios[diameterIndex]*LB;

                ResetRandomSeeds();
                ResetHistograms(flowIndex,alphaIndex,diameterIndex);

                MouvBaton(0.5L,0.5L,flowIndex,alphaIndex,diameterIndex);

                WriteThetaHistogram(
                    MakeFilename("teta","all",flowNames[flowIndex],alphaLabels[alphaIndex],diameterLabels[diameterIndex]),
                    statAll[flowIndex][alphaIndex][diameterIndex]);

                WriteThetaHistogram(
                    MakeFilename("teta","surface",flowNames[flowIndex],alphaLabels[alphaIndex],diameterLabels[diameterIndex]),
                    statSurface[flowIndex][alphaIndex][diameterIndex]);

                WriteThetaHistogram(
                    MakeFilename("teta","center",flowNames[flowIndex],alphaLabels[alphaIndex],diameterLabels[diameterIndex]),
                    statCenter[flowIndex][alphaIndex][diameterIndex]);

                WriteKsiHistogram(
                    MakeFilename("ksi","full",flowNames[flowIndex],alphaLabels[alphaIndex],diameterLabels[diameterIndex]),
                    statKsiFull[flowIndex][alphaIndex][diameterIndex]);

                samplesAll=HistogramTotal(statAll[flowIndex][alphaIndex][diameterIndex],THETA_BIN_COUNT);
                samplesSurface=HistogramTotal(statSurface[flowIndex][alphaIndex][diameterIndex],THETA_BIN_COUNT);
                samplesCenter=HistogramTotal(statCenter[flowIndex][alphaIndex][diameterIndex],THETA_BIN_COUNT);
                surfaceFraction=0.0L;
                if(samplesAll>0)
                {
                    surfaceFraction=(long double)samplesSurface/(long double)samplesAll;
                }

                summary
                    <<flowNames[flowIndex]<<"\t"
                    <<alphaValues[alphaIndex]<<"\t"
                    <<diameterRatios[diameterIndex]<<"\t"
                    <<ThetaLimit()*180.0L/pi<<"\t"
                    <<ThetaMax(statAll[flowIndex][alphaIndex][diameterIndex])<<"\t"
                    <<ThetaMax(statSurface[flowIndex][alphaIndex][diameterIndex])<<"\t"
                    <<ThetaMax(statCenter[flowIndex][alphaIndex][diameterIndex])<<"\t"
                    <<samplesAll<<"\t"
                    <<samplesSurface<<"\t"
                    <<samplesCenter<<"\t"
                    <<surfaceFraction<<"\t"
                    <<activeStepCount<<"\t"
                    <<"min_wall_clearance_over_D <= "<<SURFACE_CLEARANCE_LIMIT
                    <<endl;
            }
        }
    }

    summary.close();

    return 0;
}
