/*
 * Keypad.c
 *
 * Created: 25/05/2024 14:42:27
 * Author : Javad
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL									//Maybe will change
#include <util/delay.h>									//Maybe I'll change it in the future
#include <string.h>

#define		KEY_DDR	DDRA
#define		KEY_ROW	PORTA
#define		KEY_COL	PINA

#define		LCD_DDR DDRB
#define		LCD_OUT PORTB
#define		LCD_IN	PINB

#define		ETC_DDR DDRD
#define		ETC_OUT PORTD
#define		ETC_IN	PIND

unsigned int login = 0;
unsigned char password[8] = "0000";
unsigned char inPass[8] = "";
unsigned char empty[8] = "\0";

unsigned char passwordCheck()
{
	for ( int j = 0 ; j<8 ; j++ )
	{
		if ( inPass [j] != password [j] )
			return '0';
	}
	return '1';
}

unsigned char letterReader( int row )
{
	unsigned char table [4][3] = {{'1','2','3'},
								  {'4','5','6'},
								  {'7','8','9'},
								  {'*','0','#'}};
		
	KEY_ROW = ~(1<<row);
	unsigned int column = (KEY_COL & 0xE0)>>5;
	unsigned char letter;
	switch(column)
	{
		case(7):
		{
			letter = 0;
			return letter;
		}
		case(6):
		{
			letter = table[row][2];
			return letter;
		}
		case(5):
		{
			letter = table[row][1];
			return letter;
		}
		case(3):
		{
			letter = table[row][0];
			return letter;
		}
	}
	return 0;
}

void lcdCommand( unsigned char cmd )
{
	LCD_OUT = cmd;
	ETC_OUT = 1;
	_delay_us(1);
	ETC_OUT = 0;
	_delay_us(100);
}

void lcdInit()
{
	ETC_DDR = 0x0F;
	LCD_DDR = 0xFF;
	ETC_OUT = 0x00;
	_delay_ms(1);
	
	lcdCommand(0x34);
	lcdCommand(0x0F);
	lcdCommand(0x01);
	_delay_ms(1);
	lcdCommand(0x06);
}

void lcdType( unsigned char letter )
{
	if ( letter == '*' )
	{
		if (strlen(inPass) == 0)
		{
			lcdCommand(2);
			return;
		}
			
		inPass[strlen(inPass)-1] = '\0';
		lcdCommand(0x10);
		LCD_OUT = 0x20;
		ETC_OUT = 0x05;
		_delay_us(1);
		ETC_OUT = 0x04;
		_delay_us(100);
		lcdCommand(0x10);
		return;
	}
	else if ( letter == '#' )
	{
		lcdCommand(1);
		lcdCommand(2);
		if ( passwordCheck() == '1')
		{
			unsigned char y,e,s;
			y = 'Y'; e = 'E' ; s = 'S';
			lcdType(y);
			lcdType(e);
			lcdType(s);
			ETC_OUT = 0x0C;
			login = 1;
		}
		memset(inPass,'\0',sizeof(inPass));
		return;
	}
	else
	{
		strncat(inPass,&letter,1);
		LCD_OUT = letter;
		ETC_OUT = 0x05;
		_delay_us(1);
		ETC_OUT = 0x04;
		_delay_us(100);
	}
}

int main(void)
{
	DDRC = 0xFF;
	ETC_OUT =0x0F;
	
	KEY_DDR = 0x1F;
	lcdInit();
	unsigned char letter;

    while (1) 
    {
		PORTC = login;
		if ( login == 0 )
		{
			
			for ( int i = 0 ; i < 4 ; i++ )
			{
				_delay_ms(6);
				letter = letterReader(i);
				if(letter != 0)
					lcdType(letter);
			}
		}
    }
}

