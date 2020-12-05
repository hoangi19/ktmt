/*
 * bai_4.c
 *
 * Created: 11/27/2020 3:42:33 AM
 * Author: hoangi19
 */

#include <io.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>

#define BT1 PINB.2
#define BT2 PINB.3
#define BT3 PINB.0

#define led PORTD.5

int dem = 0;
char *buf;

void main(void)
{

DDRB = 0x00;
PORTB = 0xFF;

// DEN NEN MAN HINH
DDRD.7 = 1;
PORTD.7 = 1;

DDRD.5 = 1; // LED

lcd_init(16);
lcd_clear();
lcd_gotoxy(0,0);
lcd_puts("0");

while (1)
    {
    // Please write your application code here
        if (BT1 == 0)
        {   
            while(BT2);
            delay_ms(250);
            dem++;
            itoa(dem, buf);
            lcd_clear();
            lcd_gotoxy(0,0);  
            lcd_puts(buf);
        }
        
        if (BT2 == 0)
        {    
            while(BT1);   
            delay_ms(250);
            dem--;
            if (dem < 0) dem = 0;
            itoa(dem, buf);
            lcd_clear();
            lcd_gotoxy(0,0);  
            lcd_puts(buf);
        }
        
        if (dem > 0) led = 1;
            else led = 0;
    }
}
