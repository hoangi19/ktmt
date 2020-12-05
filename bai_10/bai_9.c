/*
 * bai_8.c
 *
 * Created: 11/13/2020 9:25:43 AM
 * Author: hoangi19
 */

#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <delay.h>
#include <stdint.h> // for uint8_t
#include <alcd.h>

#define DHT_ER 0
#define DHT_OK 1

#define DHT_DATA_IN     PINB.7
#define DHT_DATA_OUT    PORTB.7
#define DHT_DDR_DATA    DDRB.7

char data[16];
unsigned char dht_nhiet_do, dht_do_am, i;

unsigned char DHT_GetTemHumi(unsigned char *tem, unsigned char *humi)
{
    unsigned char buffer[5] = {0,0,0,0,0};
    
    unsigned char ii, checksum;
    
    DHT_DDR_DATA = 1;
    DHT_DATA_OUT = 1;
    delay_us(40);
    DHT_DATA_OUT = 0;
    delay_ms(30);
    DHT_DATA_OUT = 1;
    DHT_DDR_DATA = 0;
    delay_us(40);
    
    if (DHT_DATA_IN)
    {
        return DHT_ER;
    }
    else while ((!DHT_DATA_IN));
    
    delay_us(30);
    if (!DHT_DATA_IN)
    {
        return DHT_ER;
    }
    else while ((DHT_DATA_IN));
    
    //BAT DAU DOC DU LIEU
    
    for (i = 0; i< 5; i++)
    {
        for (ii = 0; ii < 8; ii++)      // moi lan do 1 byte
        {
            while(!DHT_DATA_IN); // DOI DATA LEN 1
            delay_us(30);
            if (DHT_DATA_IN)
            {
                buffer[i] |= (1 << (7-ii)); // lay 7 bit
                while((DHT_DATA_IN)); //DOI DATA XUONG 0
            }
        }
    }
    
    checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
    //kiem tra check sum
    
    if ((checksum) != buffer[4])
        return DHT_ER;
    
    
    // lay du lieu
    *tem = buffer[2];
    *humi = buffer[0];
    
    return DHT_OK;
}

void main(void)
{
lcd_init(16); //8
lcd_clear();
lcd_gotoxy(0,0);
lcd_putsf("Hello ..");

DDRD=0x80; // 1000 0000
PORTD = 0x80;

while (1)
    {
    // Please write your application code here
        if (DHT_GetTemHumi(&dht_nhiet_do, &dht_do_am))
        {
            lcd_clear();
            lcd_gotoxy(0,0);
            sprintf(data, "Do am %u", (uint8_t)dht_do_am);
            lcd_puts(data);
            lcd_gotoxy(0,1);
            sprintf(data, "Nhiet do %u", (uint8_t)dht_nhiet_do);
            lcd_puts(data);
            delay_ms(300);
        }
    }
}
