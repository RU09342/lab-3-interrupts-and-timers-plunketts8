#include <msp430.h> 


/**
 * main.c
 *  Button Interrupt
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |=BIT0; //set Port 1.0 output

    P5DIR &=~(BIT5); 
    P5REN|=BIT5;//enabl3
    P1OUT|=BIT1; //pull-up resistor

    P5IE |=BIT5;
    P5IES |=BIT5;//set as falling edge
    P5IFG &=~(BIT5);//clear interrupt

    //low power mode
    _BIS_SR(LPM4_bits + GIE);
}
//Port 1 ISR
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
    P1OUT ^=0x01; // Change state of P1.1
    volatile unsigned int time = 1000;
    do (time=time-1);
    while (time != 0);
    P5IFG &=~(BIT5); // Clear flag
}
