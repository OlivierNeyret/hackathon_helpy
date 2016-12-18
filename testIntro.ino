//Example_RGBMatrix.ino
//By: Ryan Owens @ SparkFun Electronics
// 
//modified 27 Oct 2014
//by Bobby Chan @ SparkFun Electronics

// This is example code to output an array to 
// the RGB Serial Backpack Matrix and set the position of
// a daisy chained matrix.

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

//Define final array to output to LED Matrices (maximum of 8 matrices daisy chained)
//Ex.) if you have 1 matrix, you have an array of 64=64*1
//     if you have 2 matrices, you have an array of 128=64*2
//     if you have 3 matrices, you have an array of 194=64*3
const int num_matrix = 1; //define number of daisy chained matrices
char color_buffer[64*num_matrix]; //final array

//array to clear 1 matrix
char blank[]={
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK
};

//set LED Matrix Value for daisy chained LED Matrices
//maximum of 8 daisy chained LED Matrices
void set_matrix(){
    digitalWrite(SLAVESELECT, LOW); //Activate the RGB Matrix
    spi_transfer(0x25); //command character % == 0x25
    spi_transfer(0x02); //set LED matrix to position in daisy chain, must be between 0x01-0x08
    digitalWrite(SLAVESELECT, HIGH); //Deactivate the RGB Matrix
}

int p = 0; //dot position
int xMAX = 8;//max number column in 1 subset
int yMAX = 8;//max number row in 1 subset

void clear_buffer(){
    //start clearing array moving down rows
    for(int y=0; y<yMAX; y++){
        //clear array from the highest subset in daisy chained array
        for(int i=num_matrix; i>0; i--){
            //clear array from right to left
            for(int x=0; x<xMAX; x++){
                //current position that is being cleared
                p = (yMAX*y) + (x + (i-1)*(xMAX*yMAX));
                //clear by saving what is in the blank sub-array to your final array
                color_buffer[p] = blank[x];
            }
        }
    }
    matrix_write();//write array of colors to matrix
    delay(10);//allow some time for the final matrix to be seen  
}

void setup(){  
    //----------SPI BUS SETUP----------
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);	//Enable SPI HW, Master Mode, divide clock by 16

    //Set the pin modes for the RGB matrix
    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK,OUTPUT);
    pinMode(SLAVESELECT,OUTPUT);

    //Make sure the RGB matrix is deactivated
    digitalWrite(SLAVESELECT,HIGH); 
    //----------END SPI BUS SETUP----------

    //use this to set a LED Matrix to position in daisy chain
    //set_matrix();
    intro(5);
    delay(100);
    clear_buffer();
}

void loop(){
}

//display array on the LED Matrix/daisy chained LED Matrices
void matrix_write(){
    digitalWrite(SLAVESELECT, LOW); //Activate the RGB Matrix
    spi_transfer(0x26); //command char to reset frame index
    digitalWrite(SLAVESELECT, HIGH); //Deactivate the RGB Matrix

    digitalWrite(SLAVESELECT, LOW); //Activate the RGB Matrix
    //Send the color buffer to the RGB Matrix
    delayMicroseconds(1500);

    for(int LED=0; LED<(64*num_matrix); LED++){
        spi_transfer(color_buffer[LED]);//send what is in buffer to the matrices
    }
    delayMicroseconds(1500);//allow some time for the serial data to be sent 
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

void intro(int count)
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
}
