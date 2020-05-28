# MagicBand
Arduino base Magicband Doorbell and RFID reader

Very much a work in progress at this stage as still waiting after nearly 8 weeks for some parts to arrive from China to test/complete.

The idea was to produce a doorbell that looked similar to the Disney MagicBand readers for my house. It will include a 433mhz transmitter which I intend to send a signal to my RFXCOM receiver connected to my home automation server to play some Haunted Mansion music.

Video of it while in build mode.
https://www.youtube.com/watch?v=pBCrjpx0mSs

Components
Arduino nano 5v (but will run down to 2.8 so Lipo ok to power via 5v rail
TPL5110 5v (but runs on lipo)
433mhz Transmitter 3v rail
RFID Reader 3v rail
DFPlayer 3.2-5 (let's take the 5v rail)
Batteries 2 x 18650 in parallel for long life


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

I had problems with the TPL5110 whereby when you pressed the button it would rapidly blink, this was resolved after placing a 22uf cap across the VIN/DRV pins

Tag
Card UID: C9 FB 87 59

Card
Card UID: 9E 13 64 31


