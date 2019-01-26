# Sunbird

Version: rev11.

## Technical information

This is a board designed around an off-the-shelf ESP8266 ESP-12(E|F|S) module.

### Component choices

 * [ESP8266](./docs/esp8266ex.pdf) single-core 160Mhz 32 bit microcontroller with Wifi, 32K RAM and 4MB ROM as main CPU.
 * 2x 5050 RGB notification LEDs on either side of the PCB at the rear end
 * USB C charge and programming port.
 * [CH340g](./docs/CH340DS1.pdf) USB UART controller, with automatic reset circuitry for programming CPU.
 * [FS312F-G](./docs/FS312F-G-DS-10_EN.pdf) (and associated double-mosfet) short circuit protection circuitry. This also provides overcharge/overdischarge protection
 * [TP4056](./docs/TP4056.pdf) li-ion battery charger circuit. CHRG and STDBY signals passed through to CPU.
 * [ADXL345](./docs/ADXL345.pdf) Accellerometer for smart-power-off and usage detection using i2c bus with interrupt line.
 * [FM116B](./docs/FM116B.pdf) motor driver H-bridge IC. Warning: Datasheet almost entirely in Chinese.
 * Integrated 500mA fuse on PCB.
 * Standardised around 0603 size components where possible.
 * [Tag-Connect TC2030 no-legs](http://www.tag-connect.com/TC2030-MCP-NL) zero-pcb-parts connector used for programming and debugging before the CH340G is brought up, and for diagnosis when the CH340G is not populated, or otherwise unavailable due to failure.

### Technical features

 * Ability to field-program in-situ using USB bus.
 * Ability to OTA (Over The Air) program device.
 * Ability to sample battery voltage without incurring passive current draw, using 2 high-resistence resistors and a single transitor to enable battery sampling.
 * Ability to run while charging battery.
 * Ability to show status using RGB colour LED on both sides of circuit board.

### Known issues
 * 3.3v regulator has been problematic so far. Hopefully resolved in rev11.
 * 5050 RGB LEDs don't have consistent pinout of which colour channel is on which pin, meaning the value of R8020-22 are unpredictable, and subject to change before assembly. I have debated using WS2812B or similar as a replacement, but increasing parts cost and program complexity deterred me.

## PCB
![Render][images/3d.png]
![PCB view][images/pcb.png]

## Schematics

### Processor
![Processor][images/processor.png]

### Battery Charger Circuit
![Battery Charger][images/battery_charger.png]

### Power Regulator
![Power Regulator][images/power_regulator.png]

### Motor Driver
![Motor Driver][images/motor_driver.png]

### USB UART
![USB UART][images/usb_uart_ch340g.png]


