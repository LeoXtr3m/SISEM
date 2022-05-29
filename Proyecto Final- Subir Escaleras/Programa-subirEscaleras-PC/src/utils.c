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


#include <utils.h>
//#include "timer.h"

#define BASE 10

void strreverse(char* begin, char* end) {

    char aux;
    while(end>begin)
        aux=*end, *end--=*begin, *begin++=aux;
}

void itoa(int value, char* str) {
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* wstr=str;
    int sign;
    // Take care of sign
    if ((sign=value) < 0) value = -value;
    // Conversion. Number is reversed.
    do *wstr++ = num[value%BASE]; while(value/=BASE);
    if(sign<0) *wstr++='-';
    //*wstr='\0';
    // Reverse string
    strreverse(str,wstr-1);
}





void intTOchar(int value, char* str1, char* str2, char* str3, char* str4, char* str5) {

    int i=  0;
    int ii =0;
    int cifras[4];
    int cifras2[4];
    char* char1=str1;
    char* char2=str2;
    char* char3=str3;
    char* char4=str4;
    char* char5=str5;

    if(value==0){
        *char1 = 0 + '0' ;
        *char2 = 0 + '0' ;
        *char3 = 0 + '0' ;
        *char4 = 0 + '0' ;
        *char5 = 0 + '0' ;
    }
    else if(value>0 && value<10){
        *char1 =  0 + '0' ;
        *char2 = 0 + '0' ;
        *char3 = 0 + '0' ;
        *char4 = 0 + '0' ;
        *char5 = (value%10) + '0';

    }
    else if(value>=10 && value<100){
        i = 0;
        while(value>0){
            cifras[i] = value%10;   //obtengo el ultimo digito sin decimal
            value =value/10;   // divido entre 10 para que me de un decimal y elimarlo
            i++;    // sumo 1 para guardar el siguiente numero
        }
        ii =0;
        for(value = i-1 ; value >=0; value--){
            cifras2[ii] = cifras[value];      // se guarda del valor mayor del arreglo al menor
            ii++;
        }

        *char1 =  0 + '0' ;
        *char2 =  0 + '0' ;
        *char3 =  0 + '0' ;
        *char4 =  cifras2[0] + '0' ;
        *char5 =  cifras2[1] + '0' ;

    }

    else if(value>=100 && value<1000){
        i = 0;
        while(value>0){
            cifras[i] = value%10;   //obtengo el ultimo digito sin decimal
            value =value/10;   // divido entre 10 para que me de un decimal y elimarlo
            i++;    // sumo 1 para guardar el siguiente numero
        }
        ii =0;
        for(value = i-1 ; value >=0; value--){
            cifras2[ii] = cifras[value];      // se guarda del valor mayor del arreglo al menor
            ii++;
        }

        *char1 =  0 + '0' ;
        *char2 =  0 + '0' ;
        *char3 =  cifras2[0] + '0' ;
        *char4 =  cifras2[1] + '0' ;
        *char5 =  cifras2[2] + '0' ;

    }

    else if(value>=1000 && value<10000){
        i = 0;
        while(value>0){
            cifras[i] = value%10;   //obtengo el ultimo digito sin decimal
            value =value/10;   // divido entre 10 para que me de un decimal y elimarlo
            i++;    // sumo 1 para guardar el siguiente numero
        }
        ii =0;
        for(value = i-1 ; value >=0; value--){
            cifras2[ii] = cifras[value];      // se guarda del valor mayor del arreglo al menor
            ii++;
        }

        *char1 =  0 + '0' ;
        *char2 =  cifras2[0] + '0' ;
        *char3 =  cifras2[1] + '0' ;
        *char4 =  cifras2[2] + '0' ;
        *char5 =  cifras2[3] + '0' ;

    }
    else if(value>=10000 && value<100000){
        i = 0;
        while(value>0){
            cifras[i] = value%10;   //obtengo el ultimo digito sin decimal
            value =value/10;   // divido entre 10 para que me de un decimal y elimarlo
            i++;    // sumo 1 para guardar el siguiente numero
        }
        ii =0;
        for(value = i-1 ; value >=0; value--){
            cifras2[ii] = cifras[value];      // se guarda del valor mayor del arreglo al menor
            ii++;
        }

        *char1 =  cifras2[0] + '0' ;
        *char2 =  cifras2[1] + '0' ;
        *char3 =  cifras2[2] + '0' ;
        *char4 =  cifras2[3] + '0' ;
        *char5 =  cifras2[4] + '0' ;

    }



}





