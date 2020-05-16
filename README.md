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
	POWEROFF	6

WS2812b LED (5v)
	DATA		8

DFPlayer (5v)
	RX		2
	TX		3

433mhz Transmitter (3v)
	RX		4
	TX		7
	PPT		5

RFID (3v)
	RST   		9
	SDA  		10
	MOSI 		11
	MISO 		12
	SCK 		13
