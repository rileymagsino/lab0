/* 
 * File:   switch.c
 * Author: Riley Magsino
 *
 * Created on September 3, 2015, 10:15 AM
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0


void initSwitch1(){
    TRISDbits.TRISD6 = INPUT;   // Enable input for switch          
//    CNENDbits.CNIED6 = 1;       // Enable CN interrupt for pin
//    IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
//    IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    CNPUDbits.CNPUD6 = 1;       // Enable Internal Pull-up resistor
}