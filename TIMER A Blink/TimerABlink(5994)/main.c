#include <msp430.h>

/**
 * main.c
 * Timer A Blink
 */

unsigned long count = 0;
int trigger = 0;
unsigned int counter = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    P1SEL &= ~BIT0;
    P1DIR |= BIT0; //set Port 1.0 output
    P4SEL &= ~BIT7;
    P4DIR |= BIT7; //set Port 4.6 output

    P1DIR &= ~(BIT1); //set Port 1.1 input
    P1REN |= BIT1; //enable pull-up resistor on
    P1OUT |= BIT1;
    P1IE |= BIT1; //enable the interrupt on Port 1.1
    P1IES |= BIT1; //set as falling edge
    P1IFG &= ~(BIT1); //clear interrupt flag

    TA0CTL = TASSEL_1 + MC_1;
    TA0CCTL0 = 0x10;
    TA0CCR0 = 12000;

    P4OUT &= ~BIT7;

    //LPM
    __enable_interrupt();
    _BIS_SR(LPM4_bits + GIE);

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P4OUT ^= BIT7;
    counter++;
    if(counter == 5){
        P1OUT ^= BIT0;
        counter =0;
    }
}
