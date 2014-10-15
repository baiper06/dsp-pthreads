/*
 * stages.h
 *
 *  Created on: 13/10/2014
 *      Author: bairon
 */

#ifndef STAGES_H_
#define STAGES_H_

#include "samples.h"

#define PI 3.14159265

void printArray( double array[] );
void generarMuestra( struct s_samples* sample, int pTimeSapling, int pFrecuency);
void procesarMuestra(struct s_samples* sample, int pDistance);
void plot(struct s_samples* sample, int numeroMuestreo);

#endif /* STAGES_H_ */
