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
#include <math.h>
#include <stdio.h>

int q =0;
int k =0;

char charY;
char charZ;

uint8_t datos = 150;

uint8_t yy = 0;
uint8_t zz = 0;

unsigned int promedioY = 0;
unsigned int promedioZ = 0;

unsigned int sumaY= 0;
unsigned int sumaZ= 0;

int restaVarY = 0;
int restaVarZ = 0;

unsigned int sumaVarY = 0;
unsigned int sumaVarZ = 0;

unsigned int varianzaY = 0;
unsigned int varianzaZ = 0;

unsigned int desEstandarY = 0;
unsigned int desEstandarZ = 0;

unsigned int maximoY = 0;
unsigned int maximoZ = 0;

unsigned int minimoY = 100;
unsigned int minimoZ = 100;

uint8_t analisis2 = 0;
uint8_t subiendoEscaleras = 0;


char concatenado;

void recopilarDatos(int16_t* ejeX, int16_t* ejeY, int16_t* ejeZ){

    if(q<datos){

        yy = (int)division(ejeY,100);
        zz = (int)division(ejeZ,10);

        buffer_Y[q] = yy;
        buffer_Z[q] = zz;

        q++;
    }
}

void procesarDatos(uint8_t* resultado){
    sumaY = 0;
    sumaZ = 0;

    //Suma
    for(k = 0; k<datos ; k++){
        sumaY = sumaY + buffer_Y[k];
        sumaZ = sumaZ + buffer_Z[k];

        //Maximos Y
        if(buffer_Y[k]> maximoY){
            maximoY = buffer_Y[k];
        }
        //minimos Y
        else if (buffer_Y[k]< minimoY){
            minimoY = buffer_Y[k];
        }
        //Maximos Z
        if(buffer_Z[k]> maximoZ){
            maximoZ = buffer_Z[k];
        }
        //minimos Z
        else if (buffer_Z[k]< minimoZ){
            minimoZ = buffer_Z[k];
        }

    }


    //Promedio
    promedioY = sumaY/datos;
    promedioZ = sumaZ/datos;

    //Varianza
    for(k = 0; k<datos ; k++){
        restaVarY =   buffer_Y[k] - promedioY;
        sumaVarY = sumaVarY + (restaVarY*restaVarY);

        restaVarZ =  buffer_Z[k] - promedioZ;
        sumaVarZ = sumaVarZ + (restaVarZ*restaVarZ );
    }

    varianzaY = sumaVarY/datos;
    varianzaZ = sumaVarZ/datos;



    //Desviacion estandar
    desEstandarY = sqrt(varianzaY);
    desEstandarZ = sqrt(varianzaZ);


    analisis2=0;
    subiendoEscaleras = 0;


    //ANALISIS 1 PROMEDIO
    if(promedioZ < 130){
        if(promedioZ > 80){
            if(promedioY < 36){
                analisis2=1;
            }
            else{
                analisis2=0;
                subiendoEscaleras = 0;
            }
        }
        else{
            analisis2=0;
            subiendoEscaleras = 0;
        }
    }
    else{
        if (sumaY == 32){
            analisis2=1;
        }
        else{
            analisis2=0;
            subiendoEscaleras = 0;
        }

    }

    //ANALISIS 2 SUMA

    if(analisis2 == 1){
        if(sumaZ < 20000){
            if(sumaZ > 10000){
                if(sumaY < 5400){
                    subiendoEscaleras = 1;
                }
                else{
                    subiendoEscaleras = 0;
                }
            }
            else{
                subiendoEscaleras = 0;
            }
        }
        else{
            if(sumaY < 4900){

                subiendoEscaleras = 1;
            }
            else{
                subiendoEscaleras = 0;
            }
        }
    }
    else{
        subiendoEscaleras = 0;
    }

    q=0;

    //se manda el resultado 1 o 0
    *resultado =  subiendoEscaleras;


}





division(int a, int b)
{
    return(a / b);
}





