#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define PI 3.14159265

/*
 * pTimeSapling  = tiempo de muestreo en ms
 * cntSamples   = cantidad de muestras
 */
double* binarySampling( int pTimeSapling, int pCntSamples){
    double  samples[pCntSamples];
    int i = 0;
    srand( (unsigned)time( NULL ) );
    for( i = 0; i < pCntSamples; ++i){
        samples[i] = (double)(rand()%2);
        printf( "samples[%d] = %f\n", i, samples[i]);
    }
    return samples;
}


/*
 * pTimeSapling  = tiempo de muestreo en ms
 * pCntSamples   = cantidad de muestras
 * pFrecuency    = frecuencia en Hz
 */
double* sinusoidalSampling( int pTimeSapling, int pCntSamples, int pFrecuency){
    double  samples[pCntSamples];
    int i = 0;
    srand( (unsigned)time( NULL ) );
    for( i = 0; i < pCntSamples; ++i){
        samples[i] = sin(2*PI*pFrecuency*pTimeSapling/1000);
        printf( "samples[%d] = %f\n", i, samples[i]);
    }
    return samples;
}



double* inversion(double* pSamples)
{
    // TODO
    return pSamples;
}


double* desplazamiento(double* pSamples, int pDistance)
{
    // TODO
    return pSamples;
}


void displayPlot(double* pSamples, double* pProcessedSamples, int pTimeSapling, int pCntSamples)
{
    // TODO
}



int main(void)
{
    binarySampling(20, 10);
    return 0;
}
