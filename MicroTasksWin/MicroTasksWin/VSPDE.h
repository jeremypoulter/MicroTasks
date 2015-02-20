//--------------------------------------------------------------------
// Arduino Console Stub
//--------------------------------------------------------------------

#if _MSC_VER 

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Add CPU hardware definitions

#define _AVR_IO_H_
#define _SFR_IO8(io_addr) ((io_addr))
#include "avr\iomxx0_1.h"

#define boolean bool



// From "C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\include\stdint.h"

/* doxygen gets confused by the __attribute__ stuff */

/** \name Exact-width integer types
    Integer types having exactly the specified width */

/*@{*/

/** \ingroup avr_stdint
    8-bit signed type. */

typedef signed char int8_t;

/** \ingroup avr_stdint
    8-bit unsigned type. */

typedef unsigned char uint8_t;

/** \ingroup avr_stdint
    16-bit signed type. */

typedef signed int int16_t;

/** \ingroup avr_stdint
    16-bit unsigned type. */

typedef unsigned int uint16_t;

/** \ingroup avr_stdint
    32-bit signed type. */

typedef signed long int int32_t;

/** \ingroup avr_stdint
    32-bit unsigned type. */

typedef unsigned long int uint32_t;

/** \ingroup avr_stdint
    64-bit signed type.
    \note This type is not available when the compiler
    option -mint8 is in effect. */

typedef signed long long int int64_t;

/** \ingroup avr_stdint
    64-bit unsigned type.
    \note This type is not available when the compiler
    option -mint8 is in effect. */

typedef unsigned long long int uint64_t;
/** \name Exact-width integer types
Integer types having exactly the specified width */

/*@{*/

/** \ingroup avr_stdint
8-bit signed type. */

typedef signed char int8_t;

/** \ingroup avr_stdint
8-bit unsigned type. */

typedef unsigned char uint8_t;

/** \ingroup avr_stdint
16-bit signed type. */

typedef signed int int16_t;

/** \ingroup avr_stdint
16-bit unsigned type. */

typedef unsigned int uint16_t;

/** \ingroup avr_stdint
32-bit signed type. */

typedef signed long int int32_t;

/** \ingroup avr_stdint
32-bit unsigned type. */

typedef unsigned long int uint32_t;

/** \ingroup avr_stdint
64-bit signed type.
\note This type is not available when the compiler
option -mint8 is in effect. */

typedef signed long long int int64_t;

/** \ingroup avr_stdint
64-bit unsigned type.
\note This type is not available when the compiler
option -mint8 is in effect. */

typedef unsigned long long int uint64_t;


// From "c:\program files\arduino\hardware\cores\arduino\print.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0

// From "c:\program files\arduino\hardware\cores\arduino\wiring.h"

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1

#define PI 3.14159265
#define HALF_PI 1.57079
#define TWO_PI 6.283185
#define DEG_TO_RAD 0.01745329
#define RAD_TO_DEG 57.2957786

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define INTERNAL 3
#define DEFAULT 1
#define EXTERNAL 0

class CSerial
{
public:
  void begin(long);

  void print(char*);
  void print(int, int = DEC);

  void println();
  void println(char*);
  void println(int, int = DEC);
  void println(unsigned int, int = DEC);
  void println(unsigned long, int = DEC);
  int available();
  char read();

  // VSPDE
  void _append(char c);
private:
  char buffer[1024];
  int buflen;
};

extern CSerial Serial;
extern unsigned long millis();
extern void delay(unsigned long);
extern void pinMode(int, int);
extern void digitalWrite(int, int);
extern bool digitalRead(int);
extern void attachInterrupt(uint8_t, void(*)(void), int mode);
extern void detachInterrupt(uint8_t);

// WMath prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned int);
long map(long, long, long, long, long);

#endif