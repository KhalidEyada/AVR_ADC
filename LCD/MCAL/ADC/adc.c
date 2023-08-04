

#include <avr/io.h> /* change it to your own one */
#include "adc.h"
#include "../../GENERAL/common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(void)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (1<<REFS0); // AREF=AVCC

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //enable adc + PRrescalar div factor =128
}

uint16 ADC_readChannel(uint8 channel_num)
{
	/* Put Code Here */
	ADMUX|=((0x0f)&channel_num); /* Set input channel to read */
	
	SET_BIT(ADCSRA,6); /* Start conversion */
	
	/* ADCSRA BIT 6 Description
	*ADSC will read as one as long as a conversion is in progress. When the conversion is complete,
	it returns to zero. Writing zero to this bit has no effect.
	*which means we can use this BIT as an indicator like of waiting for the interrupt bit.
	*/
	while(GET_BIT(ADCSRA,6)); 
	
	return ADC; /* Read the digital value from the data register */
}
