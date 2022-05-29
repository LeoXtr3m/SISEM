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
#include<stdint.h>
#include"utils.h"
#include<timer_hw.h>

unsigned int* local_EOL;
unsigned int* valorTiks_XX;
unsigned int j = 0;
unsigned int i = 1;
char rt[3];
char ul;
int valor_WPXX =0;
int n=0;

unsigned int* nuevoTimpoB;

unsigned int* banderaTimer;


/*******************************
 **funcion que inicializa UART**
 *******************************/
void uart_init(unsigned int* pt_fin){

    /*configuramos UART linea 640 msp430g2553.h capitulo 15 manual de la familia*/
    //UCA0CTL1 = 1;
    //UCSWRST = 1; // Tiene que estar en uno para indicar que esta en reset y que pueda funcionar
    UCA0CTL1 |= UCSWRST; //Configuracion de inicializacion para la UART Pag. 413 de la familia //reset enable

    P1SEL |= BIT1|BIT2; //Pagina 43 del datasheet se pide que el bit 1 y 2 del PINSEL esten en 1, el 0 se configura solo
    P1SEL2 |=BIT1|BIT2; //Pagina 43 del datasheet se pide que el bit 1 y 2 del PINSEL2 esten en 1, el 0 se configura solo

    UCA0CTL1 |= UCSSEL_2;       //seleccionamos que vamos utilizar ACLk seleccionamos que se va a transmitir MSB primero

    //UCA0CTL0 = 0  //es zero porque en la pagina 431 de la familia se configura conforme a lo que nos pide el proyecto (
                    //El módulo de comunicación UART deberá configurar la misma en 9600 bps, 8 bits de datos, sin paridad y un
                    //bit de parada (8N1).
    UCA0CTL0 = 0;  // UCSYNC_0 + UCMODE_0 + UCSPB_0 + UCMSB_0 + UCPEN_0;
    UCA0CTL1 |= UCSSEL_2;  // Se utiliza el SMCLK de 16 MGhz, pag 430


    UCA0BR0   = 105;           //Variable de 8 bits para obtener el Baud Rate
    UCA0BR1   = 0;             //Variable de 8 bits para obtener el Baud Rate U0BR0 + U0BR1 = 16bits
    UCA0MCTL |= UCBRS0;           // resto de 32.768kHz/9600  //se activa el UCBRS0 - Configuracion del UCBRSx = 1 de acuerdo a la pag 420

    local_EOL= pt_fin; //valor de bandera inicial en 0 inicial pt_fin = pt_EOL - pero local_EOL toma las caracteristicas de puntero de pt_fin
                        // por lo que todo valor asignado a local_EOL sera almacenado en pt_fin y de ahi a EOL bandera.

    UCA0CTL1 &= ~UCSWRST;       //software reset disable

    UC0IE |= UCA0RXIE; //Habilitamos las interrupciones en UCA0RXIE (RX) para resivir datos, UC0IE no esta en la hoja de datos pero   existe
    //IE2 = 0 // Desabilitamos las interrupciones del registro 2, pag. 433 de la familia (UCA0TXIFG y UCA0RXIFG)

}


/****************************************************************************************************
* Copia en el buffer de transmision el mensaje a enviar y habilita interrupcion de registro vacio.**
* char* datos_tx: puntero a el mensaje a transmitir.************************************************
****************************************************************************************************/
void transmitir_TX(char* mensaje){

    //copiamos en el buffer de transmision el mensaje a enviar
    __disable_interrupt();
    strcpy(&buffer_TX[0], mensaje);  // EL mensaje es del buffer externo
    UCA0TXBUF = buffer_TX[0];   //enviamos el primer dato
    __enable_interrupt();
    UC0IE |= UCA0TXIE;           //habilitamos interupcion de transmision
}


/*************************************************************
* funcion que copia el buffer de recepcion a buffer externo.**
* char* buff_ext: puntero al buffer externo.
**************************************************************/
void copiar_ext(char* buff_ext){
//    UC0IE     &= ~UCA0RXIE;     //deshabilitamos interrupciones de recepcion para no tener problemas de datos compartidos
    __disable_interrupt();

      strcpy(buff_ext, &buffer_RX[0]);

    __enable_interrupt();
//    UC0IE     |= UCA0RXIE;      //habilitamos interrupciones para RX
}

/*****************************************************
**rutina de atencion a la interrupcion registro vacio*
******************************************************/
#pragma vector = USCIAB0TX_VECTOR
__interrupt void registro_vacio_TX(void){
    // i se inicializa afuera de las funciones
    // inicializa con 1 ya que TX asigna el primer valor

    if (buffer_TX[i] != '\0'){
        UCA0TXBUF = buffer_TX[i];
        i++;
    }
    else{
        buffer_TX[i+1]   = '\t';             //asignamos fin de linea
        UCA0TXBUF = buffer_TX[i+1];
        //buffer_TX[i+1] = '\r';             //le asignamos enter
        //UCA0TXBUF = buffer_TX[i+1];
        i = 1;
        UC0IE = ~UCA0TXIE;            //deshabilitamos interrupcion de transmision
    }
}



/****************************************************************
**rutina de atencion a la RX - se activa cuando llega un mensaje*   //pag. 433
****************************************************************/
#pragma vector = USCIAB0RX_VECTOR
__interrupt void recibi_mensaje_RX(void){

    // j se incializa al principio de todo
    // j vale 0 al iniciar  -- 'HOLA\r'

    buffer_RX[j] = UCA0RXBUF;  // PASO 1 - se almacena el dato de recepcion el el buffer_RX

//    UC0IE     &= ~UCA0RXIE;     //deshabilitamos interrupciones de recepcion para no tener problemas de datos compartidos
__disable_interrupt();
    if (buffer_RX[j] != '\r')       // Se indica que con '\r' (este valor lo da la tecla enter)  que el mensaje esta completo y vuelve al principio el cursos
        j++;                        //nos movemos al siguiente lugar del buffer de recepcion
    else{
          buffer_RX[j+1] = '\n';        //asigna un salto de linea
          buffer_RX[j+2] = '\0';        //guardamos el \0 fin de string   \r\n\0
        j = 0;
        *local_EOL = 1;
        //salir de la int despierto

        LPM3_EXIT;
    }


__enable_interrupt();
  //  UC0IE |= UCA0RXIE;
}








////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// FUNCION PARA COMANDOS EN CONSOLA UART      ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*************************************************************
* funcion que añade la temperatura y el tiempo al buffer_temp
* int* temp: puntero con la temperatura actual.
* int* horas: puntero con la hora actual.
* int* minutos: puntero con la minutos actuales.
* int* segundos: puntero con la segundos actuales.
**************************************************************/

void add_XYZ(int* accelX,int* accelY,int* accelZ){   // añade la temperatura al buffer_temp en caracter char

    __disable_interrupt();
    //intTOchar(accelX, &buffer_temp[0], &buffer_temp[1], &buffer_temp[2], &buffer_temp[3], &buffer_temp[4]);

    //buffer_temp[5] = ',' ;

    intTOchar(accelY, &buffer_temp[0], &buffer_temp[1], &buffer_temp[2], &buffer_temp[3], &buffer_temp[4]);

    buffer_temp[5] = ',' ;

    intTOchar(accelZ, &buffer_temp[6], &buffer_temp[7], &buffer_temp[8], &buffer_temp[9], &buffer_temp[10]);

    buffer_temp[11] = '\r' ;
    buffer_temp[12] = '\n' ;
    buffer_temp[13] = '\0' ;
    __enable_interrupt();
    //*local_EOL = 1;
}
/*************************************************************
* funcion que copia el buffer de temperatura
* char* buff_temp: puntero al buffer temperatura.
**************************************************************/

void copiar_temp(char* buff_temp){
//    UC0IE     &= ~UCA0RXIE;     //deshabilitamos interrupciones de recepcion para no tener problemas de datos compartidos
    __disable_interrupt();
    strcpy(buff_temp, &buffer_temp[0]);
    __enable_interrupt();
//    UC0IE     |= UCA0RXIE;      //habilitamos interrupciones para RX
}















