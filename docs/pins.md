# Pins

## Board Pin Routing

How the feather and micro:bit pins have been connected together.

| Feather left | micro:bit pin | | Feather right | micro:bit pin |
|--------------|---------------|-|---------------|---------------|
| RST          | Not connected | |               |               |
| 3.3V         | 3V            | |               |               |
| -            |               | |               |               |
| GND          | GND           | |               |               |
| -            |               | | -             |               |
| -            |               | | -             |               |
| -            |               | | -             |               |
| -            |               | | C Button      | P2            |
| -            |               | | B Button      | P1            |
| -            |               | | A Button      | P0            |
| SCK          | P13 (SCK)     | | D/C           |               |
| MO           | P15 (MOSI)    | | ECS           |               |
| MI           | P14 (MISO)    | | SRCS          |               |
| -            |               | | SDCS          |               |
| -            |               | | -             |               |
| -            |               | | -             |               |

Feather pins:
- RST - Connected to the Reset button in the eInk feather
- SCK - SPI Clock
- MO - SPI MOSI from microcontroller to feather
- MI - SPI MISO from feather to microcontroller
- Button A/B/C - Connected to the three top button in the feather
- D/C - The eInk Data/Command pin, required for controlling the display
- ECS - Eink SPI Chip Select
- SRCS - SRAM SPI Chip Select
- SDCS - SD Card SPI Chip Select

eInk feather pinout from:
https://learn.adafruit.com/adafruit-eink-display-breakouts/pinouts-2


## Pinouts 

### micro:bit V2 pinout

From: https://tech.microbit.org/hardware/edgeconnector/#edge-connector-pins

![micro:bit pinout](img/edge-connector-2.svg)

### Feather pinout

This is the generic feather pinout, which might change slightly depending on
the board. From:
https://learn.adafruit.com/adafruit-feather/feather-specification#pin-naming-3096825-19

| Feather left header | Feather right header |
|---------------------|----------------------|
| Rst  |      |
| 3.3V |      |
| Aref |      |
| GND  |      |
| A0   | Bat  |
| A1   | En   |
| A2   | VUSB |
| A3   | D13  |
| A4   | D12  |
| A5   | D11  |
| SCK  | D10  |
| MO   | D9   |
| MI   | D6   |
| RX   | D5   |
| TX   | SCL  |
| GND  | SDA  |

