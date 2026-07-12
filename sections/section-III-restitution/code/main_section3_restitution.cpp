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
const int RESTITUTION_COUNT = 5;
const int THETA_BIN_COUNT = 180;
const int KSI_BIN_COUNT = 1000;
const long PRODUCTION_STEP_COUNT = 10000000L;
const long QUICK_TEST_STEP_COUNT = 200000L;

const long double KSI_BIN_WIDTH = 0.001L;
const long double SURFACE_CLEARANCE_LIMIT = 0.05L;
const long double FIXED_ALPHA = 100.0L;
const long double FIXED_D_OVER_LB = 0.5L;
const char *PRODUCTION_OUTPUT_DIR = "section3_restitution_outputs";
const char *QUICK_OUTPUT_DIR = "section3_restitution_quickcheck";

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

long statAll[FLOW_COUNT][RESTITUTION_COUNT][THETA_BIN_COUNT];
long statSurface[FLOW_COUNT][RESTITUTION_COUNT][THETA_BIN_COUNT];
long statCenter[FLOW_COUNT][RESTITUTION_COUNT][THETA_BIN_COUNT];
long statKsiFull[FLOW_COUNT][RESTITUTION_COUNT][KSI_BIN_COUNT];

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
    while(teta<=-pi/2.0L) teta+=pi;
    while(teta>pi/2.0L) teta-=pi;
}

long double ThetaLimit()
{
    long double ratio;

    ratio=Dchannel/LB;
    if(ratio>=1.0L) return pi/2.0L;
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

    if(Sts1>0.5F)
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

    if(Sts>0.5F)
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

void ResetHistograms(int flowIndex,int restitutionIndex)
{
    int i;

    for(i=0;i<THETA_BIN_COUNT;i++)
    {
        statAll[flowIndex][restitutionIndex][i]=0;
        statSurface[flowIndex][restitutionIndex][i]=0;
        statCenter[flowIndex][restitutionIndex][i]=0;
    }

    for(i=0;i<KSI_BIN_COUNT;i++)
    {
        statKsiFull[flowIndex][restitutionIndex][i]=0;
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
            probability=(long double)hist[i]/(long double)total;
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
            probability=(long double)hist[i]/(long double)total;
        }

        fout<<ksiCenter<<"\t"<<probability<<endl;
    }

    fout.close();
}

string MakeFilename(
    const char *quantity,
    const char *region,
    const char *flowName,
    const char *restitutionLabel)
{
    string filename;

    filename=outputDir;
    filename+="\\";
    filename+=quantity;
    filename+="_";
    filename+=region;
    filename+="_";
    filename+=flowName;
    filename+="_alpha_100_DoverLB_0p5_";
    filename+=restitutionLabel;
    filename+=".txt";

    return filename;
}

void MouvBaton(
    long double restitutionRotation,
    long double restitutionTranslation,
    int flowIndex,
    int restitutionIndex)
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

        statAll[flowIndex][restitutionIndex][thetaBin]++;
        statKsiFull[flowIndex][restitutionIndex][ksiBin]++;

        if(IsSurfaceLayer())
        {
            statSurface[flowIndex][restitutionIndex][thetaBin]++;
        }

        if(IsCenterLayer())
        {
            statCenter[flowIndex][restitutionIndex][thetaBin]++;
        }

        N++;
    }
    while(N!=activeStepCount);
}

void WriteOriginThetaBundle(
    const string &filename,
    long hist[FLOW_COUNT][RESTITUTION_COUNT][THETA_BIN_COUNT],
    int flowIndex)
{
    int i;
    int r;
    long total;
    long double thetaCenter;
    long double probability;
    ofstream fout(filename.c_str());

    fout.precision(12);
    fout<<"theta_deg\te_0\te_0p25\te_0p5\te_0p75\te_1"<<endl;

    for(i=0;i<THETA_BIN_COUNT;i++)
    {
        thetaCenter=-89.5L+i;
        fout<<thetaCenter;

        for(r=0;r<RESTITUTION_COUNT;r++)
        {
            total=HistogramTotal(hist[flowIndex][r],THETA_BIN_COUNT);
            probability=0.0L;

            if(total>0)
            {
                probability=(long double)hist[flowIndex][r][i]/(long double)total;
            }

            fout<<"\t"<<probability;
        }

        fout<<endl;
    }

    fout.close();
}

void WriteOriginKsiBundle(const string &filename,int flowIndex)
{
    int i;
    int r;
    long total;
    long double ksiCenter;
    long double probability;
    ofstream fout(filename.c_str());

    fout.precision(12);
    fout<<"xi\te_0\te_0p25\te_0p5\te_0p75\te_1"<<endl;

    for(i=0;i<KSI_BIN_COUNT;i++)
    {
        ksiCenter=(i+0.5L)*KSI_BIN_WIDTH;
        fout<<ksiCenter;

        for(r=0;r<RESTITUTION_COUNT;r++)
        {
            total=HistogramTotal(statKsiFull[flowIndex][r],KSI_BIN_COUNT);
            probability=0.0L;

            if(total>0)
            {
                probability=(long double)statKsiFull[flowIndex][r][i]/(long double)total;
            }

            fout<<"\t"<<probability;
        }

        fout<<endl;
    }

    fout.close();
}

void WriteOriginSummary(
    const string &filename,
    long double restitutionValues[RESTITUTION_COUNT])
{
    int r;
    ofstream fout(filename.c_str());

    fout.precision(12);
    fout<<"e_equal_eprime\tlinear_all\tpoiseuille_all\tlinear_surface\tpoiseuille_surface\tlinear_center\tpoiseuille_center"<<endl;

    for(r=0;r<RESTITUTION_COUNT;r++)
    {
        fout
            <<restitutionValues[r]<<"\t"
            <<ThetaMax(statAll[LINEAR_FLOW][r])<<"\t"
            <<ThetaMax(statAll[POISEUILLE_FLOW][r])<<"\t"
            <<ThetaMax(statSurface[LINEAR_FLOW][r])<<"\t"
            <<ThetaMax(statSurface[POISEUILLE_FLOW][r])<<"\t"
            <<ThetaMax(statCenter[LINEAR_FLOW][r])<<"\t"
            <<ThetaMax(statCenter[POISEUILLE_FLOW][r])
            <<endl;
    }

    fout.close();
}

void WriteOriginSurfaceFraction(
    const string &filename,
    long double restitutionValues[RESTITUTION_COUNT])
{
    int r;
    long samplesAll;
    long samplesSurface;
    long double linearFraction;
    long double poiseuilleFraction;
    ofstream fout(filename.c_str());

    fout.precision(12);
    fout<<"e_equal_eprime\tlinear_surface_fraction\tpoiseuille_surface_fraction"<<endl;

    for(r=0;r<RESTITUTION_COUNT;r++)
    {
        samplesAll=HistogramTotal(statAll[LINEAR_FLOW][r],THETA_BIN_COUNT);
        samplesSurface=HistogramTotal(statSurface[LINEAR_FLOW][r],THETA_BIN_COUNT);
        linearFraction=0.0L;
        if(samplesAll>0) linearFraction=(long double)samplesSurface/(long double)samplesAll;

        samplesAll=HistogramTotal(statAll[POISEUILLE_FLOW][r],THETA_BIN_COUNT);
        samplesSurface=HistogramTotal(statSurface[POISEUILLE_FLOW][r],THETA_BIN_COUNT);
        poiseuilleFraction=0.0L;
        if(samplesAll>0) poiseuilleFraction=(long double)samplesSurface/(long double)samplesAll;

        fout<<restitutionValues[r]<<"\t"<<linearFraction<<"\t"<<poiseuilleFraction<<endl;
    }

    fout.close();
}

int main(int argc,char *argv[])
{
    int flowIndex;
    int restitutionIndex;

    long double restitutionValues[RESTITUTION_COUNT]={
        0.0L,
        0.25L,
        0.5L,
        0.75L,
        1.0L
    };

    const char *restitutionLabels[RESTITUTION_COUNT]={
        "e_0_eprime_0",
        "e_0p25_eprime_0p25",
        "e_0p5_eprime_0p5",
        "e_0p75_eprime_0p75",
        "e_1_eprime_1"
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
    Dchannel=FIXED_D_OVER_LB*LB;
    Alpha=FIXED_ALPHA;
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

    summary.open((outputDir+"\\theta_max_section3_restitution.txt").c_str());
    summary.precision(12);
    summary<<"# flow\talpha\tD_over_LB\te\teprime\ttheta_limit_deg\ttheta_max_all\ttheta_max_surface\ttheta_max_center\tsamples_all\tsamples_surface\tsamples_center\tsurface_fraction\tactive_steps\tsurface_definition"<<endl;

    for(flowIndex=0;flowIndex<FLOW_COUNT;flowIndex++)
    {
        for(restitutionIndex=0;restitutionIndex<RESTITUTION_COUNT;restitutionIndex++)
        {
            ResetRandomSeeds();
            ResetHistograms(flowIndex,restitutionIndex);

            MouvBaton(
                restitutionValues[restitutionIndex],
                restitutionValues[restitutionIndex],
                flowIndex,
                restitutionIndex);

            WriteThetaHistogram(
                MakeFilename("teta","all",flowNames[flowIndex],restitutionLabels[restitutionIndex]),
                statAll[flowIndex][restitutionIndex]);

            WriteThetaHistogram(
                MakeFilename("teta","surface",flowNames[flowIndex],restitutionLabels[restitutionIndex]),
                statSurface[flowIndex][restitutionIndex]);

            WriteThetaHistogram(
                MakeFilename("teta","center",flowNames[flowIndex],restitutionLabels[restitutionIndex]),
                statCenter[flowIndex][restitutionIndex]);

            WriteKsiHistogram(
                MakeFilename("ksi","full",flowNames[flowIndex],restitutionLabels[restitutionIndex]),
                statKsiFull[flowIndex][restitutionIndex]);

            samplesAll=HistogramTotal(statAll[flowIndex][restitutionIndex],THETA_BIN_COUNT);
            samplesSurface=HistogramTotal(statSurface[flowIndex][restitutionIndex],THETA_BIN_COUNT);
            samplesCenter=HistogramTotal(statCenter[flowIndex][restitutionIndex],THETA_BIN_COUNT);
            surfaceFraction=0.0L;
            if(samplesAll>0)
            {
                surfaceFraction=(long double)samplesSurface/(long double)samplesAll;
            }

            summary
                <<flowNames[flowIndex]<<"\t"
                <<FIXED_ALPHA<<"\t"
                <<FIXED_D_OVER_LB<<"\t"
                <<restitutionValues[restitutionIndex]<<"\t"
                <<restitutionValues[restitutionIndex]<<"\t"
                <<ThetaLimit()*180.0L/pi<<"\t"
                <<ThetaMax(statAll[flowIndex][restitutionIndex])<<"\t"
                <<ThetaMax(statSurface[flowIndex][restitutionIndex])<<"\t"
                <<ThetaMax(statCenter[flowIndex][restitutionIndex])<<"\t"
                <<samplesAll<<"\t"
                <<samplesSurface<<"\t"
                <<samplesCenter<<"\t"
                <<surfaceFraction<<"\t"
                <<activeStepCount<<"\t"
                <<"min_wall_clearance_over_D <= "<<SURFACE_CLEARANCE_LIMIT
                <<endl;
        }
    }

    summary.close();

    WriteOriginThetaBundle(
        outputDir+"\\origin_teta_all_linear_alpha_100_DoverLB_0p5_by_restitution.txt",
        statAll,
        LINEAR_FLOW);
    WriteOriginThetaBundle(
        outputDir+"\\origin_teta_all_poiseuille_full_alpha_100_DoverLB_0p5_by_restitution.txt",
        statAll,
        POISEUILLE_FLOW);
    WriteOriginThetaBundle(
        outputDir+"\\origin_teta_surface_linear_alpha_100_DoverLB_0p5_by_restitution.txt",
        statSurface,
        LINEAR_FLOW);
    WriteOriginThetaBundle(
        outputDir+"\\origin_teta_surface_poiseuille_full_alpha_100_DoverLB_0p5_by_restitution.txt",
        statSurface,
        POISEUILLE_FLOW);
    WriteOriginThetaBundle(
        outputDir+"\\origin_teta_center_linear_alpha_100_DoverLB_0p5_by_restitution.txt",
        statCenter,
        LINEAR_FLOW);
    WriteOriginThetaBundle(
        outputDir+"\\origin_teta_center_poiseuille_full_alpha_100_DoverLB_0p5_by_restitution.txt",
        statCenter,
        POISEUILLE_FLOW);

    WriteOriginKsiBundle(
        outputDir+"\\origin_ksi_full_linear_alpha_100_DoverLB_0p5_by_restitution.txt",
        LINEAR_FLOW);
    WriteOriginKsiBundle(
        outputDir+"\\origin_ksi_full_poiseuille_full_alpha_100_DoverLB_0p5_by_restitution.txt",
        POISEUILLE_FLOW);

    WriteOriginSummary(
        outputDir+"\\origin_theta_max_section3_restitution.txt",
        restitutionValues);
    WriteOriginSurfaceFraction(
        outputDir+"\\origin_surface_fraction_section3_restitution.txt",
        restitutionValues);

    return 0;
}
