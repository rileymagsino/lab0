/* 
 * File:   led.c
 * Author: Riley Magsino
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"

#define OUTPUT 0
#define OFF 0
void initLEDs(){ // initialize LEDs
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
}

void turnOnLED(int led){
    if(led == 1){
        LATDbits.LATD0 = 1;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 0;
    }
    else if(led == 2){
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 1;
        LATDbits.LATD2 = 0;
    }
    else if(led == 3){
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 1;
    }    
}