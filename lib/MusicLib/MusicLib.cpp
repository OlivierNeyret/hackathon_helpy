#include "MusicLib.h"

SoftwareSerial mySerial(ARDUINO_RX, ARDUINO_TX);

static int8_t Send_buf[8] = {0} ;

void sendCommand(int8_t command, int16_t dat)
{
    delay(20);
    Send_buf[0] = 0x7e; //starting byte
    Send_buf[1] = 0xff; //version
    Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
    Send_buf[3] = command; //
    Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
    Send_buf[5] = (int8_t)(dat >> 8);//datah
    Send_buf[6] = (int8_t)(dat); //datal
    Send_buf[7] = 0xef; //ending byte
    for(uint8_t i=0; i<8; i++)//
    {
        mySerial.write(Send_buf[i]) ;
    }
}

void musicInit()
{
    mySerial.begin(9600);
    delay(500);//Wait chip initialization is complete
    sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card
    delay(200);//wait for 200ms
}
void playMessage()
{
    sendCommand(CMD_PLAY_W_VOL, 0X1E01);
}

void playRepondeur()
{
    sendCommand(CMD_PLAY_W_VOL, 0X1E02);
}

void playMusic()
{
    sendCommand(CMD_PLAY_W_VOL, 0X1E03);
}

void musicPause()
{
    sendCommand(CMD_PAUSE, 0X0E);
}
