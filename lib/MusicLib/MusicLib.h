#ifndef MusicLib_h
#define MusicLib_h

#include <Arduino.h>
#include <SoftwareSerial.h>

#define ARDUINO_RX 5//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 6//connect to RX of the module

#define CMD_SEL_DEV 0X09
#define DEV_TF 0X02
#define CMD_PLAY_W_VOL 0X22
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PREVIOUS 0X02
#define CMD_NEXT 0X01

void sendCommand(int8_t command, int16_t dat);
void musicInit();
void playMusic();
void playRepondeur();
void playMessage();
void musicPause();

#endif
