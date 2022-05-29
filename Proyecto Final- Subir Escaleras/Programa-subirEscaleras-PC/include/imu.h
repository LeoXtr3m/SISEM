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


#ifndef INCLUDE_IMU_H_
#define INCLUDE_IMU_H_

#include <msp430.h>
#include <stdint.h>
#include "i2c.h"

/**
 * @brief Dirección del registro de comandos del BMI160
 */
#define CMD_REG 0x7E

/**
 * @brief Dirección del registro de configuración del BMI160
 */
#define ACC_CONF_REG 0x40

/**
 * @brief Dirección del registro de seteo de rangos del BMI160
 */
#define ACC_RANGE_REG 0x41

/**
 * @brief Dirección del registro de salida del acelerómetro del BMI160
 */
#define ACC_DATA_REG 0x12

/**
 * @brief Dirección del registro de estado del BMI160
 */
#define PMU_STATUS_REG 0x03

/**
 * @brief Valor para definir modo normal de funcionamiento del acelerómetro en el BMI160
 */
#define NORMAL_MODE_VALUE 0x11

/**
 * @brief Valor para configurar adquisicion a 50Hz en el acelerómetro del BMI160
 */
#define ACC_CONF_VALUE 0x27     //(00100111b)

/**
 * @brief Valor para definir un rango de 8g del acelerómetro en el BMI160
 */
#define ACC_RANGE_VALUE 0x08    //(00001000b)

/**
 * @brief Dirección i2c esclavo del BMI160
 */
#define ACCEL_ADDRESS 0x69

/**
 * @brief Configura el sensor BMI160 según los parámetros definidos en el módulo y comienza la adquisición de datos.
 *
 */
void initIMU();

#endif /* INCLUDE_IMU_H_ */
