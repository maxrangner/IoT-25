#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    lcd_init();
    lcd_puts("Hallå från AVR!");

    int num = 0;
    while(1) {
        lcd_set_cursor(0,1);
        lcd_printf("DÖtrist vänta:%d", num++);
        _delay_ms(1000);
    }
	return 0;
}
