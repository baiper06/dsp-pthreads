#include <pthread.h>
#include "stages.h"

int main(void){

	int timeSapling = 50; 	//milisec
	int frecuency 	= 10; 	//Hz (si es 0 se usa randomSample())
	int distance 	= 3;	//distancia del desplazamiento

	struct Samples samples;

	sample( &samples, timeSapling, frecuency );
	process( &samples, distance );
	plot( &samples, 0 );

	return 0;
}


