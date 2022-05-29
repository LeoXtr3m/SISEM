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


#ifndef INCLUDE_I2C_H_
#define INCLUDE_I2C_H_

#include <msp430.h>
#include <stdint.h>



/**
 * @brief Buffer de recepción i2c
 */
#define I2C_RX_BUFFER_SIZE 6


/**
 * @brief Buffer de transmisión i2c
 */
#define I2C_TX_BUFFER_SIZE 6


/**
 * @brief Estructura que representa datos crudos de aceleración en x,y,z
 */
struct acc_raw
{
    /*! X-axis sensor data */
    int16_t x;

    /*! Y-axis sensor data */
    int16_t y;

    /*! Z-axis sensor data */
    int16_t z;

};

/**
 * @brief Tipo que envuelve a la estructura acc_raw
 */
typedef struct acc_raw acc_raw_t;


/**
 * @brief Configura el módulo USCI_B0 para funcionar en modo I2C.
 * @details Inicializa el módulo como "I2C master" con direcciones de
 * 7 bits. Divide la fuente SMCLK entre 12 para generar la señal de reloj.
 * SCL = ~100kHz @ 1.1MHz
 */
void initI2C();

/**
 * @brief Recibe la dirección de la bandera a utilizar.
 * @param uint8_t* flag: bandera a encender cuando haya una cadena de
 * caracteres lista en el buffer de recepción.
 *
 */
void setI2Cflag(uint8_t* flag);

/**
 * @brief Envía un arreglo de bytes a la dirección del registro del esclavo
 * objetivo.
 * @param uint8_t slave_address: dirección del esclavo.
 * @param uint8_t reg: dirección del registro a escribir.
 * @param uint8_t* msg: dirección del mensaje a enviar.
 * @param uint8_t msg_size: cantidad de bytes a enviar.
 */
void sendI2C(uint8_t slave_address, uint8_t reg, uint8_t *msg, uint8_t msg_size);

/**
 * @brief Recibe un arreglo de bytes desde el registro del esclavo
 * objetivo e indica el fin de la recepción a travÃ©s de una bandera.
 * @param uint8_t slave_address: dirección del esclavo.
 * @param uint8_t reg: dirección del registro a leer.
 * @param uint8_t* msg: dirección donde guardar el mensaje recibido.
 * @param uint8_t msg_size: cantidad de bytes a recibir.
 */
void readI2C(uint8_t slave_address, uint8_t reg, uint8_t* msg, uint8_t msg_size);


/**
 * @brief Traduce los bytes recibidos a un vector de aceleraciones en enteros
 * @param uint8_t* msg: mensaje recibido del BMI160
 * @param acc_raw_t* accel: vector de datos crudos donde se guarda el resultado
 */
void asignarAccel(uint8_t* msg, acc_raw_t* accel);


#endif /* INCLUDE_I2C_H_ */
