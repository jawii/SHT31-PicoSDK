# SHT31-PicoSDK

Setupping the SHT31 with Raspberry Pi Pico-SDK

# Wiring

![Wiring](/wiring.jpg?raw=true "Wiring")

SHT VIN : Pico 3V3

SHT GND : Pico GND

SHT SCL : Pico GP17

SHT SDA : Pico GP16

# Build

Pico-SDK source must be on the Path. I created the project using the pico-project-generator.

```
cd build
cmake ..
make
```

Copy the uf2 to your Rasperrypi Pico
