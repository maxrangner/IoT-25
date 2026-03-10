#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void spi_master_init(void);
uint8_t spi_master_tranceiver(uint8_t data);

#endif
