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


#include<msp430.h>
#include<string.h>
//#include<uart.h>
#include <timer_hw.h>
//#include"utils.h"
#include <i2c.h>
#include "imu.h"
#include <algoritmo.h>
//#include<stdint.h>
#define LED1 (0x0001) //Seleccionamos el pin 1.0




/********************************************
 *             VARIABLES I2C                *
 ********************************************/
uint8_t msg[6];
acc_raw_t accel;

int accelX = 0;
int accelY = 0;
int accelZ = 0;


uint8_t resultado = 0;

uint8_t contador = 0;

void main(void)

{
    WDTCTL = WDTPW + WDTHOLD;               // Stop WDT

    /********************************************
     *       INICIALIZAMOS EL MODULO I2C        *
     ********************************************/
    int i = 0;
    for (i=0 ; i<6; i++){
        msg[i] = 0;
    }
    //Se inicializa el i2c
    initI2C();

    //Se inicializa la IMU
    initIMU();



    /********************************************
     *       INICIALIZAR MODULO DE TIMER        *
     ********************************************/

    ////bandera del timer
    static unsigned int banderaTimer =0;
    unsigned int* pt_banderaTimer;
    pt_banderaTimer = &banderaTimer ;

    setFlagTimer(pt_banderaTimer);

    P1DIR = 0;  // Pongo todos los pines como entradas
    P1DIR |= LED1; // Ponemos el pin 1.0 como salida

    //config_timer_crystal(); //inicializamos el timer hardware crystal, se agrega en timer_hw.h

    config_timer_VLO();   //inicializamos el timer hardware  VLO, se agrega en timer_hw.h

    vInitTimerA(); // se inicializa el timer A



    /********************************************
     *       INICIALIZAMOS EL PROGRAMA          *
     ********************************************/

    __enable_interrupt();

    while (1){

        //TICKs  -- se activa de acuerdo a la configuracion de milisegundos configurados en timer_hw.c
         if ((banderaTimer == 1)&&(contador < 150)){   //Ticks completos
             banderaTimer = 0;   // se resetea la bandera en 0
             __disable_interrupt();
             readI2C(ACCEL_ADDRESS, 0x12, msg, 6);
             asignarAccel(msg, &accel);
             __enable_interrupt();
             contador++;
             recopilarDatos(accel.x, accel.y, accel.z);

        }



        //UART Si llega informacion se ejecuta
        if (contador >= 150){
            __disable_interrupt();
            procesarDatos(&resultado);
            __enable_interrupt();

            //Se prende el led de acuerdo al resultado
            if(resultado == 1){
                // PRENDER LED  -- Se esta subiendo escaleras
                P1OUT |= BIT0;
            }
            else{
                // APAGAR LED  -- Se esta bajando escaleras
                P1OUT |= ~BIT0;
            }
            contador = 0;
        }

    }
}
