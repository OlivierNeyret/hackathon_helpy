#ifndef MatrixLed_h
#define MatrixLed_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#include "WConstants.h"
#endif

//Define the "Normal" Colors
#define BLACK   0x00
#define RED     0xE0
#define GREEN   0x1C
#define BLUE    0x03
#define YELLOW  RED|GREEN
#define ORANGE  0xFC
#define MAGENTA RED|BLUE
#define TEAL    BLUE|GREEN
#define WHITE   (RED|GREEN|BLUE)-0xA0

//Define the SPI Pin Numbers
#define SLAVESELECT 10//ss
#define DATAOUT     11//MOSI
#define DATAIN      12//MISO
#define SPICLOCK    13//sck

extern char color_buffer[64];

void initMatrix();
int transition(int currentLogo, int sens);

void clear_buffer();
void matrix_write();
char spi_transfer(volatile char data);
void neutralFaceEyebrowNether(int color);
void neutralFaceEyebrowTop(int color);
void smileFaceEyebrowNether(int color);
void smileFaceEyebrowTop(int color);
void sadFaceEyebrowNether(int color);
void sadFaceEyebrowTop(int color);
void setSmartphoneBuffer();
void setMessageBuffer();
void setMusicBuffer();
void setCameraBuffer();
void eye(int color);
void eyebrowTop(int color);
void eyebrowNether(int color);
void mouthNeutral(int color);
void mouthSmile(int color);
void mouthSad(int color);
void matrixIntro(int count);

#endif
