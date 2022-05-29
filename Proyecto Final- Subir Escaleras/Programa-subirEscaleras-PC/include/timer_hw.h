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


#ifndef INCLUDE_TIMER_HW_H_
#define INCLUDE_TIMER_HW_H_


//Rutina de inicializacion del timer hardware usando el crystal
void config_timer_crystal(void);

//Rutina de inicializacion del timer hardware usando el  VLO
void config_timer_VLO(void);

//Rutina de inicializacion del timer A
void vInitTimerA(void);


void setFlagTimer(unsigned int* flag_timer, int* tiks_new);


#endif /* INCLUDE_TIMER_HW_H_ */
