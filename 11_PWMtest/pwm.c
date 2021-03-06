#include <msp430.h>

#define GREEN	BIT6						// Green LED -> P1.6

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;				// Stop WDT
	P1DIR |= GREEN;							// Green LED -> Output
    // From datasheet check pin no for timer output
	P1SEL |= GREEN;							// Green LED -> Select Timer Output

	TACCR0 = 500;							// Set Timer0 PWM Period
    // How is period defined?
    // Check all types of output mode
	TACCTL1 = OUTMOD_7;						// Set TA0.1 Waveform Mode - Clear on Compare, Set on Overflow
	TACCR1 = 1;								// Set TA0.1 PWM duty cycle
	TACTL = TASSEL_2 + MC_1;				// Timer Clock -> SMCLK, Mode -> Up Count
    // clock frequency and pwm frequency relation?
	while(1)
	{
		unsigned int i;
		for(i = 0; i < 500; i++)
		{
			TACCR1 = i;						// Increase Duty from min to max
			__delay_cycles(5000);
		}
		for(i = 500; i > 0; i--)
		{
			TACCR1 = i;						// Decrease Duty from max to min
			__delay_cycles(5000);
		}
	}
}
