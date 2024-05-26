/*
 * Keypad.c
 *
 * Created: 25/05/2024 14:42:27
 * Author : Javad
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL									//Maybe will change
#include <util/delay.h>									//Maybe I'll change it in the future

#define		KEY_DDR	DDRA
#define		KEY_ROW	PORTA
#define		KEY_COL	PINA

#define		LCD1_DDR DDRB
#define		LCD1_OUT PORTB
#define		LCD1_IN	 PINB

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

void lcdLoginCommand( unsigned char cmd )
{
	LCD1_OUT = cmd;
	PORTD = 1;
	_delay_us(1);
	PORTD = 0;
	_delay_us(100);
}

void lcdLoginInit()
{
	DDRD = 0x07;
	LCD1_DDR = 0xFF;
	PORTD = 0;
	_delay_ms(1);
	
	lcdLoginCommand(0x34);
	lcdLoginCommand(0x0F);
	lcdLoginCommand(0x01);
	_delay_ms(1);
	lcdLoginCommand(0x06);
}

void lcdLoginType( unsigned char letter )
{
	LCD1_OUT = letter;
	PORTD = 0b101;
	_delay_us(1);
	PORTD = 0b100;
	_delay_us(100);
}

int main(void)
{
	DDRC = 0xFF;
	
	unsigned int login = 0;
	KEY_DDR = 0x1F;
	lcdLoginInit();
	unsigned char letter;

    while (1) 
    {
		if ( login == 0 )
		{
			
			for ( int i = 0 ; i < 4 ; i++ )
			{
				_delay_ms(6);
				letter = letterReader(i);
				PORTC = letter;
				if(letter != 0)
					lcdLoginType(letter);
			}
		}
    }
}

