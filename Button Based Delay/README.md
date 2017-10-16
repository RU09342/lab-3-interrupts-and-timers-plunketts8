# Button Based Delay

The goal of this lab was to write a program that would implement a timer based interrupt to blink the LED at a user generated frequency.

## Implementation

Similair to the other sections of this lab the correct pins need to be initialized as inputs and outputs. Since there is no interrupts the watchdog timer should be disabled with: 

```c
	WDTCTL = WDTPW + WDTHOLD or WDTCTL = WDTPW | WDTHOLD
```

The following lines of code initialized Timer A, set the compare mode for CCTL and set the rate which the LED would blink.
```c
    
	TB0CTL = TBSSEL_1 + MC_1 + ID_2; 
	TB0CCTL0 = 0x10; 
	TB0CCR0 = 1600; 

```

Whenever a push button is used bouncing must be accounted for. When the is pressed a single time a single response is expected. The following code accounts for bouncing:
```c
	P1IE &= ~BIT1;
	__delay_cycles(1);	
```
The main functionaliy of the code uses both the falling and rising edge of the button as triggers for CCR0. At the first trigger CCR1 is set to capture mode, trigger is set to 1, and TA1R is stored. This is shown in the following code:
```c

//If statment for falling edge of trigger
if (trigger == 0)
    {
        TA1CTL = TASSEL_1 + MC_3; 
        TA1CCR0 = 0xFFFF; 
        TA1CCTL0 = CAP; 
        trigger = 1;
        TA0CCR0 = 1; 

    }	
```

At the rising edge of the trigger TA1R is assigned to TA1CCR0 allowing the user to set the frequency. The code is then prepared for the next trigger. 
```c
//If statment for rising edge of trigger
    else if (trigger == 1)
    {
        TA1CTL = MC_0; 
        TA0CCR0 = TA1R; 

        if (TA0CCR0 > 65500) 
            TA0CCR0 = 0xFFFF;
        if (TA0CCR0 < 2000) 
            TA0CCR0 = 2000;

        TA1CTL = TACLR; //Clear Timer A
        trigger = 0;
    }

```




# Original Assignment
# Button Based Delay
Now that you have begun to familiarize yourself with the TIMER modules, why don't we make an interesting change to our code from the last lab.

## Task
Setup your microcontroller to initially blink and LED at a rate of 10Hz upon restarting or powering up. Then utilizing one of the buttons on board, a user should be able to set the delay or blinking rate of the LED by holding down a button. The duration in which the button is depressed should then become the new rate at which the LED blinks. As previously stated, you most likely will want to take advantage of the fact that TIMER modules exist and see if you can let them do a bulk of the work for you.

### Extra Work
## Reset Button
What is a piece of electronics without a reset button? Instead of relying on resetting your processor using the built in reset circuitry, why not instead use another button to reset the rate back to 10Hz.

## Button Based Hertz
Most likely using two buttons, what if instead of making a delay loop based on the time, the user could instead enter a mode where the number of times they pressed the button would become the number in Hz of the blinking rate? How do you think you would implement that with just one button?