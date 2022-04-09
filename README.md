Please see the full documentation at http://spaniakos.github.io/ArduinoDES

ArduinoDES
==========

DES and Triples DES encryption and decryption library for the Arduino microcontroller platform.
This code was ported from the AVR-Crypto-Lib (http://www.das-labor.org/wiki/AVR-Crypto-Lib).

Arduino IDE
-----------

To install the library, download and copy the files into a subfolder (e.g. "DES") in the 
"libraries" folder of your Arduino development environment.

The library was tested on an Arduino Leonardo and works on an Intel Galileo board, too (thanks spaniakos).


PlatformIO
----------

To use this library in a PlatformIO project, add this repository's url to the list of `lib_deps` in `platformio.ini`.
Make sure to use `framework = arduino`:

```
framework = arduino
lib_deps =
    https://github.com/Octoate/ArduinoDES.git
```


Usage
=====

It is possible to encrypt and decrypt messages with the DES or Triples DES crypto algorithms.
Have a look at the example code for more information.

### Raspberry  pi
install
```
sudo make install
cd examples_Rpi
make
```

What to do after changes to the library
```
sudo make clean
sudo make install
cd examples_Rpi
make clean
make
```

What to do after changes to a sketch
```
cd examples_Rpi
make <sketch>

or 
make clean
make
```

How to start a sketch
```
cd examples_Rpi
sudo ./<sketch>
```



License
=======

Library for DES and 3DES encryption and decryption
Ported to the Arduino platform 2013 by Tim Riemann

Original version taken from the AVR-Crypto-Lib
(http://www.das-labor.org/wiki/AVR-Crypto-Lib)
Copyright (C) 2006-2010  Daniel Otte (daniel.otte@rub.de)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
