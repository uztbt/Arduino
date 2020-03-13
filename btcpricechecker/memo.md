# GxEPD2 Library

## mapping suggestion for ESP32

https://github.com/ZinggJM/GxEPD2/blob/master/ConnectingHardware.md

| E-Paper Pin | ESP 32 Pin | Checked up | BTCIOT(VSPI)   | Use HSPI bus  |
| ----------- | ---------- | ---------- | -------------- | ------------- |
| BUSY        | 4          |            | 4              | 17            |
| RST         | 16         |            | 21 (VSPIHD...) | 4 (HSPIHD...) |
| DC          | 17         |            | 22 (VSPIWP...) | 2 (HSPIWP...) |
| CS          | SS(5)      | YES        | 5 (VSPI)       | 15 (HSPI)     |
| CLK         | SCK(18)    | YES        | 18 (VSPI)      | 14 (HSPI)     |
| DIN         | MOSI(23)   | YES        | 23 (VSPI)      | 13 (HSPI)     |
| GND         | GND        | YES        | GND            | GND           |
| 3.3V        | 3.3V       | YES        | 3.3V           | 3.3V          |

- Using IO5 as a chip selector
- It corresponds to VSPICS0 (https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf)
- This wiring uses the **VSPI buses**
- This system is using SPI3 controller out of the four options (SPI0 to SPI3)
- Actually, IO23 is VSPID

# Pins of the epaper module

| Short name | Long name             | Description                                         |
| ---------- | --------------------- | --------------------------------------------------- |
| VCC        | 3.3V                  |                                                     |
| GND        | Ground                |                                                     |
| Busy       | Busy state output pin | Tells the ESP32 that this module is doing something |
| Reset      | External reset pin    | Reset the module                                    |
| D/C        | Data Connect          |                                                     |
| CS         | SPI Chip Select       |                                                     |
| SCLK       | SPI Clock (SCK)       | Sense the clock                                     |
| SDI        | SPI MOSI              |                                                     |
