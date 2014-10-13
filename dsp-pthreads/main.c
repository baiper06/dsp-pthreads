#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define PI 3.14159265

/*
 * pTimeSapling  = tiempo de muestreo en ms
 * cntSamples   = cantidad de muestras
 */
void binarySampling( int pTimeSapling, double pSamples[], int pCntSamples ){
    printf( "--- binarySampling ---\n");
    printf( "[ ");
    int i = 0;
    srand( (unsigned)time( NULL ) );
    for( i = 0; i < pCntSamples; i++){
        pSamples[i] = (double)(rand()%2);
        printf( "%.1lf  ", i, pSamples[i]);
    }
    printf( "]\n");
}


/*
 * pTimeSapling  = tiempo de muestreo en ms
 * pCntSamples   = cantidad de muestras
 * pFrecuency    = frecuencia en Hz
 */
double* sinusoidalSampling( int pTimeSapling, int pCntSamples, int pFrecuency){
    printf( "--- sinusoidalSampling ---\n");
    printf( "[ ");
    double  samples[pCntSamples];
    int i = 0;
    srand( (unsigned)time( NULL ) );
    for( i = 0; i < pCntSamples; ++i){
        samples[i] = sin(2*PI*pFrecuency*pTimeSapling/1000);
        printf( "%.1lf  ", i, samples[i]);
    }
    printf( "]\n");
    return samples;
}



void reverse(double pSamples[], double samplesReversed[], int pCntSamples){
    printf( "--- reverse ---\n");
    printf( "[ ");
    int i = 0;
    for( i = 0; i < pCntSamples; i++){
        samplesReversed[i] = pSamples[pCntSamples-(i+1)];
        printf( "%.1lf  ", i, samplesReversed[i]);
    }
    printf( "]\n");
}


void shiftRight(double pSamples[], double samplesShifted[], int pDistance, int pCntSamples){
    printf( "--- shiftRight ---\n");
    printf( "[ ");
    int i = 0;
    for( i = 0; i < pDistance; i++){
        samplesShifted[i] = 0;
        printf( "%.1lf  ", i, samplesShifted[i]);
    }
    for( ; i < pCntSamples; i++){
        samplesShifted[i] = pSamples[i-pDistance];
        printf( "%.1lf  ", i, samplesShifted[i]);
    }
    printf( "]\n");
}


void displayPlot(double* pSamples, double* pProcessedSamples, int pTimeSapling, int pCntSamples)
{
    // TODO
}



int main(void){
    int cntSamples  = 10;
    int timeSapling = 20; //milisec
    double samples[cntSamples];
    double samplesReversed[cntSamples];
    double samplesShifted[cntSamples];

    binarySampling(timeSapling, samples, cntSamples);
    reverse(samples, samplesReversed, cntSamples);
    shiftRight(samplesReversed, samplesShifted, 3, cntSamples);

    return 0;
}
