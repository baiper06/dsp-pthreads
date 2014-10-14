/*
 * stages.cc
 *
 *  Created on: 13/10/2014
 *      Author: bairon
 */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h> /* srand, rand */
#include <iostream>
#include <time.h>
#include "gnuplot.h"
#include "stages.h"


void printArray( double array[] ){
	printf( "[ ");
	int i = 0;
	for( i = 0; i < CNT_SAMPLES; i++){
		printf( "%.2lf  ", array[i]);
	}
	printf( "]\n");
}

/*
 * pTimeSapling  = tiempo de muestreo en ms
 * cntSamples   = cantidad de muestras
 */
void randomSample( int pTimeSapling, struct Samples* pSaplesGroup ){
	int time 	= 0;

	printf( "--- binarySampling ---\n");
	//srand( time( 0 ) );
	int i = 0;
	for( i = 0; i < CNT_SAMPLES; i++){
		//pSaplesGroup->samplesRaw[i] = (double)(rand()%2);
		pSaplesGroup->samplesRaw[i] = (double)(i);
		pSaplesGroup->timesSapling[i] = time;
		time += pTimeSapling;
	}
	pSaplesGroup->processed = false;
}


/*
 * pTimeSapling  = tiempo de muestreo en ms
 * pCntSamples   = cantidad de muestras
 * pFrecuency    = frecuencia en Hz
 */
void sinusoidalSample( int pTimeSapling, struct Samples* pSaplesGroup, int pFrecuency){
	int time 	= 0;

	printf( "--- sinusoidalSampling ---\n");
	int i = 0;
	for( i = 0; i < CNT_SAMPLES; i++){
		pSaplesGroup->samplesRaw[i] = sin(2*PI*pFrecuency*time/1000);
		pSaplesGroup->timesSapling[i] = time;
		time += pTimeSapling;
	}
	pSaplesGroup->processed = false;
}


/*
 * pSaplesGroup = estructura de muestras
 */
void reverse(struct Samples* pSaplesGroup){
	printf( "--- reverse ---\n");
	int i = 0;
	for( i = 0; i < CNT_SAMPLES; i++){
		pSaplesGroup->samplesProcessed[i] = pSaplesGroup->samplesRaw[CNT_SAMPLES-(i+1)];
	}
}

/*
 * pSaplesGroup = estructura de muestras
 * pDistance  	= distancia del desplazamiento
 */
void shiftRight(struct Samples* pSaplesGroup, int pDistance){
	printf( "--- shiftRight ---\n");
	double samplesShifted[CNT_SAMPLES];
	int i = 0;
	for( i = 0; i < pDistance; i++){
		samplesShifted[i] = 0;
	}
	for( ; i < CNT_SAMPLES; i++){
		samplesShifted[i] = pSaplesGroup->samplesProcessed[i-pDistance];
	}
	for( i = 0; i < CNT_SAMPLES; i++){
		pSaplesGroup->samplesProcessed[i] = samplesShifted[i];
	}
}

/*
 * pSaplesGroup  = estructura de muestras
 * pTimeSapling  = tiempo de muestreo en ms
 * pFrecuency    = frecuencia en Hz, si es NULL se ejecuta randomSample()
 */
void sample( struct Samples* pSaplesGroup, int pTimeSapling, int pFrecuency ){
	if( pFrecuency==NULL ){
		randomSample( pTimeSapling, pSaplesGroup);
	}else{
		sinusoidalSample( pTimeSapling, pSaplesGroup, pFrecuency);
	}
	printArray( pSaplesGroup->samplesRaw );
}

/*
 * pSaplesGroup = estructura de muestras
 * pDistance  	= distancia del desplazamiento
 */
void process(struct Samples* pSaplesGroup, int pDistance){
	reverse( pSaplesGroup);
	printArray( pSaplesGroup->samplesProcessed );
	shiftRight( pSaplesGroup, pDistance );
	printArray( pSaplesGroup->samplesProcessed );
	pSaplesGroup->processed = true;
}

/*
 * pSaplesGroup 	= estructura de muestras
 * pNumberSampling 	= numero de la estructura de muestras
 */
void plot(struct Samples* pSaplesGroup, int pNumberSampling){
	printf( "--- plot ---\n");
	mostrarGrafico(pSaplesGroup->timesSapling, pSaplesGroup->samplesRaw, CNT_SAMPLES, "original", pNumberSampling, 0);
	mostrarGrafico(pSaplesGroup->timesSapling, pSaplesGroup->samplesProcessed, CNT_SAMPLES, "procesada", pNumberSampling, 0);
}




