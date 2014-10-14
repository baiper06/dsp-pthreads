#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include "gnuplot.h"

#define PI 3.14159265

/*
 * pTimeSapling  = tiempo de muestreo en ms
 * cntSamples   = cantidad de muestras
 */
void binarySampling( int pTimeSapling, double pSamples[], int pTimesSapling[], int pCntSamples ){
	printf( "--- binarySampling ---\n");
	printf( "[ ");
	int i = 0;
	srand( (unsigned)time( NULL ) );
	for( i = 0; i < pCntSamples; i++){
		pSamples[i] = (double)(rand()%2);
		pTimesSapling[i] = pTimeSapling*i;
		printf( "%.1lf  ", pSamples[i]);
	}
	printf( "]\n");
}


/*
 * pTimeSapling  = tiempo de muestreo en ms
 * pCntSamples   = cantidad de muestras
 * pFrecuency    = frecuencia en Hz
 */
void sinusoidalSampling( int pTimeSapling,  double pSamples[], int pTimesSapling[], int pCntSamples, int pFrecuency){
	printf( "--- sinusoidalSampling ---\n");
	printf( "[ ");
	int i = 0;
	srand( (unsigned)time( NULL ) );
	for( i = 0; i < pCntSamples; ++i){
		pSamples[i] = sin(2*PI*pFrecuency*pTimeSapling/1000);
		printf( "%.1lf  ", pSamples[i]);
	}
	printf( "]\n");
}



void reverse(double pSamples[], double samplesReversed[], int pCntSamples){
	printf( "--- reverse ---\n");
	printf( "[ ");
	int i = 0;
	for( i = 0; i < pCntSamples; i++){
		samplesReversed[i] = pSamples[pCntSamples-(i+1)];
		printf( "%.1lf  ", samplesReversed[i]);
	}
	printf( "]\n");
}


void shiftRight(double pSamples[], double samplesShifted[], int pDistance, int pCntSamples){
	printf( "--- shiftRight ---\n");
	printf( "[ ");
	int i = 0;
	for( i = 0; i < pDistance; i++){
		samplesShifted[i] = 0;
		printf( "%.1lf  ", samplesShifted[i]);
	}
	for( ; i < pCntSamples; i++){
		samplesShifted[i] = pSamples[i-pDistance];
		printf( "%.1lf  ", samplesShifted[i]);
	}
	printf( "]\n");
}

int main(void){
	int cntSamples  = 10;
	int timeSapling = 20; //milisec

	double 	samples[cntSamples];
	double 	samplesReversed[cntSamples];
	double 	samplesShifted[cntSamples];
	int 	timesSapling[cntSamples];

	binarySampling(timeSapling, samples, timesSapling, cntSamples);
	reverse(samples, samplesReversed, cntSamples);
	shiftRight(samplesReversed, samplesShifted, 3, cntSamples);

//	EJEMPLO GNUPLOT
	int arraySize = 10;
	int xAxis[arraySize];
	int yAxis[arraySize];
	int numero_muestreo = 0;

	int pos = 0;
	for(pos = 0; pos < arraySize; pos++)
	{
		xAxis[pos] = pos;
		yAxis[pos] = pos*3;
	}

	mostrarGrafico(xAxis, yAxis, arraySize, "normal", numero_muestreo, 0);

	return 0;
}
