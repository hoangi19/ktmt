/*
 * bai_6.c
 *
 * Created: 12/3/2020 6:50:38 PM
 * Author: hoangi19
 */

#include <io.h>

#include <delay.h>
#include <alcd.h>
#include <stdlib.h>

#define CT1 PINB.2

char i = 0;
unsigned int adc_val = 0;
char *buf;

// Declare your global variables here

// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}


void main(void)
{

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);

// ADC initialization
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: AREF pin
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ACME);

DDRB = 0x00;
PORTB = 0xFF;

DDRD.7 = 1;
PORTD.7 = 1;

lcd_init(16);
lcd_clear();

while (1)
    {
    // Please write your application code here
        if (CT1 == 1)
        {
            for (i = 2; i <= 5; i++)
            {
                adc_val = read_adc(i);
                lcd_gotoxy(5*(i-2)%14, 5*(i-2)/14);
                itoa(adc_val, buf);
                lcd_puts(buf);
            }    
        }    
    }
}
