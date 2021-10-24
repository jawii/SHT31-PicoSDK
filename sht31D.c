#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

int main()
{
    const uint8_t SHT31_DEFAULT_ADDR = 0x44;
    stdio_init_all();
    sleep_ms(5000);
    printf("Program start\n");

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;

    // I2C Initialisation. Using it at 400Khz.
    const uint sda_pin = 16;
    const uint scl_pin = 17;
    i2c_inst_t *i2c = i2c0; // Ports the default port can be used aswell

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    i2c_init(i2c, 400 * 1000);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);

    // Send high repeatability measurement command
    char config[2] = {0};
    config[0] = 0x2C;
    config[1] = 0x06;
    i2c_write_blocking(i2c, SHT31_DEFAULT_ADDR, config, 2, true);
    sleep_ms(2000);

    while (true)
    {
        sleep_ms(2000);
        gpio_put(LED_PIN, 1);

        // Read 6 bytes of data: temp msb, temp lsb, temp CRC, humidity msb, humidity lsb, humidity CRC
        char data[6] = {0};
        i2c_read_blocking(i2c, SHT31_DEFAULT_ADDR, data, 6, true);
        printf("%i\t%i\t%i\t%i\t%i\t%i", data[0], data[1], data[2], data[3], data[4], data[5]);

        double cTemp = (((data[0] * 256) + data[1]) * 175.0) / 65535.0 - 45.0;
        double humidity = (((data[3] * 256) + data[4])) * 100.0 / 65535.0;
        printf("\tTemperature: %.1f C \tHumidity: %.1f RH\n", cTemp, humidity);

        gpio_put(LED_PIN, 0);
    }

    return 0;
}