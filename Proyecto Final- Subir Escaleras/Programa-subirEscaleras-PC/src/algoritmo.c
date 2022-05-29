/*
* @algoritmo.c
*
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


#include <algoritmo.h>
#include <msp430.h>
#include <stdint.h>

int q =0;

char charY;
char charZ;

char concatenado;

void algoritmo(int16_t* ejeX, int16_t* ejeY, int16_t* ejeZ){

    if(q<100){

        charY = ejeY + '0';
        charZ = ejeZ + '0';

        concatenado = strcat(charY,",", charZ);

       // buffer_Y[q] = concatenado;
        //buffer_Z[q] = 'ejeZ';
        q++;

    }


}









