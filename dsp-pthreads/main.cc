#include <pthread.h>
#include <cstddef>
#include <cstdlib>
#include <stdio.h>

#include "list.h"
#include "samples.h"
#include "stages.h"

#define MUESTRAS_EN_COLA 50

#define TIEMPO 50
#define FRECUENCIA 10
#define DISTANCIA 3

//Cola de estructuras con las muestras
List listaMuestreos;

//Hilos y mutex para acceso a la cola
pthread_t samp_t, proc_t, plot_t;
pthread_mutex_t lock;

//Variable que infica que se esta en ejecucion
int s_corriendo = 1;

void * empezarGeneracionMuestras(void *arg){

	//Crea la lista de muestreos
	listaMuestreos = create_list_with_capacity(MUESTRAS_EN_COLA);

	//Se crean las estructuras en la cola para reutilizar
	int index;
	for ( index = 0; index < MUESTRAS_EN_COLA; index++) {

		printf( "Created and stored the array %i\n", index);

		s_samples* sample = (s_samples*) malloc (sizeof(s_samples));
		sample->numeroMuestreo = index;
		sample->etapa = MUESTREO;
		list_add(&listaMuestreos, sample);
	}

	//Ahora comienza a llenar las structs en estado
	while(s_corriendo)
	{
		pthread_mutex_lock(&lock);
		s_samples* paraMuestrear = list_first_element_in_state(&listaMuestreos, MUESTREO);
		pthread_mutex_unlock(&lock);

		printf("PARA MUESTREO\n");

		if(paraMuestrear != NULL) {
			generarMuestra(paraMuestrear,TIEMPO, FRECUENCIA);
			//Aqui hay que llenar la estructura con el muestreo
			paraMuestrear->etapa = PROCESAMIENTO;
		}
	}

	return NULL;
}

void * empezarProcesamientoDeMuestras(void *arg) {


	//Ahora comienza a llenar las structs en estado
	while(s_corriendo)
	{
		pthread_mutex_lock(&lock);
		s_samples* paraProcesar = list_first_element_in_state(&listaMuestreos, PROCESAMIENTO);
		pthread_mutex_unlock(&lock);

		printf("PARA PROCESAR\n");
		if(paraProcesar != NULL) {
			procesarMuestra(paraProcesar, DISTANCIA);
			//Aqui hay que realizar el procesamiento sobre la muestra
			paraProcesar->etapa = PLOT;
		}
	}

	return NULL;
}

void * empezarDibujarMuestras(void *arg) {

	//Ahora comienza a llenar las structs en estado
	while(s_corriendo)
	{
		pthread_mutex_lock(&lock);
		s_samples* paraProcesar = list_first_element_in_state(&listaMuestreos, PLOT);
		pthread_mutex_unlock(&lock);

		printf("PARA PLOTTEAR\n");
		if(paraProcesar != NULL) {
			plot(paraProcesar,paraProcesar->numeroMuestreo);
			//Aqui hay que dibujar los graficos
			paraProcesar->etapa = MUESTREO;
		}
	}

	return NULL;
}

int main(void){

	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("\n mutex init failed\n");
		return 1;
	}

	//creacion de los hilos
	pthread_create(&samp_t, NULL, empezarGeneracionMuestras, NULL);
	pthread_create(&proc_t, NULL, empezarProcesamientoDeMuestras, NULL);
	pthread_create(&plot_t, NULL, empezarDibujarMuestras, NULL);

	pthread_join(samp_t, NULL);
	pthread_join(proc_t, NULL);
	pthread_join(plot_t, NULL);

	pthread_mutex_destroy(&lock);
	return 0;
}


