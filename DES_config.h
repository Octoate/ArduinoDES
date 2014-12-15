#ifndef __DES_CONFIG_H__
#define __DES_CONFIG_H__

#define DES_PRINT
//#define DES_DEBUG

#if  (defined(__linux) || defined(linux)) && !defined(__ARDUINO_X86__)

  #define DES_LINUX

  #pragma GCC diagnostic ignored "-Wformat"
  #pragma GCC diagnostic ignored "-Wformat-contains-nul" 
  #include <stdint.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <sys/time.h>
  #include <unistd.h> 
#else
  #include <Arduino.h>
#endif

#include <stdint.h>
#include <string.h>

#if defined(__ARDUINO_X86__) || (defined (__linux) || defined (linux))
	#undef PROGMEM
	#define PROGMEM __attribute__(( section(".progmem.data") ))
	#define pgm_read_byte(p) (*(p))
	typedef unsigned char byte;
	#define printf_P printf
	#define PSTR(x) (x)
#else
	#include <avr/pgmspace.h>
#endif

#endif
