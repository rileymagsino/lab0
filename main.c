/* 
 * File:   main.c
 * Author: rmagsino8505
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"
#include "switch.h"

#define OUTPUT 0
#define INPUT 1

#define LED1 LATDbits.LATD0 
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2

//Define states of the state machine
// This is Part Three

typedef enum stateTypeEnum{
    led1, led2, led3, wait, otherWait, debouncePress, debounceRelease, debounceReleasePart2    
} stateType;

volatile int timing = 0;
volatile stateType state = led1;

int main() {
  
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initSwitch1();
    initLEDs();
    initTimer1();
    initTimer2();
    int PrevState=0;  
    while(1)
    {
            switch(state){
               case  led1:
                    LED1=1;
                    LED2=0; 
                    LED3=0;
                    PrevState=1;
                    if(PORTDbits.RD6==0) state=debouncePress; 
                    break;
                     
                case led2:
                    LED1= 0;
                    LED2= 1;
                    LED3= 0;
                    PrevState=2;
                    if(PORTDbits.RD6==0) state=debouncePress;
                    break;
                    
                case led3:
                    LED1 = 0;
                    LED2 = 0;
                    LED3 = 1;
                    PrevState=3;
 
                    if(PORTDbits.RD6==0) state=debouncePress;
                    break;
                    
                case debouncePress:
                    delayMS(10);
                    state=wait;
                    break;      
 
                case debounceRelease: 
                    delayMS(10); 
                    state=otherWait;
                    break;
                   
                case wait:
 
                    if(PORTDbits.RD6 == 0) state=wait; 
                    else state = debounceRelease;
                    break;
 
                case otherWait:
                    if (timing == 1)
                     {
                         if(PrevState == 1)
                        {
                             timing = 0;
                             TMR1 = 0;
                             state = led3;
                        }
                        else if(PrevState == 2)
                        {
                            timing = 0;
                            TMR1 = 0;
                            state = led1;
                         }
                         else if(PrevState == 3)
                         {
                             timing = 0;
                             TMR1 = 0;
                             state = led2;
                         }
                     }
                    
                     else
                     {
                        if(PrevState == 1)
                        {
                            timing=0; 
                            TMR1=0;
                            state=led2;
                        }
                        else if(PrevState==2)
                        {
                            timing=0;
                            TMR1=0;
                            state=led3;
                        }
                         else if(PrevState==3)
                        {   
                            timing=0;
                            TMR1=0;
                            state=led1;
                        }
                     } 
                   break;
            }
        }
    return 0;
}
 

void __ISR(_TIMER_1_VECTOR, IPL7SRS) __T1Interupt()
{

    IFS0bits.T1IF=0;        //set flag back down
 
    timing=1;
 
}

/*// This is Part Two
typedef enum stateTypeEnum{
    led1, led2, led3  
} stateType;

volatile stateType state = led1; //Use volatile variables that change within interrupts

int main() {
    SYSTEMConfigPerformance(10000000); //Configures low-level system parameters for 10 MHz clock
    enableInterrupts(); //This function is necessary to use interrupts.
    initLEDs(); // initializes LEDs
    initTimer1(); // initializes timers`

    while (1) {
        switch (state) {
            case led1:
                LATDbits.LATD0 = 1;
                LATDbits.LATD1 = 0;
                LATDbits.LATD2 = 0;
                break;
            case led2:
                LATDbits.LATD0 = 0;
                LATDbits.LATD1 = 1;
                LATDbits.LATD2 = 0;
                break;
            case led3:
                LATDbits.LATD0 = 0;
                LATDbits.LATD1 = 0;
                LATDbits.LATD2 = 1;
                break;
        }
    }

    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt() { // ISR for timer
    IFS0bits.T1IF = 0;
    if (state == led1) state = led2;
    else if (state == led2) state = led3;
    else if (state == led3) state = led1;
    return;
} */
//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed