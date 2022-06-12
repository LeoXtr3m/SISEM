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


#include <stdint.h>
#include <msp430.h>
#include <timer_hw.h>

unsigned int tiks;
unsigned int numm;
unsigned int contTimer;

unsigned int*    Tflag;
unsigned int     SEL_tiks;

void vInitTimerA(void)
{
    // Configuracion Pag. 355 de la familia

    //inicializacion pag. 358 de la familia
    TACCR0 = 0; //Inicialmente parar el timer
    TACCTL0 |= CCIE; //Habilitar la interrupcion para CCR0. -Pag.372 de la familia
    TACTL = TASSEL_1 + ID_0 + MC_1; //Selecciono ACLK, divisor 1, y Modo UP (timer)

    TACCR0 = tiks; /// Valor a cargar en TACCR0, segun el oscilador seleccionado, para dar interrupcion cada 250ms.

}

void setFlagTimer(unsigned int* flag_timer){
    /*Set flag*/
    Tflag = flag_timer;   /// variable de seteo de tiks
    contTimer=0;
}

//Timer ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void vTimerAInterrupt(void)
{
    //inc_time(250);
    numm++;

    contTimer++;
    *Tflag = 1;
    //if(contTimer >= SEL_tiks){
    //    *Tflag = 1;
    //    contTimer = 0;
    //    LPM3_EXIT;
    //}


    // Conmuto el led
    //P1OUT ^= BIT0;

} //Timer ISR



//Rutina de inicializacion del timer hardware usando el cristal como fuente de reloj.
void config_timer_crystal(void)
{
    //  slau144j.pdf, p280
    //The LFXT1 oscillator supports ultra-low current consumption using a 32768-Hz watch crystal in LF mode  (XTS = 0)

    // XTS = 0
    BCSCTL1 &= ~(XTS);

    //  LFXT1Sx = 00, 32768-Hz crystal on LFXT1
    BCSCTL3 |= LFXT1S_0;

    tiks = 8192 - 1; // (32768/4) - 1 valor para 250 ms con el crystal


}

//Rutina de inicializacion del timer hardware usando el VLO como fuente de reloj
void config_timer_VLO(void)
{


    // MSP430x2xx Family users Guide.pdf, p276
    // Usa una frecuencia de 12kHz
    // VLOCLK source is selected by setting LFXT1Sx = 10 when XTS = 0.

    // XTS = 0
    BCSCTL1 &= ~(XTS);
    //LFXT1Sx = 10, bits 4 y 5
    BCSCTL3 |= LFXT1S_2;

    tiks = 120 - 1; // (12000/4) - 1 valor para 250 ms con el VLO
}

