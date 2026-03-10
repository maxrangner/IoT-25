#include <avr/io.h>
#include <stdint.h>

void spi_master_init(void)
{
    DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2);
    PORTB |= (1 << PORTB2);
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t spi_master_tranceiver(uint8_t data)
{
    SPDR = data;

    while ( !(SPSR & (1 << SPIF)) );

    return SPDR;
}
