/*
 * Keypad.c
 *
 * Created: 25/05/2024 14:42:27
 * Author : Javad
 */ 

#include <avr/io.h>
#include <util/delay.h>									//Maybe I'll change it in the future
#define		KEY_DDR	DDRA
#define		KEY_ROW	PORTA
#define		KEY_COL	PINA


int main(void)
{
	DDRC = 0xFF;
	
	unsigned int login = 0;
	KEY_DDR = 0x1F;
	unsigned int column;
	unsigned char table [4][3] = {{'1','2','3'},
								  {'4','5','6'},
								  {'7','8','9'},
								  {'*','0','#'}};
    while (1) 
    {
		if ( login == 0 )
		{
			for ( int i = 0 ; i < 4 ; i++ )
			{
				KEY_ROW = ~(1<<i);
				column = (KEY_COL & 0xE0)>>5;
				PORTC = column;
				_delay_ms(100);
			}
		}
    }
}

