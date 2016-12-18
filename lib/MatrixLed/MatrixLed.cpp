#include "MatrixLed.h"

char color_buffer[64]; //final array

void initMatrix(){
    //----------SPI BUS SETUP----------
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);//Enable SPI HW, Master Mode, divide clock by 16

    //Set the pin modes for the RGB matrix
    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK,OUTPUT);
    pinMode(SLAVESELECT,OUTPUT);

    delay(10);

    //Make sure the RGB matrix is deactivated
    digitalWrite(SLAVESELECT,HIGH);
    //----------END SPI BUS SETUP----------

    delay(100);

    digitalWrite(SLAVESELECT, LOW); //Activate the RGB Matrix
    spi_transfer(0x25); //command character % == 0x25
    spi_transfer(0x02); //set LED matrix to position in daisy chain, must be between 0x01-0x08
    digitalWrite(SLAVESELECT, HIGH); //Deactivate the RGB Matrix

    //make sure buffer is cleared before writing to matrices
    clear_buffer();
}

void clear_buffer(){
    delay(10);

    for(int LED=0; LED<64; LED++){
        color_buffer[LED] = BLACK;
        delayMicroseconds(100);
    }

    delay(10);

    matrix_write();//write array of colors to matrix

    delay(10);//allow some time for the final matrix to be seen
}

//display array on the LED Matrix/daisy chained LED Matrices
void matrix_write(){
    delayMicroseconds(500);

    digitalWrite(SLAVESELECT, LOW); //Activate the RGB Matrix
    spi_transfer(0x26); //command char to reset frame index
    digitalWrite(SLAVESELECT, HIGH); //Deactivate the RGB Matrix

    delayMicroseconds(500);

    digitalWrite(SLAVESELECT, LOW); //Activate the RGB Matrix
    //Send the color buffer to the RGB Matrix
    delayMicroseconds(500);

    for(int LED=0; LED<64; LED++){
        spi_transfer(color_buffer[LED]);//send what is in buffer to the matrices
        delayMicroseconds(10);
    }

    delayMicroseconds(500);//allow some time for the serial data to be sent
    digitalWrite(SLAVESELECT, HIGH); //Deactivate the RGB Matrix
}

//Use this command to send a single color value to the RGB matrix.
//NOTE: You must send x number of color values to the RGB matrix
//      before it displays an image!
char spi_transfer(volatile char data){
    SPDR = data;                    // Start the transmission
    while (!(SPSR & (1<<SPIF))){
        // Wait for the end of the transmission
    };
    return SPDR;                    // return the received byte
}

int transition(int currentLogo, int sens)
{
    const int nbLogo = 4;
    int direct = -1;

    if(sens > 0)
    {
        direct = 1;
    }

    int numLogo = 0;

    if (sens > 0 && currentLogo == (nbLogo - 1)){
        numLogo = 0;
    } else if (sens == 0 && currentLogo == 0){
        numLogo = nbLogo - 1;
    } else {
        numLogo = currentLogo + direct;
    }

    clear_buffer();
    delay(100);
    switch (numLogo) {
        case 0:
            setMessageBuffer();
            break;
        case 1:
            setSmartphoneBuffer();
            break;
        case 2:
            setMusicBuffer();
            break;
        case 3:
            setCameraBuffer();
            break;
        default:
            setMusicBuffer();
            break;
    }
    delay(100);
    matrix_write();

    return numLogo;
}

void neutralFaceEyebrowNether(int color)
{
    clear_buffer();
    eyebrowNether(color);
    eye(color);
    mouthNeutral(color);
    matrix_write();
}

void neutralFaceEyebrowTop(int color)
{
    clear_buffer();
    eyebrowTop(color);
    eye(color);
    mouthNeutral(color);
    matrix_write();
}

void smileFaceEyebrowNether(int color)
{
    clear_buffer();
    eyebrowNether(color);
    eye(color);
    mouthSmile(color);
    matrix_write();

}

void smileFaceEyebrowTop(int color)
{
    clear_buffer();
    eyebrowTop(color);
    eye(color);
    mouthSmile(color);
    matrix_write();
}

void sadFaceEyebrowNether(int color)
{
    clear_buffer();
    eyebrowNether(color);
    eye(color);
    mouthSad(color);
    matrix_write();
}

void sadFaceEyebrowTop(int color)
{
    clear_buffer();
    eyebrowTop(color);
    eye(color);
    mouthSad(color);
    matrix_write();
}

void setSmartphoneBuffer()
{
    Serial.println("setSmartphoneBuffer");
    color_buffer[0]=WHITE;
    color_buffer[1]=WHITE;
    color_buffer[8]=WHITE;
    color_buffer[9]=WHITE;
    color_buffer[16]=WHITE;
    color_buffer[19]=WHITE;
    color_buffer[20]=WHITE;
    color_buffer[21]=WHITE;
    color_buffer[22]=WHITE;
    color_buffer[24]=WHITE;
    color_buffer[26]=WHITE;
    color_buffer[27]=WHITE;
    color_buffer[28]=ORANGE;
    color_buffer[29]=ORANGE;
    color_buffer[30]=WHITE;
    color_buffer[32]=WHITE;
    color_buffer[34]=WHITE;
    color_buffer[35]=WHITE;
    color_buffer[36]=ORANGE;
    color_buffer[37]=ORANGE;
    color_buffer[38]=WHITE;
    color_buffer[40]=WHITE;
    color_buffer[43]=WHITE;
    color_buffer[44]=WHITE;
    color_buffer[45]=WHITE;
    color_buffer[46]=WHITE;
    color_buffer[48]=WHITE;
    color_buffer[49]=WHITE;
    color_buffer[56]=WHITE;
    color_buffer[57]=WHITE;
}

void setMessageBuffer()
{
    Serial.println("setMessageBuffer");
    color_buffer[1]=BLUE;
    color_buffer[2]=WHITE;
    color_buffer[3]=WHITE;
    color_buffer[4]=WHITE;
    color_buffer[5]=WHITE;
    color_buffer[9]=WHITE;
    color_buffer[10]=BLUE;
    color_buffer[11]=WHITE;
    color_buffer[12]=WHITE;
    color_buffer[13]=WHITE;
    color_buffer[17]=WHITE;
    color_buffer[18]=WHITE;
    color_buffer[19]=BLUE;
    color_buffer[20]=WHITE;
    color_buffer[21]=WHITE;
    color_buffer[25]=WHITE;
    color_buffer[26]=WHITE;
    color_buffer[27]=BLUE;
    color_buffer[28]=WHITE;
    color_buffer[29]=WHITE;
    color_buffer[33]=WHITE;
    color_buffer[34]=WHITE;
    color_buffer[35]=BLUE;
    color_buffer[36]=WHITE;
    color_buffer[37]=WHITE;
    color_buffer[41]=WHITE;
    color_buffer[42]=WHITE;
    color_buffer[43]=BLUE;
    color_buffer[44]=WHITE;
    color_buffer[45]=WHITE;
    color_buffer[49]=WHITE;
    color_buffer[50]=BLUE;
    color_buffer[51]=WHITE;
    color_buffer[52]=WHITE;
    color_buffer[53]=WHITE;
    color_buffer[57]=BLUE;
    color_buffer[58]=WHITE;
    color_buffer[59]=WHITE;
    color_buffer[60]=WHITE;
    color_buffer[61]=WHITE;
}

void setMusicBuffer()
{
    Serial.println("setMusicBuffer");
    color_buffer[20]=WHITE;
    color_buffer[21]=WHITE;
    color_buffer[27]=WHITE;
    color_buffer[28]=WHITE;
    color_buffer[29]=WHITE;
    color_buffer[30]=WHITE;
    color_buffer[31]=WHITE;
    color_buffer[32]=WHITE;
    color_buffer[33]=WHITE;
    color_buffer[34]=WHITE;
    color_buffer[35]=WHITE;
    color_buffer[36]=WHITE;
    color_buffer[37]=WHITE;
    color_buffer[38]=WHITE;
    color_buffer[39]=WHITE;
    color_buffer[40]=WHITE;
    color_buffer[48]=WHITE;
}

void setCameraBuffer()
{
    color_buffer[0]=WHITE;
    color_buffer[1]=WHITE;
    color_buffer[2]=WHITE;
    color_buffer[3]=WHITE;
    color_buffer[4]=WHITE;
    color_buffer[5]=WHITE;
    color_buffer[6]=WHITE;
    color_buffer[7]=WHITE;
    color_buffer[8]=WHITE;
    color_buffer[9]=ORANGE;
    color_buffer[14]=WHITE;
    color_buffer[16]=WHITE;
    color_buffer[17]=ORANGE;
    color_buffer[22]=WHITE;
    color_buffer[23]=WHITE;
    color_buffer[24]=WHITE;
    color_buffer[27]=WHITE;
    color_buffer[28]=WHITE;
    color_buffer[30]=WHITE;
    color_buffer[31]=WHITE;
    color_buffer[32]=WHITE;
    color_buffer[35]=WHITE;
    color_buffer[36]=WHITE;
    color_buffer[38]=WHITE;
    color_buffer[39]=WHITE;
    color_buffer[40]=WHITE;
    color_buffer[46]=WHITE;
    color_buffer[48]=WHITE;
    color_buffer[54]=WHITE;
    color_buffer[56]=WHITE;
    color_buffer[57]=WHITE;
    color_buffer[58]=WHITE;
    color_buffer[59]=WHITE;
    color_buffer[60]=WHITE;
    color_buffer[61]=WHITE;
    color_buffer[62]=WHITE;
}

void eye(int color)
{
    color_buffer[9]=color; // oeil gauche
    color_buffer[49]=color; // oeil droit
}

void eyebrowTop(int color)
{
    color_buffer[63]=color; // sourcil gauche
    color_buffer[7]=color;
    color_buffer[15]=color;

    color_buffer[39]=color; // sourcil droit
    color_buffer[47]=color;
    color_buffer[55]=color;
}

void eyebrowNether(int color)
{
    color_buffer[0]=color; // sourcil gauche
    color_buffer[8]=color;
    color_buffer[16]=color;

    color_buffer[40]=color; // sourcil droit
    color_buffer[48]=color;
    color_buffer[56]=color;
}

void mouthNeutral(int color)
{
    color_buffer[13]=color; // bouche
    color_buffer[21]=color;
    color_buffer[29]=color;
    color_buffer[37]=color;
    color_buffer[45]=color;
    color_buffer[53]=color;
}

void mouthSmile(int color)
{
    color_buffer[12]=color; // bouche
    color_buffer[21]=color;
    color_buffer[30]=color;
    color_buffer[38]=color;
    color_buffer[20]=color;
    color_buffer[28]=color;
    color_buffer[29]=color;
    color_buffer[37]=color;
    color_buffer[36]=color;
    color_buffer[44]=color;
    color_buffer[52]=color;
    color_buffer[45]=color;
}

void mouthSad(int color)
{
    color_buffer[14]=color; // bouche
    color_buffer[21]=color;
    color_buffer[29]=color;
    color_buffer[37]=color;
    color_buffer[45]=color;
    color_buffer[54]=color;
}

void matrixIntro(int count)
{
    clear_buffer();
    int colors[] = {TEAL, RED, YELLOW, GREEN, BLUE, WHITE, ORANGE, MAGENTA};
    int i=0, j=0;
    while(count>0)
    {
        while(i!=63)
        {
            j = (1+j)%7;
            i = (1+i)%64;
            color_buffer[i]=colors[j];
            delay(1);
            matrix_write();
        }
        count=count-1; i=0; j=0; clear_buffer();
    }
    delay(100);
    clear_buffer();
    delay(100);
    matrix_write();
}
