# MagicBand
Arduino base Magicband Doorbell and RFID reader

Very much a work in progress at this stage as still waiting after nearly 8 weeks for some parts to arrive from China to test/complete.

The idea was to produce a doorbell that looked similar to the Disney MagicBand readers for my house. It will include a 433mhz transmitter which I intend to send a signal to my RFXCOM receiver connected to my home automation server to play some Haunted Mansion music.

Video of it while in build mode.
https://www.youtube.com/watch?v=pBCrjpx0mSs
https://www.youtube.com/watch?v=BiTqXcxttCY

Components
Arduino nano 5v (but will run down to 2.8 so Lipo ok to power via 5v rail
*TPL5110 5v (but runs on lipo)
433mhz Transmitter 3v rail
RFID Reader 3v rail
DFPlayer 3.2-5 (let's take the 5v rail)
Batteries 2 x 18650 in parallel for long life

subsequent to the build video's I've replaced the TPL5110 with an adafruit Power button https://www.adafruit.com/product/1400
This was a straight swap, had a bigger button area and removed the need of a rather sketchy desoldering of one of the TPLl5110 legs (pin 6), isolating from vcc and connecting to ground in order to get it to work in 'One Shot' mode. Similar power consumption in standby of only 0.5uA so long life for battery.This does sit higher so dremeled the plastic to fit else when screwed together it would have been continually pressed. You may want to consider modifying the stl files if using this instead as it's 4mm higher


Pin Out
TPL5110 (5v)
	POWEROFF	6 - Yellow

WS2812b LED (5v)
	DATA		8 - Orange

DFPlayer (5v)
	RX		2 - Yellow
	TX		3 - Orange

433mhz Transmitter (3v)
	RX		4
	TX		7 - Blue
	PPT		5

RFID (3v)
	RST   		9  - Green
	SDA  		10 - Blue
	MOSI 		11 - White
	MISO 		12 - Yellow
	SCK 		13 - Orange

I had problems with the TPL5110 whereby when you pressed the button it would rapidly blink, this was resolved after placing a 22uf cap across the VIN/DRV pins. (Not required if replacing with the adafruit power button mentioned earlier)


usbasp
368old bootloader
ch340 driver for non fdti chip knock off

this one works
https://www.aliexpress.com/item/33020752786.html

this one doesn't
https://www.aliexpress.com/item/32899642573.html
