//Board = Arduino Mega 2560
#define ARDUINO 23
#define __AVR_ATmega2560__
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
#define __attribute__(x)
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__
#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define prog_void
#define PGM_VOID_P int
#define NOINLINE __attribute__((noinline))

typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {}

//already defined in arduno.h
//already defined in arduno.h
void motorLeft_foward(int leftpwm);
void motorLeft_reverse(int leftpwm);
void motorRight_foward(int rightpwm);
void motorRight_reverse(int rightpwm);
void motorLeft_stop();
void motorRight_stop();
void moveForward(int leftpwm,int rightpwm);
void turnRight(int pwm);
void turnLeft(int pwm);
void rotateClockwise(int leftpwm,int rightpwm);
void rotateAntiClockwise(int leftpwm,int rightpwm);
void stop();
void serialTest();

#include "E:\Electronic\Softwares\Arduino Setup\arduino-0023\hardware\arduino\cores\arduino\wprogram.h"
#include "D:\Robotics\iNexus 2013\Programing\Robo-1 Autonomous\Test Codes\PID\ex2\ex2.pde"
