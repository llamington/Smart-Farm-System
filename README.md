# Smart Farm System
## Project Files
[Data Broker Board](https://easyeda.com/lissington4/smart-farm-schematic-data-broker)

[Sensor Subsystem Board](https://easyeda.com/lissington4/smart-farm-schematic)

## Programming Board:
1. Insert FTDI board
   * If Data Broker select 5V
   * If Sensor Subsystem select 3.3V
2. Ensure Jumpers are selected to 'PROG' mode for programming
3. Plug in Battery to Sensor Subsystem
4. Ensure Arduino IDE COM port is correctly selected
5. Ensure 'Board:' is set to:
   * 'Arduino Pro or Pro Mini' (Sensor Subsystem)
   * 'Arduino/Genuino Uno'  (Data Broker)
6. Ensure 'Processor:' is set to 'ATmega328P (3.3V, 8MHz)' for Data Broker
7. Ensure 'Programmer:' is set to 'AVRISP mkII'
8. The board's reset button may have to be pressed while pressing 'Upload Sketch'
## Documentation
* [Executive Summary](https://docs.google.com/document/d/1e9hxD1EgtwhdI2ElwgMCJGJI10CNnTmsidURxNL1KP8/edit?usp=sharing)
* [Report](https://docs.google.com/document/d/1hib91_5W7olT_gy1vOQjhlBxqv88XaVicgFhEBmSrUQ/edit?usp=sharing)
* [Bill of Materials](https://docs.google.com/spreadsheets/d/1ZyjLawHQprvmQZ0Cbc97jp_R3VOazbsFH6kYA6FA8nM/edit?usp=sharing)
## Datasheets
* [Bosch BME280](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf)
* [Ebyte E22-900T30S](http://www.ebyte.com/en/downpdf.aspx?id=485)
* [Atmel ATMEGA328P](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
* [Ai-Thinker ESP-12F](http://file.elecfans.com/web1/M00/91/F3/o4YBAFzdEFaAKJx0ABJWYqWPp88163.pdf?filename=ESP-12F%28ESP8266MOD%29_Ai-Thinker.pdf)
## Flashing Bootloader
1. Install [Zadig](https://zadig.akeo.ie/)
2. Plug USPasp into computer, with J21 placed in 3.3V while the other jumpers are empty
3. Ensure 'Options>List all Devices' is selected
4. Select 'USBasp' within the USB selection box
5. Replace driver with 'libusb-win32'
6. Install [AVRDUDESS](https://blog.zakkemble.net/avrdudess-a-gui-for-avrdude/)
7. 'Detect' MCU and ensure ATMEGA328P is detected
8.

## Notes
* Sensor Subsystem is currently sending strings over serial. The data is innacurate but readable
* Charging the battery by USB consists of plugging the battery in to 'BAT' and plugging the USB into a source.
* If boards not in sync then ensure battery holder is making connection
* If BME280 is not soldered directly to the board the address may have to be changed from 0x76
