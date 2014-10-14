/*
 * stages.h
 *
 *  Created on: 13/10/2014
 *      Author: bairon
 */

#ifndef STAGES_H_
#define STAGES_H_


#define PI 3.14159265
#define CNT_SAMPLES 10

struct Samples {
	double samplesRaw[CNT_SAMPLES];
	double samplesProcessed[CNT_SAMPLES];
	int timesSapling[CNT_SAMPLES];
	bool processed;
};

void printArray( double array[] );

void sample( struct Samples* pSaplesGroup, int pTimeSapling, int pFrecuency);
void process(struct Samples* pSaplesGroup, int pDistance);
void plot(struct Samples* pSaplesGroup, int pNumberSampling);

#endif /* STAGES_H_ */
