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
#define D   880e-9

const int FLOW_COUNT = 2;
const int ALPHA_COUNT = 7;
const int THETA_BIN_COUNT = 180;
const int KSI_BIN_COUNT = 500;
const long STEP_COUNT = 10000000L;
const long double SURFACE_KSI_LIMIT = 0.5L;
const long double KSI_BIN_WIDTH = 0.001L;
const char *OUTPUT_DIR = "results_alpha0_full";

enum FlowType
{
    LINEAR_FLOW = 0,
    PARABOLIC_FLOW = 1
};

long double val,ed,eb,DeltaB,Btrans,LB,Alpha,pi;
float deft;
long double zc,teta,teta5,zc5,qsi,teta1,phi,phi5, phi1,phi4,d, tetac,phic,teta4,re,rp, s;

long statBulk[FLOW_COUNT][ALPHA_COUNT][THETA_BIN_COUNT];
long statSurface[FLOW_COUNT][ALPHA_COUNT][THETA_BIN_COUNT];
long statKsiSurface[FLOW_COUNT][ALPHA_COUNT][KSI_BIN_COUNT];

long grain1,grain2,grain3,grain4;

float ran2(long *idum)
{
    int j,i;
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

void BrowRot(long double *teta)
{
    long double Brot1;
    float Sts1;

    Brot1=DeltaB;
    Sts1=ran2(&grain3);

    if(Sts1>0.5)
    {
        Brot1=-Brot1;
    }

    *teta=*teta+Brot1;
}

void BrowTrans(long double *zc)
{
    float Sts;

    Btrans=DeltaB*LB/3;
    Sts=ran2(&grain2);

    if(Sts>0.5)
    {
        Btrans=-Btrans;
    }

    *zc=*zc+Btrans;
}

long double LocalAlpha(int flowType)
{
    long double normalizedZ;

    if(flowType==LINEAR_FLOW)
    {
        return Alpha;
    }

    normalizedZ=zc/D;

    if(normalizedZ<0) normalizedZ=0;
    if(normalizedZ>1) normalizedZ=1;

    return Alpha*(1-normalizedZ);
}

void DynRot(long double *teta,int flowType)
{
    long double Brot;
    long double alphaLocal;

    alphaLocal=LocalAlpha(flowType);

    Brot=alphaLocal*sin(*teta)*sin(*teta)*DeltaB*DeltaB/2;
    *teta=*teta-Brot;
}

int toucheInf(long double *teta, long double *zc)
{
    if (*zc<=(LB/2*fabs(sin(*teta)))) return 1;
    else return 0;
}

int toucheP(long double *teta,long double *zc)
{
    if (*zc<=(LB/2*fabs(sin(*teta))) && (*teta>=0)) return 1;
    else return 0;
}

int toucheN(long double *teta,long double *zc)
{
    if (*zc<=(LB/2*fabs(sin(*teta))) && (*teta<0)) return 1;
    else return 0;
}

int ThetaBin(long double teta)
{
    long num;

    num=(long)floor((teta*180/pi)+90);

    if(num<0) num=0;
    if(num>=THETA_BIN_COUNT) num=THETA_BIN_COUNT-1;

    return (int)num;
}

int KsiBin(long double qsi)
{
    long num;

    num=(long)floor(qsi/KSI_BIN_WIDTH);

    if(num<0) num=0;
    if(num>=KSI_BIN_COUNT) num=KSI_BIN_COUNT-1;

    return (int)num;
}

void ResetHistograms(int flowIndex,int alphaIndex)
{
    int i;

    for(i=0;i<THETA_BIN_COUNT;i++)
    {
        statBulk[flowIndex][alphaIndex][i]=0;
        statSurface[flowIndex][alphaIndex][i]=0;
    }

    for(i=0;i<KSI_BIN_COUNT;i++)
    {
        statKsiSurface[flowIndex][alphaIndex][i]=0;
    }
}

void ResetRandomSeeds()
{
    grain1=-1;
    grain2=-3;
    grain3=-2;
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

void WriteThetaHistogram(const string &filename,long hist[THETA_BIN_COUNT])
{
    int i;
    long total;
    long double thetaCenter;
    long double probability;
    ofstream fout(filename.c_str());

    total=HistogramTotal(hist,THETA_BIN_COUNT);

    for(i=0;i<THETA_BIN_COUNT;i++)
    {
        thetaCenter=-89.5L+i;
        probability=0;

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

    total=HistogramTotal(hist,KSI_BIN_COUNT);

    for(i=0;i<KSI_BIN_COUNT;i++)
    {
        ksiCenter=(i+0.5L)*KSI_BIN_WIDTH;
        probability=0;

        if(total>0)
        {
            probability=(long double)hist[i]/total;
        }

        fout<<ksiCenter<<"\t"<<probability<<endl;
    }

    fout.close();
}

void MouvBaton(long double eb,long double ed,int flowIndex,int alphaIndex)
{
    long num;
    long N;

    N=0;
    zc=LB/4;
    teta=pi/4;

    do
    {
        DynRot(&teta,flowIndex);

        if (zc>D) zc=2*D-zc;
        if(teta<=-pi/2) teta+=pi;
        if(teta>=pi/2)  teta-=pi;

        if(toucheN(&teta,&zc)==1)
        {
            zc=zc+ed*(LB/2-zc);
            teta=-fabs(asin((2*zc/LB)));
        }

        if (zc>D) zc=2*D-zc;
        if(teta<=-pi/2) teta+=pi;
        if(teta>=pi/2)  teta-=pi;

        teta5=teta;
        zc5=zc;

        BrowRot(&teta);

        if (zc>D) zc=2*D-zc;
        if(teta<=-pi/2) teta+=pi;
        if(teta>=pi/2)  teta-=pi;

        teta1=teta;

        if(toucheN(&teta1,&zc)==1)
        {
            teta=-fabsl(asinl(zc*2/LB));
            teta=teta+eb*fabsl(teta-teta5);
        }
        else
        if(toucheP(&teta1,&zc)==1)
        {
            teta=fabsl(asinl(zc*2/LB));
            teta=teta-eb*fabsl(teta-teta5);
        }

        if(teta<-pi/2) teta+=pi;
        if(teta>pi/2) teta-=pi;

        zc5=zc;

        BrowTrans(&zc);

        if (zc>D) zc=2*D-zc;

        if(toucheInf(&teta,&zc)==1)
        {
            zc=(LB/2*fabsl(sin(teta)));
            zc=zc+eb*(zc5-zc);
        }

        if (zc>D) zc=2*D-zc;
        if(teta<=-pi/2) teta+=pi;
        if(teta>=pi/2)  teta-=pi;

        qsi=(long double)(zc/LB);
        num=ThetaBin(teta);

        if(qsi<=SURFACE_KSI_LIMIT)
        {
            statSurface[flowIndex][alphaIndex][num]++;
            statKsiSurface[flowIndex][alphaIndex][KsiBin(qsi)]++;
        }
        else
        {
            statBulk[flowIndex][alphaIndex][num]++;
        }

        N++;
    }
    while (N!=STEP_COUNT);
}

string MakeFilename(const char *quantity,const char *region,const char *flowName,const char *alphaLabel)
{
    string filename;

    filename=OUTPUT_DIR;
    filename+="\\";
    filename+=quantity;
    filename+="_";
    filename+=region;
    filename+="_";
    filename+=flowName;
    filename+="_";
    filename+=alphaLabel;
    filename+=".txt";

    return filename;
}

int main()
{
    int flowIndex;
    int alphaIndex;

    long double alphaValues[ALPHA_COUNT]={0.0,0.5,1.0,2.0,5.0,10.0,100.0};
    const char *alphaLabels[ALPHA_COUNT]={
        "alpha_0",
        "alpha_0p5",
        "alpha_1",
        "alpha_2",
        "alpha_5",
        "alpha_10",
        "alpha_100"
    };
    const char *flowNames[FLOW_COUNT]={"linear","parabolic"};

    LB=880e-9;

    pi=acosl(-1.0);
    DeltaB=0.03;

    _mkdir(OUTPUT_DIR);

    for(flowIndex=0;flowIndex<FLOW_COUNT;flowIndex++)
    {
        for(alphaIndex=0;alphaIndex<ALPHA_COUNT;alphaIndex++)
        {
            Alpha=alphaValues[alphaIndex];

            ResetRandomSeeds();
            ResetHistograms(flowIndex,alphaIndex);

            MouvBaton(0.5,0.5,flowIndex,alphaIndex);

            WriteThetaHistogram(
                MakeFilename("teta","bulk",flowNames[flowIndex],alphaLabels[alphaIndex]),
                statBulk[flowIndex][alphaIndex]);

            WriteThetaHistogram(
                MakeFilename("teta","surface",flowNames[flowIndex],alphaLabels[alphaIndex]),
                statSurface[flowIndex][alphaIndex]);

            WriteKsiHistogram(
                MakeFilename("ksi","surface",flowNames[flowIndex],alphaLabels[alphaIndex]),
                statKsiSurface[flowIndex][alphaIndex]);
        }
    }

    return 0;
}
