/*
 * Keypad.c
 *
 * Created: 25/05/2024 14:42:27
 * Author : Javad
 */ 

#include <avr/io.h>
#define		KEY_DDR	DDRA
#define		KEY_ROW	PORTA
#define		KEY_COL	PINA


int main(void)
{
	KEY_DDR = 0x1F;
    while (1) 
    {
    }
}

