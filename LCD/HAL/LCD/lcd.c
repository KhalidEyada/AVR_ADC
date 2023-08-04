
#define F_CPU 8000000UL
#include <util/delay.h> /* For the delay functions */
#include "../../GENERAL/common_macros.h" /* For GET_BIT Macro */
#include "lcd.h"
#include "../../MCAL/DIO/DIO_Interface.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void)
{
	/* Configure the direction for RS and E pins as output pins */
	DIO_voidSetPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,DIO_u8_OUTPUT);
	DIO_voidSetPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_u8_OUTPUT);

	_delay_ms(20);		/* LCD Power ON delay always > 15ms */


	/* Configure 4 pins in the data port as output pins */
	DIO_voidSetPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,DIO_u8_OUTPUT);
	DIO_voidSetPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,DIO_u8_OUTPUT);
	DIO_voidSetPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,DIO_u8_OUTPUT);
	DIO_voidSetPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,DIO_u8_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);


	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command)
{
	DIO_voidSetPinValue(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); /* Instruction Mode RS=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	DIO_voidSetPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/*Put Code Here*/
	// Send most 4bits
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,(command&(1<<4))>>4);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,(command&(1<<5))>>5);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,(command&(1<<6))>>6);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,(command&(1<<7))>>7);
	
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_voidSetPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	DIO_voidSetPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/*Put Code Here*/
	// send least 4bits
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,(command&(1<<0))>>0);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,(command&(1<<1))>>1);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,(command&(1<<2))>>2);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,(command&(1<<3))>>3);
	
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_voidSetPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data)
{
	/*Put Code Here*/
	DIO_voidSetPinValue(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH); /* Instruction Mode RS=1 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	DIO_voidSetPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/*Put Code Here*/
	// Send most 4bits
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,(data&(1<<4))>>4);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,(data&(1<<5))>>5);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,(data&(1<<6))>>6);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,(data&(1<<7))>>7);
	
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_voidSetPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	DIO_voidSetPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/*Put Code Here*/
	// send least 4bits
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,(data&(1<<0))>>0);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,(data&(1<<1))>>1);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,(data&(1<<2))>>2);
	DIO_voidSetPinValue(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,(data&(1<<3))>>3);
	
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_voidSetPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

	
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str)
{
	/*Put Code Here*/
	/* display the string character by character until it reaches null character */
	while(*Str!='\0')
	{
		LCD_displayCharacter(*Str); 
		Str++;
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col)
{
	/*Put Code Here*/
	/* go to the start address of the intended row then add the column position to the start address of the row  */
	switch(row){
		case 0:LCD_sendCommand(0x80+col); break;
		case 1:LCD_sendCommand(0xC0+col); break;
		case 2:LCD_sendCommand(0x94+col); break;
		case 3:LCD_sendCommand(0xD4+col); break;
	}
	
	
}


void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}
/*
 * Description :
 * fill special characters in CGRAM
 */
void LCD_saveSpecialCharacter(u8 position, u8 arr[8]){
		
		LCD_sendCommand(0x40+(position*8));//move to start of character in  the CGRAM
		for (u8 conter=0; conter<8;conter++)
		{
			LCD_displayCharacter(arr[conter]);//fill the 8 lines of the cell with defined value
		}
}
