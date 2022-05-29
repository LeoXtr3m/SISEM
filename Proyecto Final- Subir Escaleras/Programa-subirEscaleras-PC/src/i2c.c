
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


static uint8_t* flagI2C;


void setI2Cflag(uint8_t* flag) {
    flagI2C = flag;
}

void initI2C(){

  UCB0CTL1 |= UCSWRST;                      // Se habilita el reset de software pag. 430 Familia

  UCB0CTL1 |= UCSSEL_2;                     // Se se lecciona el reloj SMCLK

  UCB0CTL0 &= ~UCSLA10;                      // Direccion de esclavo con 7 bits de direccion
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, Modo de I2C, Modo sincrono pag. 468 familia

  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;

  P1SEL |= BIT6 + BIT7;                     // Asigna los pines del I2C a USCI_B0, P1.7 = SDA
  P1SEL2|= BIT6 + BIT7;                     // Asigna los pines del I2C a USCI_B0, P1.6 = SCL

  UCB0CTL1 &= ~UCSWRST;                     // Restablecimiento de USCI liberado para la operación.


  IE2 &= ~(UCB0RXIE + UCB0TXIE);            // Se desactivan las interrupciones RX y TX

}

void sendI2C(uint8_t slave_address, uint8_t reg, uint8_t *msg, uint8_t msg_size){

    UCB0I2CSA = slave_address;

    /*
     * Send at most I2C_TX_BUFFER_SIZE
     * */

    int j, tope;
    if (msg_size < (I2C_TX_BUFFER_SIZE - 1) ){
        tope = msg_size;
    }
    else {
        tope = I2C_TX_BUFFER_SIZE - 1;
    }

    while (UCB0CTL1 & UCTXSTP);                 // Ensure previous stop condition got sent

    UCB0CTL1 &= ~UCB0TXIFG;                     // Clear TX interrupt flag
    UCB0CTL1 |= UCTR + UCTXSTT;                 // I2C TX, start condition

//    while (UCB0CTL1 & UCTXSTT);                 // Wait for start condition to be sent

    while (!(IFG2 & UCB0TXIFG));                // Wait for previous byte to be loaded into shift register
    UCB0TXBUF = reg;                            // Send slave register address

    for (j=0; j < tope; j++){                   // Send Message

        while (!(IFG2 & UCB0TXIFG));            // Wait for previous byte to be loaded into shift register
        UCB0TXBUF = msg[j];

    }

    while (!(IFG2 & UCB0TXIFG));                // Wait for previous byte to be loaded into shift register
    IFG2 &= ~UCB0TXIFG;                         // Turn off TX Interrupt Flag

    UCB0CTL1 |= UCTXSTP;                        // Generate stop condition
    while (UCB0CTL1 & UCTXSTP);                 // Wait for stop condition to be sent

}

void readI2C(uint8_t slave_address, uint8_t reg, uint8_t* msg, uint8_t msg_size){

    UCB0I2CSA = slave_address;

    while (UCB0CTL1 & UCTXSTP);                 // Ensure previous stop condition got sent

    UCB0CTL1 |= UCTR + UCTXSTT;                 // I2C TX, start condition

    while (!(IFG2 & UCB0TXIFG));                // Wait for slave address to be loaded into shift register
    UCB0TXBUF = reg;                            // Send slave register address

    while (!(IFG2 & UCB0TXIFG));                // Wait for previous byte to be loaded into shift register
    IFG2 &= ~UCB0TXIFG;                         // Turn off TX Interrupt Flag

    IFG2 &= ~UCB0RXIFG;                         // Clear RX Interrupt Flag
    UCB0CTL1 &= ~UCTR;                          // Receiver mode

    UCB0CTL1 |= UCTXSTT;                        // Generate restart condition
    while (UCB0CTL1 & UCTXSTT);                 // Wait for restart condition to be sent
    
    int j;
    for (j = 0; j < msg_size; j++) {

        if ( (msg_size - j) == 1) {
            UCB0CTL1 |= UCTXSTP;
        }

        while (!(IFG2 & UCB0RXIFG));            // Wait for new byte
        msg[j] = UCB0RXBUF;

    }

    while (UCB0CTL1 & UCTXSTP);                 // wait for stop condition to be sent

    *flagI2C = 1;
}


///PROCESAMIENTO
void asignarAccel(uint8_t* msg, acc_raw_t* accel){
    uint8_t idx = 0;
    uint8_t lsb;
    uint8_t msb;
    int16_t msblsb;

    lsb = msg[idx++];
    msb = msg[idx++];
    msblsb = (int16_t)((msb << 8) | lsb);

    if (msblsb < 0) msblsb = - msblsb;
    accel->x = msblsb;

    lsb = msg[idx++];
    msb = msg[idx++];
    msblsb = (int16_t)((msb << 8) | lsb);

    if (msblsb < 0) msblsb = - msblsb;
    accel->y = msblsb;

    lsb = msg[idx++];
    msb = msg[idx++];
    msblsb = (int16_t)((msb << 8) | lsb);

    if (msblsb < 0) msblsb = - msblsb;
    accel->z = msblsb;
}



