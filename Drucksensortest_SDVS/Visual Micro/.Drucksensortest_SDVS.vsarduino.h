/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Teensy 3.1, Platform=avr, Package=teensy
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define _VMDEBUG 1
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 96000000
#define USB_SERIAL
#define LAYOUT_US_ENGLISH
#define __cplusplus
#define __MK20DX256__
#define TEENSYDUINO 118
#define __extension__
#define  __attribute__(x)
#define __builtin_va_list


//
//
void getSensorData();
void log2SD();
void SelectChannel (int channel);

#include "C:\Program Files (x86)\Arduino\hardware\teensy\cores\teensy3\arduino.h"
#include "D:\Dropbox\Akaflieg\AK_Logger\Drucksensortest_SDVS\Drucksensortest_SDVS.ino"
#include "D:\Dropbox\Akaflieg\AK_Logger\Drucksensortest_SDVS\resource.h"
#endif
