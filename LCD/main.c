
#define F_CPU 8000000UL
#include "../HAL/LCD/lcd.h"
#include "../GENERAL/std_types.h"
#include "../MCAL/ADC/adc.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include <util/delay.h>
#include <stdlib.h>


int main(){
	DIO_voidSetPinDirection(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_INPUT); /*setting Pin1 as input in Port A as it will be used lm35 input */
	LCD_init(); /*initializing LCD*/
	LCD_moveCursor(0,0); /*Moving the cursor to the start of the LCD*/
	LCD_displayString("temperature = "); /*displaying the string temperature = */
	ADC_init();/*initializing ADC*/
	char str[5];/*initializing array of characters to contain the converted analog readings */
		while(1)
		{
			LCD_moveCursor(0,15); /*Moving the cursor to row 0 column 15*/
			uint16 temperature = ADC_readChannel(1)*0.49; /*LM35 adc values needes to be calibrated by 0.49*/
			itoa(temperature,str,10);/*convert integer values to string*/
			LCD_displayString(str);/*displaying the temperature value*/
			_delay_ms(1000);
		}
		return 0;
}
