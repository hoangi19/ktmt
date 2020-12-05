/*
 * bai_8.c
 *
 * Created: 12/4/2020 2:20:30 AM
 * Author: hoangi19
 */

#include <io.h>
#include <delay.h>
#include <stdlib.h>
#include <alcd.h>

#define CT1 PINB.2
#define CT2 PINB.3
#define servo1 PORTC.7

float goc = 0.0;
int dem = 0;
int vitri = 150;
unsigned char buf[10];

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Reinitialize Timer 0 value
TCNT0=0xB0;
// Place your code here
dem++;
if (dem == 2000) dem = 0;
if (dem < vitri) servo1 = 1;
else servo1 = 0;
}



void main(void)
{

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
// Timer Period: 0.01 ms
ASSR=0<<AS0;
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0xB0;
OCR0=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
ETIMSK=(0<<TICIE3) | (0<<OCIE3A) | (0<<OCIE3B) | (0<<TOIE3) | (0<<OCIE3C) | (0<<OCIE1C);

// Global enable interrupts
#asm("sei")

lcd_init(16);
lcd_clear();


DDRB = 0x00;
PORTB = 0xFF;

DDRC.7 = 1;

DDRD.7 = 1;
PORTD.7 = 1;
     
//lcd_gotoxy(0,0);
//lcd_putsf("0.0");
while (1)
    {
    // Please write your application code here 
        ftoa(goc, 3, buf);
        //itoa(dem,buf);
        lcd_gotoxy(0,0);
        lcd_puts(buf);
        if (CT1 == 0)
        {
            delay_ms(50);
            vitri++; 
            goc += 1.8;
            if (vitri == 200)
            {
                vitri = 150;
                goc = 0.0;
            }
        }
        
        if (CT2 == 0)
        {
            delay_ms(50);
            vitri--;
            goc -= 1.8;
            if (vitri == 100)
            {
                vitri = 150;
                goc = 0.0;
            }
        }
        
 
    }
}
