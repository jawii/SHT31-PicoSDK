# SHT31-PicoSDK

Setupping the SHT31 with Raspberry Pi Pico-SDK

# Wiring

SHT VIN : Pico 3V3
SHT GND : Pico GND
SHT SCL : Pico GP17
SHT SDA : Pico GP16

# Build

```
cd build
cmake ..
make
```

Copy the uf2 to your Rasperrypi Pico
