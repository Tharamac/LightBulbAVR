/*
 * 3HB05_2.c
 *
 * Created: 2/25/2020 11:29:51 AM
 * Author : TharaMac
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

//After-Lab Question
void hardware_test(){
  PORTD = 0x02;
  PORTB = 0xFF;
  PORTC = 0xFF;
  _delay_ms(1000);
}

void chk2_1(){
  PORTD = 0x04;
  _delay_ms(500);
  PORTD = 0x00;
  _delay_ms(500);
}

int main(void)
{
	//7SEGs are common cathode which are active high.
	DDRB = 0xFF; //LED1_OUT
	DDRC = 0xFF; //LED2_OUT
	DDRD = 0xFE; //0 (SW) IN : REST(BULB & SCOPE) OUT
	unsigned char SW, firsttime = 1;
	unsigned char on[] = { 0b01011100, 0b01010100};
	unsigned char off[] = { 0b01011100, 0b01110001};
	unsigned char LOOKUPTB[] = {
		0b00111111, 0b00000110, 0b01011011, 0b01001111,
		0b01100110, 0b01101101, 0b01111101, 0b00000111,
		0b01111111, 0b01101111
	};
	unsigned char status = 0;
	hardware_test();
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00; 
	do
	{
		SW = PIND;
		SW &= 0x01;
	} while (SW);
    /* Replace with your application code */
    while (1) 
    {	
		//chk2_1()
		_delay_ms(10);
		SW = PIND;
		SW &= 0x01;
		if(!SW){
			status = !status;
		}
		_delay_ms(10);
		if(status){
			firsttime = 1;
			PORTD = 0x06;
			PORTB = on[0];
			PORTC = on[1];
			_delay_ms(1000);
			PORTD = 0x02;
			PORTB = 0x00;
			PORTC = 0x00;
			_delay_ms(1000);
		}else{
			if(firsttime){
				PORTB = LOOKUPTB[2];
				PORTC = LOOKUPTB[0];
				_delay_ms(1000);
				for (int i = 1; i >= 0 ; i--){
  					for(int j = 9; j >= 0 ; j--){
    					PORTB = LOOKUPTB[i];
    					PORTC = LOOKUPTB[j];
    					_delay_ms(1000);
  					}
				}
				firsttime = 0; 
			}
				PORTD = 0x04;
				PORTB = off[0];
				PORTC = off[1];
				_delay_ms(1000);
				PORTD = 0x00;
				PORTB = 0x00;
				PORTC = 0x00;
				_delay_ms(1000);
		}	
    }
}



