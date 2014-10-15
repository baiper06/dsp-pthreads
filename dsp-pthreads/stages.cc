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
#include <stdint.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "gnuplot.h"
#include "stages.h"


void printArray( double array[] ){
	printf( "[ ");
	int i = 0;
	for( i = 0; i < CANT_MUESTRAS_POR_MUESTREO; i++){
		printf( "%.2lf  ", array[i]);
	}
	printf( "]\n");
}

/*
 * pSaplesGroup  = estructura de muestras
 * pTimeSapling  = tiempo de muestreo en ms
 * pFrecuency    = frecuencia en Hz, si es 0 se ejecuta randomSample()
 */
void generarMuestra( struct s_samples* pSaplesGroup, int pTimeSapling, int pFrecuency ){
	int time 	= 0;
	struct timespec ts;
	ts.tv_sec = pTimeSapling/1000;				// sec = ms/1000
	ts.tv_nsec = (pTimeSapling%1000)*1000000;	//nsec = ms*1000000

	printf( "--- sample ---\n");

	int i;
	for( i = 0; i < CANT_MUESTRAS_POR_MUESTREO; i++){
		if( pFrecuency==0 ){
			//randomSample
			pSaplesGroup->muestrasNormal[i] = (double)(rand()%2);
		}else{
			//sinusoidalSample
			pSaplesGroup->muestrasNormal[i] = sin(2*PI*pFrecuency*time/1000);
		}
		nanosleep(&ts, NULL);
		pSaplesGroup->tiempos[i] = time;
		time += pTimeSapling;
	}
	//pSaplesGroup->processed = false;
	//printArray( pSaplesGroup->samplesRaw );
}


/*
 * pSaplesGroup = estructura de muestras
 */
void reverse(struct s_samples* pSaplesGroup){
	printf( "--- reverse ---\n");
	int i = 0;
	for( i = 0; i < CANT_MUESTRAS_POR_MUESTREO; i++){
		pSaplesGroup->muestrasProcesadas[i] = pSaplesGroup->muestrasNormal[CANT_MUESTRAS_POR_MUESTREO-(i+1)];
	}
}

/*
 * pSaplesGroup = estructura de muestras
 * pDistance  	= distancia del desplazamiento
 */
void shiftRight(struct s_samples* pSaplesGroup, int pDistance){
	printf( "--- shiftRight ---\n");
	double samplesShifted[CANT_MUESTRAS_POR_MUESTREO];
	int i = 0;
	for( i = 0; i < pDistance; i++){
		samplesShifted[i] = 0;
	}
	for( ; i < CANT_MUESTRAS_POR_MUESTREO; i++){
		samplesShifted[i] = pSaplesGroup->muestrasProcesadas[i-pDistance];
	}
	for( i = 0; i < CANT_MUESTRAS_POR_MUESTREO; i++){
		pSaplesGroup->muestrasProcesadas[i] = samplesShifted[i];
	}
}

/*
 * pSaplesGroup = estructura de muestras
 * pDistance  	= distancia del desplazamiento
 */
void procesarMuestra(struct s_samples* pSaplesGroup, int pDistance){
	reverse( pSaplesGroup);
	//printArray( pSaplesGroup->samplesProcessed );
	shiftRight( pSaplesGroup, pDistance );
	//printArray( pSaplesGroup->samplesProcessed );
	//pSaplesGroup->processed = true;
}

/*
 * pSaplesGroup 	= estructura de muestras
 * pNumberSampling 	= numero de la estructura de muestras
 */
void plot(struct s_samples* pSaplesGroup, int pNumberSampling){
	printf( "--- plot ---\n");
	mostrarGrafico(pSaplesGroup->tiempos, pSaplesGroup->muestrasNormal, CANT_MUESTRAS_POR_MUESTREO, "original", pNumberSampling, 0);
	mostrarGrafico(pSaplesGroup->tiempos, pSaplesGroup->muestrasProcesadas, CANT_MUESTRAS_POR_MUESTREO, "procesada", pNumberSampling, 0);
}




