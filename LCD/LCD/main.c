/*
 * LCD.c
 *
 * Created: 27/05/2024 17:48:14
 * Author : Javad
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL									//Maybe will change
#include <util/delay.h>									//Maybe I'll change it in the future
#include <string.h>

#define		LCD_DDR		DDRC
#define		LCD_OUT		PORTC
#define		LCD_IN		PINC

#define		Micro_DDR	DDRA
#define		Micro_OUT	PORTA
#define		Micro_IN	PINA



void lcdCommand( unsigned char cmd )
{
	LCD_OUT = cmd;
	PORTD = 1;
	_delay_us(1);
	PORTD = 0;
	_delay_us(100);
}

void lcdType( unsigned char letter )
{
	LCD_OUT = letter;
	PORTD = 0b101;
	_delay_us(1);
	PORTD = 0b100;
	_delay_us(100);
}

void lcdPrint( unsigned char word[] )
{
	for ( int i = 0 ; i<strlen(word) ; i++ )
	{
		lcdType(word[i]);
	}
}

void lcdInit()
{
	DDRD = 0x07;
	LCD_DDR = 0xFF;
	PORTD = 0;
	_delay_ms(1);
	
	lcdCommand(0x38);
	lcdCommand(0x0C);
	lcdCommand(0x01);
	_delay_ms(1);
	lcdCommand(0x06);
	for ( int i = 0 ; i < 80 ; i ++ )
	{
		if( i<16 || i>=40 )
			lcdType(0xFF);
		else
			lcdType(' ');
	}
}

void lcdLogin()
{
	lcdCommand(18);
}

int main(void)
{
	lcdInit();
	
	DDRB = 0;
	unsigned int login = 0;
	_delay_ms(1000);
	login = PINB;
	
    while (1) 
    {
		if ( login == 1 )
			lcdLogin();
    }
}

