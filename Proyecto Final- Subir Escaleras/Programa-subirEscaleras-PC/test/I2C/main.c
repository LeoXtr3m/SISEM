#include <i2c.h>
#include <msp430.h>
#include "imu.h"

int ejeX = 0;
int ejeY = 0;
int ejeZ = 0;

uint8_t msg[6];
acc_raw_t accel;

int main(void)
{


    // stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    //Se inicializa el i2c
    initI2C();

    //Se inicializa la IMU
    initIMU();

    __enable_interrupt();

    while(1) {


        readI2C(ACCEL_ADDRESS, 0x12, msg, 6);
        asignarAccel(msg, &accel);

        ejeX = accel.x;  //aceleracion en x
        ejeY = accel.y;  //aceleracion en y
        ejeZ = accel.z;  //aceleracion en z

        __delay_cycles(20000);

    }
}
