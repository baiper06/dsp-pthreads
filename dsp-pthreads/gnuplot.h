/*
 * gnu-plot.h
 *
 *  Created on: Oct 13, 2014
 *      Author: fabian
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef GNUPLOT_H_
#define GNUPLOT_H_

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
 * 		folder_default/(muestreo + numeroMuestreo + tituloGrafico) **NOTA: no trae extension
 *
 * @param guardarEnImagen 1 = indica si la imagen se debe guardar en una imagen. Esto hace que no se muestre el grafico en pantalla
 * 						  0 = se muestra el grafico en pantalla
 *
 * Por ejemplo, para hacer varios graficos para el mismo muestreo, se mantiene el numeroMuestreo y se cambia el tituloGrafico.
 * Si cambia el muestreo , cambie el numero de muestreo
 */
void mostrarGrafico(int *xAxis, double *yAxis, int capacity, char* tituloGrafico, int numeroMuestreo, int guardarEnImagen);


#endif /* GNUPLOT_H_ */
