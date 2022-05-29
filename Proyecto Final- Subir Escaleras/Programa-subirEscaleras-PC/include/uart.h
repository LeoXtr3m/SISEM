/**********************************************************
* @file main.c
*
* Proyecto final
* Modulo Round Robin OBTENER DATOS POR UART
*
* Este modulo agrupa las funciones de manejo del timer
*
* @version 1.0
* @author   Leoncio Rios, Jesus Calixto
* Version inicial
* @date 20 de Mayo 2022
*
**********************************************************/


#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

//#include<stdint.h>

#define BUFF 21   // tamaño de los buffers
static char buffer_TX[BUFF];   // se les pasa el tamaño a todos por igual
static char buffer_RX[BUFF];
static char buffer_ext[BUFF];

static char buffer_temp[BUFF];

/**
 * @brief funcion que inicializa UART
 */

void uart_init(unsigned int* pt_fin);

/**
 * @brief funcion que para transmitir. Copia en el buffer de transmicion el mensaje a enviar y habilita interrupcion de registro vacio.
 * @param char* mensaje: puntero a el mensaje a transmitir.
 *
 */

void transmitir_TX(char* mensaje);

/**
 * @brief funcion que copia el buffer de recepcion a buffer externo.
 * @param char* buff_ext: puntero al buffer externo.
 */

void copiar_ext(char* buff_ext);


 ////////////////////////////////////////////////////////


/**
 * @brief funcion que añade temperatura y la hora actual al buffer temp
 * @param int* temp: puntero con la temperatura actual.
 * @param int* horas: puntero con la hora actual.
 * @param int* minutos: puntero con la minutos actuales.
 * @param int* segundos: puntero con la segundos actuales.
 *
 */

void add_XYZ(int* accelX,int* accelY,int* accelZ);

/**
 * @brief funcion que copia el buffer de temperatura
 * @param char* buff_temp: puntero al buffer temperatura.
 */

void copiar_temp(char* buff_temp);    //Copia la temperatura al buffer


/**
 * @brief funcion que evalua los parametros que entran por consola a la UART
 * @param int* tiksXX: puntero de salida de los tiks ingresados en WP XX.
 * @param int* tiks_actual: puntero de entrada de los tiks actuales .
 * @param int* temp_actual: puntero de entrada de la temeperatura actual.
 */



#endif /* INCLUDE_UART_H_ */



