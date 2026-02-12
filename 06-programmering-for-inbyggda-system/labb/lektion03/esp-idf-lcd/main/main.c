#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "hd44780.h"

void app_main(void)
{
    hd44780_t lcd = {
        .write_cb = NULL,
        .pins = {
            .rs = 0,
            .e = 0,
            .d4 = 0,
            .d5 = 0,
            .d6 = 0,
            .d7 = 0
        },
        .font = HD44780_FONT_5X8,
        .lines = 2
    };
    
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
