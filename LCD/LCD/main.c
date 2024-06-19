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
}

void lcdLogin()
{
	PORTB = PINB;
	PORTB = PINB << 1;
	
	unsigned char name1[] = "Mohammad Javad Rahimi   40009153";
	lcdPrint(name1);
	
	_delay_ms(50);
	
	for ( int i = 0 ; i < 39 ; i++ )
	{
		_delay_ms(15);
		lcdCommand(0x18);
	}

	lcdCommand(1);
	_delay_ms(50);
	lcdCommand(2);
	
	
	lcdCommand(0x00);
	unsigned char name2[] = "Mohammad Amin Shams     40011223";
	lcdPrint(name2);
	
	_delay_ms(50);
	
	for ( int i = 0 ; i < 39 ; i++ )
	{
		_delay_ms(15);
		lcdCommand(0x18);
	}
		
	lcdCommand(1);
	_delay_ms(50);
	lcdCommand(2);
	
	unsigned char line1[] = "                1) Change Password                 ";
	lcdPrint(line1);
	
	lcdCommand(0xC0);
	unsigned char line2[] = "                2) Log out                    ";
	lcdPrint(line2);
}

void options()
{
	
	_delay_ms(50);
	
	for ( int i = 0 ; i < 39 ; i++ )
	{
		_delay_ms(20);
		lcdCommand(0x18);
	}
}

int main(void)
{
	lcdInit();
	Micro_DDR = 0xFF;
	
	DDRB = 2;
	
    while (1) 
    {
		if ( PINB == 1 )
		{
			lcdLogin();
			while (1)
			{
				options();
			}
		}
    }
}

