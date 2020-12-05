/*
 * bai_1.c
 *
 * Created: 11/27/2020 2:11:17 AM
 * Author: hoangi19
 */

#include <io.h>
#include <alcd.h>
#include <delay.h>


#define BT1 PINB.2
#define BT2 PINB.3
#define BT0 PINB.0

char *s = "hello-world_____";
int i = 12;
char idend = 12;
char idbegin = 0;
char tmp;


void main(void)
{
DDRB = 0x00;
PORTB = 0xFF;

DDRD.7 = 1;
PORTD.7 = 1;

lcd_init(16);
lcd_clear();
lcd_puts(s);

while (1)
    {
    // Please write your application code here
        if (BT1 == 0)
        {
            delay_ms(250);
            while(idend != 17)
            {
                if (i == idend) idend++;
                if (i == idbegin) {
                    idbegin++;
                }
         
                tmp = s[i];
                s[i] = s[i-1];
                s[i-1] = tmp;
                i--;
                if (i == idbegin) {
                    idbegin++;
                }
                if (i < idbegin) i = idend;
                
                lcd_gotoxy(0,0);
                lcd_puts(s);
                delay_ms(250);
                // printf("%d\n", idend);
            }
        }
        
        if (BT2 == 0)
        {
            delay_ms(250);
            while(idend != 0)
            {
                if (i == idend) idend--;
                if (i == idbegin) {
                    idbegin--;
                }
         
                tmp = s[i];
                s[i] = s[i+1];
                s[i+1] = tmp;
                i++;
                if (i == idend) {
                    idend--;
                }
                if (i > idend) i = idbegin;
                
                lcd_gotoxy(0,0);
                lcd_puts(s);
                delay_ms(250);
                // printf("%d\n", idend);
            }
        }    
    }
}
