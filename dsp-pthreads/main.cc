#include <pthread.h>
#include "stages.h"

int main(void){

	int timeSapling = 20; //milisec
	int frecuency 	= 10; //Hz (NULL para usar randomSample()
	int distance 	= 3;

	struct Samples samples;

	sample( &samples, timeSapling, frecuency );
	process( &samples, distance );
	plot( &samples, 0 );

	return 0;
}
