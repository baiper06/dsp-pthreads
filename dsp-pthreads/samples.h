/*
 * samples.h
 *
 *  Created on: 14/10/2014
 *      Author: luis
 */

#ifndef SAMPLES_H_
#define SAMPLES_H_

#define CANT_MUESTRAS_POR_MUESTREO 10

enum S_SAMPLE_ETAPA { MUESTREO, PROCESAMIENTO, PLOT};

struct s_samples {

	double muestrasNormal[CANT_MUESTRAS_POR_MUESTREO];
	double muestrasProcesadas[CANT_MUESTRAS_POR_MUESTREO];
	int tiempos[CANT_MUESTRAS_POR_MUESTREO];
	int numeroMuestreo;
	S_SAMPLE_ETAPA etapa;
};

#endif /* SAMPLES_H_ */
