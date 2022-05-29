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
#include<uart.h>
#include <timer_hw.h>
#include"utils.h"
#include <i2c.h>
#include "imu.h"
//#include <algoritmo.h>
//#include<stdint.h>
#define LED1 (0x0001) //Seleccionamos el pin 1.0



/********************************************
 *             VARIABLES UART                *
 ********************************************/
int contt=0;
int contUART = 0;
int banderaUART = 0;

/********************************************
 *             VARIABLES I2C                *
 ********************************************/
uint8_t msg[6];
acc_raw_t accel;

int accelX = 0;
int accelY = 0;
int accelZ = 0;


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
    unsigned int tikss =8;
    unsigned int* Stiks;
    Stiks=&tikss;

    ////bandera del timer
    static unsigned int banderaTimer =0;
    unsigned int* pt_banderaTimer;
    pt_banderaTimer = &banderaTimer ;

    setFlagTimer(pt_banderaTimer, tikss);

    P1DIR = 0;  // Pongo todos los pines como entradas
    P1DIR |= LED1; // Ponemos el pin 1.0 como salida

    //config_timer_crystal(); //inicializamos el timer hardware crystal, se agrega en timer_hw.h

    config_timer_VLO();   //inicializamos el timer hardware  VLO, se agrega en timer_hw.h

    vInitTimerA(); // se inicializa el timer A



    /********************************************
     *       INICIALIZAMOS EL MODULO UART       *
     ********************************************/

    //inicializamos la bandera EOL
    static unsigned int EOL=0;
    unsigned int* pt_EOL;
    pt_EOL=&EOL;

    //inicializamos UART
    uart_init(pt_EOL);



    /********************************************
     *       INICIALIZAMOS EL PROGRAMA          *
     ********************************************/

    __enable_interrupt();

    while (1){

        //TICKs  -- se activa de acuerdo a la configuracion de milisegundos configurados en timer_hw.c
         if (banderaTimer == 1){   //Ticks completos
             banderaTimer = 0;   // se resetea la bandera en 0
             __disable_interrupt();
             readI2C(ACCEL_ADDRESS, 0x12, msg, 6);
             asignarAccel(msg, &accel);
             __enable_interrupt();
             contt++;
             banderaUART = 1;
             //algoritmo(accel.x, accel.y, accel.z);
             //accelX = accel.x ;  //aceleracion en x
             //accelY = accel.y ;  //aceleracion en y
             //accelZ = accel.z ;  //aceleracion en z

        }



        //UART Si llega informacion se ejecuta
        if (banderaUART == 1){
            banderaUART = 0;
            add_XYZ(accel.x, accel.y, accel.z);    // Añade el valor de la temperatura al buffer
            copiar_temp(&buffer_temp[0]);
            transmitir_TX(&buffer_temp[0]);             //mandamos los datos
            contUART++;
         }

        //if((banderaTimer == 0)&&(EOL == 0)){
           // LPM3;
        //}
    }
}
