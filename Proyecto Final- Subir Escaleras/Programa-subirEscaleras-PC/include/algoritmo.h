/*
 * algoritmo.h
 *
 *  Created on: May 28, 2022
 *      Author: LeoXtr3m
 */

#ifndef INCLUDE_ALGORITMO_H_
#define INCLUDE_ALGORITMO_H_

#include <msp430.h>
#include <stdint.h>
#define BUFFER 255  // tamaño de los buffers


//static int16_t buffer_X[BUFFER];
static char buffer_Y[BUFFER];
//static char buffer_Z[BUFFER];


void algoritmo(int16_t* ejeX, int16_t* ejeY, int16_t* ejeZ);
/**
 * @brief funcion que procesa los datos del acelerometro
 * @param int* temp: puntero con la temperatura actual.
 * @param int* horas: puntero con la hora actual.
 * @param int* minutos: puntero con la minutos actuales.
 * @param int* segundos: puntero con la segundos actuales.
 *
 */







#endif /* INCLUDE_ALGORITMO_H_ */
