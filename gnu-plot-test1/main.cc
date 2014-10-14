/*
 * main.c
 *
 *  Created on: Oct 13, 2014
 *      Author: fabian
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "gnuplot-iostream.h"

/** Estructura necesaria para revisar la existencia de un folder - mkdir */
struct stat st = {0};

/**
 *
 * Esta funcion guarda los datos en un archivo para ser utilizado por GNUPlot
 *
 * @param xAxis valores para el eje X
 * @param yAxis valores para el eje Y
 * @param capacity cantidad de elementos que contiene xAxis y yAxis
 * @param tituloGrafico titulo para el grafico. se incluye en el nombre del archivo
 * @param numeroMuestreo numero de este muestreo. se incluye en el nombre del archivo
 * @param filePath valor de salida. contiene la ruta + nombre con que se guardo el archivo relativo a la ubicacion del proyecto.
 * @return el largo de filePath o -1 en caso de error
 */
int guardarArchivoDat(int *xAxis, int *yAxis, int capacity,  char* tituloGrafico, int numeroMuestreo, char* filePath)
{
	/** Revisa se existe el folder de los muestreos, si no, se crea */
	char* folder = "muestreos";
	if (stat(folder, &st) == -1) {
		mkdir(folder, 0700);
	}

	/** Primero crea el nombre del grafico correspondiente */
	int charSize;
	charSize = sprintf (filePath, "%s/muestreo%d%s.dat",folder, numeroMuestreo, tituloGrafico);

	/** Crea el archivo a utilizar por gnuplot con el formato x \t y */
	FILE *f = fopen(filePath, "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		return -1;
	}

	int pos = 0;
	for(pos = 0; pos < capacity; pos++)
	{
		fprintf(f, "%d\t%d\n", xAxis[pos], yAxis[pos]);
	}

	fclose(f);
	return charSize;
}

/**
 *
 * Muestra un grafico utilizando GNUPlot. Para esto primero guarda un archivo .dat con los datos suministrados.
 * El nombre del archivo se forma de la siguiente manera:
 *
 * @param xAxis valores para el eje X
 * @param yAxis valores para el eje Y
 * @param capacity cantidad de elementos que contiene xAxis y yAxis
 * @param tituloGrafico titulo para el grafico. se incluye en el nombre del archivo.
 * @param numeroMuestreo numero de este muestreo. se incluye en el nombre del archivo
 * @param filePath valor de salida. De la forma:
 *
 * 		folder_default/(muestreo + numeroMuestreo + tituloGrafico).dat
 *
 * Por ejemplo, para hacer varios graficos para el mismo muestreo, se mantiene el numeroMuestreo y se cambia el tituloGrafico.
 * Si cambia el muestreo , cambie el numero de muestreo
 */
void mostrarGrafico(int *xAxis, int *yAxis, int capacity, char* tituloGrafico, int numeroMuestreo)
{
	/** Nombre del archivo con los datos creado */
	char filePath [50];
	int filePathSize;

	/** Crea el archivo con la informacion para gnuplot */
	filePathSize = guardarArchivoDat(xAxis, yAxis, capacity, tituloGrafico, numeroMuestreo, filePath);

	/** Hace el plot en gnuplot */
	Gnuplot gp;

	/** Titulos de la ventana */
	gp << "set term wxt title \"" << filePath << "\"" << std::endl;

	/** Titulos del grafico y de los ejes */
	gp << "set title \"" << filePath << "\"" << std::endl;
	gp << "set xlabel \"titulo eje x\" " << std::endl;
	gp << "set ylabel \"titulo eje y\" " << std::endl;

	/** Pinta el grafico */
	gp << "plot \"" << filePath << "\" using 1:2 with points" << std::endl;
	printf ("[%s] is a string %d chars long\n",filePath, filePathSize);
}

int main() {

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
	mostrarGrafico(xAxis, yAxis, arraySize, "Normal", numero_muestreo);
	return 0;
}
