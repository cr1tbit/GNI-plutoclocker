# GNI-plutoclocker

![Alt text](images/3d-view.png?raw=true "Board 3d view")

This device serves a couple of roles:
* allowing clocking adalm-pluto by an external clock source of broad frequency range
* injecting clock signal into RF trace, for clocking modded LNB
* supplying LNB with DC voltage (12v/18v selectable with an external switch)
* additional clock output

The device is based on CDCE913 which is a neat 3-output clock source generator. It has an excillent, low jitter PLL inside, and has been tested to work well with an OCXO for the purpose of communication via OSCAR-100 satellite.

## Configuration

The device is programmed via I2C rail. The proper register values may be programmed, using an arduino sketch ( available in this repo).

![Alt text](images/GNI-plutoclocker-photo.jpg?raw=true "Board 3d view")

More about this project may be found on https://hf5l.pl/en/adalm-pluto-clocker-2/
