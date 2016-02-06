/* 
 * File:   timer.c
 * Author: Riley Magsino
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>
#include "timer.h"

#define PRESCALAR_256 3

void initTimer1(){
    TMR1 = 0; // things that keeps count
    T1CONbits.TCKPS = PRESCALAR_256;
    PR1 = 39061;// period register
    T1CONbits.ON = 1; // turn on timer
    IEC0bits.T1IE = 1; // enable interrupt
    IPC1bits.T1IP = 7; //Timer 1 priority
    IFS0bits.T1IF = 0; // put down interrupt flag
}

void initTimer2() {
    TMR2 = 0; // thing that keeps count
    IFS0bits.T3IF; // put down interrupt flag
}

void delayMS(int delay) {
    TMR2 = 0;
    T2CONbits.ON = 1;
    T2CONbits.TCKPS = 7;
    PR2 = ((delay - 10000000)/PRESCALAR_256) - 1 ;
    IFS0bits.T3IF = 0;
    T2CONbits.ON=0;
    IFS0bits.T3IF = 0;
}