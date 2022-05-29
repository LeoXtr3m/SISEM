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

#include <i2c.h>
#include <msp430.h>
#include <stdint.h>
#include "imu.h"


void initIMU(){

    while ( UCB0STAT & UCBBUSY );      // espero a que el bus este libre

    uint8_t msg = 0xB6; // Soft reset
    sendI2C(ACCEL_ADDRESS, CMD_REG, &msg, 1);
    __delay_cycles(5000);

    msg = NORMAL_MODE_VALUE; // Pasar acelerometro a normal mode (low-power es 0x12)
    sendI2C(ACCEL_ADDRESS, CMD_REG, &msg, 1);
    __delay_cycles(5000);


    msg = ACC_CONF_VALUE; // Setear frecuencia
    sendI2C(ACCEL_ADDRESS, ACC_CONF_REG, &msg, 1);
    __delay_cycles(5000);


    msg = ACC_RANGE_VALUE; // Setear rango
    sendI2C(ACCEL_ADDRESS, ACC_RANGE_REG, &msg, 1);
    __delay_cycles(5000);

}
