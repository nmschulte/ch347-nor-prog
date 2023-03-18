# Simple CH347 ~~SPI-NOR programmer~~ Infineon TLE920x Diagnosis Commander

Infineon TLE9201/TLE9202 Diagnosis Commander software for WCH CH347 USB 2.0 High-speed USB to UART+SPI+I2C bridge using libusb.

Forked from [ch347-nor-prog](https://github.com/981213/ch347-nor-prog) by Chuanhong Guo.
Based on [ch341prog](https://github.com/hackpascal/ch341prog) by Hackpascal.

Tested under linux. It should work under Windows with winusb driver installed but I haven't tried it yet.

## Performance

The maximum SPI frequency supported by this chip is 60MHz and it can achieve a read speed of about 4950KB/s.

Pretty impressive for a 32CNY board :)
