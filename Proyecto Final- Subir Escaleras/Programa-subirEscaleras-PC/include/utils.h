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



#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

//#include "timer.h"

/**
 * Convierte un entero a ASCII
 * @param int value: valor entero a covertir
 * @param char* str: puntero a char donde guardar el resultado
 */
void itoa(int value, char* str);


/**
 * Convierte un entero de 1 o dos digitos en dos ASCII  - 00 01 02 03 10 11 12
 */
void intTOchar(int value, char* str1, char* str2, char* str3, char* str4, char* str5);



#endif // UTILS_H_INCLUDED
