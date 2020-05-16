/*#include "uTFT_ST7735.h"

#define RESET 0
#define INIT 1
#define RUN 2

void myDelay(int16_t ms);

bool newValue = false, updateFlag = false;

int currentState = RESET;

void receiveNewPixel() {
  newValue = PINB & 0b0001;
  updateFlag = true;
}

uint8_t readRules() {
  uint8_t res = 0, mult = 1;
  //interfacing with the 74HC165 shift register
  //step 1: load values
  PORTA |= (1 << 2);
  myDelay(5);
  PORTA &= ~(1 << 2);
  myDelay(5);
  
  //step 2: read value and shift to next bit
  for(int i = 0; i < 8; i++)
  {
    res += (PINA & 1) * mult;
    mult *= 2;

    PORTA |= (1 << 1);
    myDelay(5);
    PORTA &= ~(1 << 1);
    myDelay(5);    
  }

  return res;
}

void setup() {
  // init ports
  // PA0, PA3 in | PA1, PA2 out | PA4, PA5, PA6 uTFT | PA7 vacant
  // enable pullups for now
  DDRA = 0b01110110;
  PORTA = 0b10001101;

  // PB0, PB1, PB2 in | PB3 uTFT
  // enable pullups for now
  DDRB = 0b1000;
  PORTB = 0b0111;
  
  // init screen
  // ATTINY84 profile, ST7735, 128*128 1.44" TFT display
  ////init();
  ////fillScreen(Color565(0,0,0));

  //attach interrupt on pin PB2
  attachInterrupt(PB2, receiveNewPixel, RISING);
}

void loop() {
  
  //check for state changes
  if(PINB & 0x0010 == false)
    currentState = RESET;
  else if(PINA & 0x00001000 == true)
    currentState = INIT;
  else
    currentState = RUN;

  //perform operations for each state
  if(currentState == RESET)
  {
    //clear screen
  }
  else if(currentState == INIT)
  {
    //read the current rule number and show on the screen
    //something = readRules();
  }
  else
  {
    if(updateFlag == true)
    {
      updateFlag = false;

      //add a new pixel to screen
    }
  }
}
*/

#include <SPI.h>
#include "Ucglib.h"

#define RESET 0
#define INIT 1
#define RUN 2
#define INITWAIT 3

#define ORIGIN_X 10
#define ORIGIN_Y 45

#define DEF_DRAW_X 126
#define DEF_DRAW_Y 70

bool newValue = false, updateFlag = false;

int currentState = RESET;
int posX, posY;

Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 9, /*cs=*/ 10, /*reset=*/ 8);

void receiveNewPixel() {
  newValue = (PIND & 0b00000100) >> 2;
  updateFlag = true;
}

uint8_t readRules() {
  uint8_t res = 0, mult = 128;
  //interfacing with the 74HC165 shift register
  //step 1: load values
  PORTC &= ~(1 << 2);
  //delay(5);
  PORTC |= (1 << 2);
  //delay(5);
  
  //step 2: read value and shift to next bit
  for(int i = 0; i < 8; i++)
  {
    res += (PINC & 1) * mult;
    mult /= 2;

    PORTC |= (1 << 1);
    //delay(5);
    PORTC &= ~(1 << 1);
    //delay(5);    
  }

  return res;
}

void attemptStateChange() {
  
  //check for state changes
  if(currentState == RUN && (PIND & 0b00010000) == 0)
    currentState = RESET;
  else if(currentState == RESET)
    currentState = INITWAIT;
  else if(currentState == INITWAIT && (PINC & 0b0001000) == 0b0001000)
    currentState = INIT;
  else if(currentState == INIT)
    currentState = RUN; 
}

void setup() {
  // init ports
  // PC0, PC3 in | PC1, PC2 out | PC6 reserved | PC4 - PC5 vacant
  // enable pullups for now
  DDRC |= 0b0000110;
  DDRC &= ~(0b0001001);
  PORTC |= 0b0001101;
  PORTC &= ~(0b0000010);

  // PD2 - PD4 in | PD0, PD1 reserved | PD5 - PD7 vacant
  // enable pullups for now
  DDRD &= ~(0b00011100);
  PORTD |= 0b00011100;
  
  // init screen
  // ATMEGA328P profile, ST7735, 128*160 1.8" TFT display
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_ncenR08_hr);
  ucg.setRotate180();
  ucg.clearScreen();

  delay(5);
  ucg.setPrintPos(ORIGIN_X, ORIGIN_Y);    //this is the upper-left corner of the screen
  ucg.print("Initialized");
  delay(200);

  //attach interrupt on pin PD3
  attachInterrupt(1, receiveNewPixel, RISING);
}

void loop() {

  //perform operations for each state
  if(currentState == RESET)
  {
    //clear screen
    ucg.clearScreen();

    //make background white
    ucg.setColor(255, 255, 255);
    ucg.drawBox(0, 0, ucg.getWidth(), ucg.getHeight());

    //put required text in
    ucg.setColor(0, 0, 0);
    ucg.setPrintPos(ORIGIN_X, ORIGIN_Y);
    ucg.print("Current Rule: ");

    //reset drawing location
    posX = DEF_DRAW_X;
    posY = DEF_DRAW_Y;

    //set drawing color
    ucg.setColor(255, 0, 0);

    attemptStateChange();
  }
  else if(currentState == INIT)
  {
    //read the current rule number and show on the screen
    ucg.print(readRules());

    //draw the initial bit on the center of first line
    ucg.drawBox(posX-60, posY-2, 2, 2);

    attemptStateChange();
  }
  else
  {
    if(updateFlag == true)
    {
      //clear flag
      updateFlag = false;

      //set draw position and draw if newValue is true
      if(newValue == 1)
        ucg.drawBox(posX, posY, 2, 2);

      //move to next drawing location
      posX-=2;

      if(posX < 0)
      {
        posX = DEF_DRAW_X;
        posY+=2;
      }
    }
    
    attemptStateChange();
    delay(5);
  }
}
