/*
 * bai_11.c
 *
 * Created: 12/4/2020 10:46:45 AM
 * Author: hoangi19
 */

#include <io.h>
#include <delay.h>
#include <stdlib.h>
#include <alcd.h>

#define CT1 PINB.2

unsigned int dem = 0;
char buf[10];


void main(void)
{
lcd_init(16);
lcd_clear();

DDRD.7 = 1;

DDRB = 0x00;
PORTB = 0xFF;

PORTD.7 = 1;

while (1)
    {
    // Please write your application code here
        itoa(dem, buf);
        lcd_gotoxy(0,0);
        lcd_puts(buf);
        if (CT1 == 0)
        {
            dem++;
        }    

    }
}
