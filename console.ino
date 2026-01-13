#include <vector>
#include <unordered_map>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int blueButton = 2;
int b_buttonState = 0;

const int redButton = 3;
int r_buttonState = 0;

const int whiteButton = 8;
int w_buttonState = 0;

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char Logo[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00,
  0x00, 0x00, 0x0f, 0xc0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x01, 0xf0, 0x00, 0x00,
  0x00, 0x00, 0x3c, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x3c, 0x00, 0x00,
  0x00, 0x00, 0xf0, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x0e, 0x00, 0x00,
  0x00, 0x01, 0xc0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0x00, 0x00,
  0x00, 0x03, 0x80, 0x00, 0x00, 0x13, 0x80, 0x00, 0x00, 0x03, 0x98, 0x00, 0x00, 0x23, 0x80, 0x00,
  0x00, 0x07, 0x0e, 0x00, 0x38, 0x23, 0x80, 0x00, 0x00, 0x07, 0x06, 0x06, 0x30, 0x23, 0xc0, 0x00,
  0x00, 0x07, 0x03, 0x06, 0x30, 0x21, 0xc0, 0x00, 0x00, 0x07, 0x07, 0x8e, 0x30, 0x21, 0xc0, 0x00,
  0x00, 0x07, 0x07, 0x8e, 0x30, 0x21, 0xc0, 0x00, 0x00, 0x07, 0x05, 0xd6, 0x30, 0x21, 0xc0, 0x00,
  0x00, 0x07, 0x04, 0xf7, 0x30, 0x21, 0xc0, 0x00, 0x00, 0x07, 0x04, 0xe7, 0x30, 0x21, 0xc0, 0x00,
  0x00, 0x07, 0x04, 0x63, 0x18, 0x41, 0xc0, 0x00, 0x00, 0x07, 0x8c, 0x43, 0x0c, 0xc3, 0x80, 0x00,
  0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x00, 0x00, 0x03, 0x80, 0x01, 0x80, 0x03, 0x80, 0x00,
  0x00, 0x03, 0xc0, 0x00, 0x60, 0x07, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x0f, 0x00, 0x00,
  0x00, 0x01, 0xe0, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x1e, 0x00, 0x00,
  0x00, 0x00, 0x78, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x78, 0x00, 0x00,
  0x00, 0x00, 0x1f, 0x03, 0x81, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0xf7, 0xe0, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xc2, 0x08, 0x44, 0x8c, 0x90, 0xc8, 0x00, 0x00, 0xe7, 0x18, 0xc0, 0x8c, 0x9c, 0xc8, 0x00,
  0x00, 0xe7, 0x0c, 0xc0, 0xcc, 0x9e, 0xcc, 0x00, 0x00, 0xbb, 0x2c, 0xc0, 0x8c, 0x99, 0xc8, 0x00,
  0x00, 0x93, 0x26, 0xc0, 0x8c, 0x98, 0xc8, 0x00, 0x01, 0x93, 0x46, 0x64, 0xcc, 0x98, 0x4d, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char BirdIcon[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x09,
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x7c, 0x00,
  0x00, 0x00, 0x00, 0x18, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x70, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x22, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
  0x22, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x22, 0x00,
  0x00, 0x00, 0x00, 0x10, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x00, 0x40, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x60, 0x10,
  0x00, 0x00, 0x00, 0x08, 0x07, 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x38, 0x00, 0xc0, 0x00, 0x00,
  0x00, 0x27, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x76, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x8c,
  0x02, 0x20, 0x00, 0x00, 0x00, 0x01, 0x10, 0x01, 0x10, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x88,
  0x00, 0x00, 0x00, 0x05, 0x80, 0x00, 0x48, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x64, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char PingPongIcon[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
  0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x1e, 0x00, 0x08, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char MonsterBattlesIcon[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x7d, 0x80, 0x00, 0x00, 0x00, 0x00, 0x04, 0xf8, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x09, 0xf3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0xe4, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x27, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4f, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
	0x20, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3e, 0x40, 0x00, 0x00, 0x00, 0x00, 0x02, 0x7c, 0x80, 0x00, 
	0x00, 0x00, 0x00, 0x34, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0xf2, 0x00, 0x00, 0x00, 0x00, 
	0x10, 0x23, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x8f, 
	0x90, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x40, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xed, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xa0, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x05, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xee, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x03, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char GoblinHead[] PROGMEM = {
	0x00, 0x00, 0x07, 0xe0, 0x0f, 0xf0, 0x5f, 0xfa, 0x7f, 0xfe, 0x77, 0xee, 0x33, 0xcc, 0x3e, 0x7c, 
	0x1e, 0x78, 0x1d, 0xb8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00
};

const unsigned char SlimeHead[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x0f, 0xf0, 0x1f, 0xf8, 0x1b, 0xd8, 0x3b, 0xdc, 
	0x3b, 0xdc, 0x3f, 0xfc, 0x3e, 0x7c, 0x1f, 0xf8, 0x0f, 0xf0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00
};

const unsigned char KnightHead[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x0f, 0xf0, 0x1f, 0xf8, 0x1f, 0xf8, 0x13, 0xc8, 0x11, 0x88, 
	0x18, 0x18, 0x1e, 0x78, 0x1e, 0x78, 0x0e, 0x70, 0x07, 0xe0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00
};

const unsigned char SkeletonHead[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x1f, 0xf8, 0x1f, 0xf8, 0x3b, 0xdc, 0x3b, 0xdc, 0x3b, 0xdc, 
	0x3b, 0xdc, 0x3f, 0xfc, 0x3f, 0xfc, 0x0d, 0xb0, 0x0c, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char BanditHead[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x0b, 0xc0, 0x1f, 0xf0, 0x1e, 0x78, 0x38, 0x18, 0x30, 0x08, 0x32, 0x48, 
	0x12, 0x48, 0x10, 0x08, 0x18, 0x18, 0x1e, 0x70, 0x07, 0xe0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00
};

const char* games[] = { "Flappy Bird", "Ping-Pong", "Monster Battle" };
bool inGame = false;
int activeGame[] = { 0, 0, 0 };
int currentGame = 0;

int prevBlueState = LOW;
int prevRedState = LOW;
int prevWhiteState = LOW;

void manageInputs();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(blueButton, INPUT);
  pinMode(redButton, INPUT);
  pinMode(whiteButton, INPUT);

  // initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Clear the buffer.
  display.clearDisplay();


  // Text Layout
  display.setTextSize(1);       // Set text size
  display.setTextColor(WHITE);  // Set text color
  display.setCursor(0, 28);     // Set cursor position
  display.println("Starting Console...");
  display.display();

  delay(1500);

  // Show Logo
  display.clearDisplay();
  display.drawBitmap(32, 0, Logo, 63, 63, WHITE);
  display.display();

  delay(2250);
  display.clearDisplay();
};

void loop() {
  manageInputs();

  // Console Loop
  if (inGame == false) {
    menuLoop();
  } else {
    // Clear the screen
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    switch (currentGame) {
      case 0:
        flappyBird();
        break;
      case 1:
        pingPong();
        break;
      case 2:
        monster_battles();
        break;
      default:
        display.println("No game found!");
        display.display();
        delay(2000);
        inGame = false;
        break;
    }

    display.clearDisplay();
  }
}

void menuLoop() {
  if (b_buttonState == HIGH && prevBlueState == LOW) {
    currentGame == 2 ? currentGame = 0 : currentGame += 1;
  }

  if (r_buttonState == HIGH && prevRedState == LOW) {
    currentGame == 0 ? currentGame = 2 : currentGame -= 1;
  }

  if (w_buttonState == HIGH && prevWhiteState == LOW) {
    inGame = true;
    activeGame[currentGame] = 1;
  }

  currentGame = constrain(currentGame, 0, 2);

  menu(games[currentGame]);

  prevBlueState = b_buttonState;
  prevRedState = r_buttonState;
  prevWhiteState = w_buttonState;

  delay(50);
}

void menu(String title) {

  display.clearDisplay();
  int textWidth = title.length() * 6;
  int midXCoords = (128 - textWidth) / 2;

  // Display Game Title
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(midXCoords, 0);
  display.println(title);

  // Display Game Icon
  switch (currentGame) {
    case 0:
      display.drawBitmap(32, 12, BirdIcon, 50, 50, WHITE);
      break;
    case 1:
      display.drawBitmap(32, 12, PingPongIcon, 50, 50, WHITE);
      break;
    case 2:
      display.drawBitmap(32, 10, MonsterBattlesIcon, 50, 50, WHITE);
      break;
  }

  // Display Arrows
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 28);
  display.println("<");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(116, 28);
  display.println(">");

  display.display();
}

void flappyBird() {

  // Variables
  unsigned long lastFrameTime = 0;
  const unsigned long frameDelay = 40;

  int birdY = 32;
  int birdX = 10;
  int gravity = 2;
  int flapStrength = 15;

  int pipeX = 128;
  int pipeThickness = 7;
  int pipeSpeed = 2;
  int gapY = 0;
  int gapHeight = 20;

  int score = 0;

  bool running = true;
  bool resetGame = false;

  do {
    // Check Inputs
    manageInputs();

    if (w_buttonState == HIGH && prevWhiteState == LOW) {
      Serial.println("exiting flappy bird!");
      running = false;
      inGame = false;
    }

    if (b_buttonState == HIGH && prevBlueState == LOW) {
      Serial.println("flapping!");
      birdY > 0 ? birdY -= flapStrength : birdY = 0;
    }

    birdY = constrain(birdY, 0, 63);


    unsigned long now = millis();

    //  |===-----   Game Logic   -----===|
    if (now - lastFrameTime >= frameDelay) {
      lastFrameTime = now;

      // Apply Gravity
      birdY < 63 ? birdY += gravity : resetGame = true;

      if (score >= 10) {
        pipeSpeed = 3;
      }

      if (pipeX < -10) {
        // Reset the pipe back if it gets too far
        pipeX = 128;
        score++;
        gapY = random(5, 42);
      } else {
        pipeX -= pipeSpeed;
      }

      // Pipe Collision Check
      if (pipeX < 17 && pipeX > 6 && (birdY < gapY || birdY > gapY + gapHeight)) {
        resetGame = true;
      }


      if (resetGame) {
        // Reset variables
        score = 0;
        birdY = 32;
        pipeSpeed = 2;
        pipeX = 128;
        gapY = random(5, 42);
      }

      // Draw Assets
      display.clearDisplay();
      display.fillCircle(birdX, birdY, 3, SSD1306_WHITE);

      // Pipes
      display.fillRect(pipeX, 0, pipeThickness, gapY, SSD1306_WHITE);
      display.fillRect(pipeX, gapY + gapHeight, pipeThickness, SCREEN_HEIGHT, SSD1306_WHITE);

      // Score Display
      display.setTextSize(1);       // Set text size
      display.setTextColor(WHITE);  // Set text color
      display.setCursor(0, 0);
      display.println("Score: ");

      display.setTextSize(1);       // Set text size
      display.setTextColor(WHITE);  // Set text color
      display.setCursor(38, 0);
      display.println(score);

      display.display();
    }

    // Set previous states
    prevBlueState = b_buttonState;
    prevRedState = r_buttonState;
    prevWhiteState = w_buttonState;

    resetGame = false;
  } while (running);
}

void pingPong() {
  display.println("Playing Ping-Pong!");

  // Game Variables
  bool running = true;
  bool resetGame = false;
  int lineThickness = 2;
  int lineHeight = 19;
  int ballCycles = 0;
  int speed = 2;
  unsigned long lastFrameTime = 0;
  const unsigned long frameDelay = 40;

  // CPU Variables
  int cpuX = 10;
  int cpuY = 32;
  int cpuScore = 0;

  // Player Variables
  int playerX = 116;
  int playerY = 32;
  int playerScore = 0;

  // Ball Variables
  int ballX = 64;
  int ballY = 32;
  int ogBallX = 64;
  int ogBallY = 32;
  int ballRadi = 2;
  int ballSpeed = 1;
  int ogBallSpeed = 1;
  bool moveDown = true;
  bool moveRight = false;

  do {

    // Input Manager
    manageInputs();
    if (w_buttonState == HIGH && prevWhiteState == LOW) {
      running = false;
      inGame = false;
    }

    unsigned long now = millis();
    if (now - lastFrameTime >= frameDelay) {
      lastFrameTime = now;

      // ----==  Logic  ==----
      if (ballY <= 0) moveDown = true;
      if (ballY >= 63) moveDown = false;

      if (ballX <= 0) {
        resetGame = true;
        playerScore++;
      }

      if (ballX >= 127) {
        resetGame = true;
        cpuScore++;
      }

      // Collision Checks
      if (ballX < (lineThickness + playerX) && ballX > (playerX - lineThickness) && (ballY < playerY + lineHeight && ballY > playerY)) {
        moveRight = false;
        ballCycles++;
      }

      if (ballX < (lineThickness + cpuX) && ballX > (cpuX - lineThickness) && (ballY < cpuY + lineHeight && ballY > cpuY)) moveRight = true;

      // Apply Gravity
      if (moveDown) {
        ballY += 1;
      } else {
        ballY -= 1;
      }

      if (ballCycles == 2) {
        ballSpeed++;
        ballCycles = 0;
      }

      // Apply Ball Movement
      if (moveRight) {
        ballX += ballSpeed;
      } else {
        ballX -= ballSpeed;
      }

      // Apply Player Movement
      if (b_buttonState == HIGH) {
        playerY -= speed;
      }

      if (r_buttonState == HIGH) {
        playerY += speed;
      }

      // CPU AI
      if (cpuY + (lineHeight / 2) > ballY) {
        // Go Up
        cpuY -= speed;
      } else if (cpuY + (lineHeight / 2) < ballY) {
        // Go down
        cpuY += speed;
      }

      // Reset Game
      if (resetGame) {
        ballY = ogBallY;
        ballX = ogBallX;
        ballSpeed = ogBallSpeed;
        ballCycles = 0;
        resetGame = false;
        moveRight = false;
      }

      // Make sure the elements are in full display
      cpuY = constrain(cpuY, 0, 63);
      ballY = constrain(ballY, 0, 63);
      playerY = constrain(playerY, 0, 63);

      // Draw Assets
      display.clearDisplay();

      display.fillCircle(ballX, ballY, ballRadi, SSD1306_WHITE);
      display.fillRect(playerX, playerY, lineThickness, lineHeight, SSD1306_WHITE);
      display.fillRect(cpuX, cpuY, lineThickness, lineHeight, SSD1306_WHITE);

      // Score Display
      display.setTextSize(1);       // Set text size
      display.setTextColor(WHITE);  // Set text color
      display.setCursor(80, 0);
      display.println(playerScore);

      display.setTextSize(1);       // Set text size
      display.setTextColor(WHITE);  // Set text color
      display.setCursor(64, 0);
      display.println("-");

      display.setTextSize(1);       // Set text size
      display.setTextColor(WHITE);  // Set text color
      display.setCursor(48, 0);
      display.println(cpuScore);

      display.display();
    }

    prevBlueState = b_buttonState;
    prevRedState = r_buttonState;
    prevWhiteState = w_buttonState;
  } while (running);
}


struct Spell {
  const String name;
  int baseDmg;
};

enum Attacks{
  BITE,
  BOMB_BLAST,
  SHORTBOW,
  HEAVY_STRIKE,
  THRUST,
  SHIELD_BASH,
  BOUNCE,
  LUNGE,
  HURL,
};

struct AttackMove {
  const char* name;
  int dmg;
};

class Enemy {
private:
  std::vector<AttackMove> generic_moves;
public:
  const unsigned char* bitmapSprite;
  String name;
  int atk;
  int hp;

  Enemy(String n, int a, int h, std::vector<AttackMove> moves, const unsigned char* sprite)
    : name(n), atk(a), hp(h), generic_moves(moves), bitmapSprite(sprite){};

  void chooseMove(String& move, int& enemyDmg){
    bool useMove = (random(0,2) + 1 >= 2);
    size_t totalMoves = generic_moves.size();
    int chosenMove = 0;

    if(!useMove)
    {
      // Use normal attack
      enemyDmg = random(atk - 2, atk + 2);
      move = "strikes!";
    }
    else
    {
      // Use special attack
      chosenMove = random(0,totalMoves);
      enemyDmg = random(generic_moves[chosenMove].dmg - 3, generic_moves[chosenMove].dmg + 3);
      move = generic_moves[chosenMove].name;
    }
  }
};

void monster_battles() {
  // Game Variables
  bool running = true;
  bool playersTurn = true;
  bool actionMade = false;
  int menuOptions = 0;
  int runCount = 1;
  bool showRestock = false;
  const int HP_POT = 7;
  const int STRENGTH_POT = 11;
  const int HARMING_POT = 14;
  const int DODGE_POT = 16;
  const int STUN_POT = 19;
  const int DRAGON_BUFF = 20;
  bool fightEnd = false;

  int originalMaxHp = 90;
  int originalPlayerAtk = 7;
  int originalSpellCount = 4;
  int originalItemCount = 3;

  unsigned long lastFrameTime = 0;
  const unsigned long frameDelay = 40;

  // Player Statistics
  int maxHp = originalMaxHp;
  int playerHp = maxHp;
  int playerAtk = originalPlayerAtk;
  int spellCount = originalSpellCount;
  int itemCount = originalItemCount;
  int dodgeCounts = 0;

  Spell common_spells[] = {
    { "Fireball", 12 },
    { "Whirlpool", 13 },
    { "Earthquake", 15 },
    { "Tornado", 16 },
    { "GUN", 20 },
    { "Sweet Talk", 10 },
    { "Feces Storm", 18 },
    { "Wild Card!", 5 },
    { "Small Talk", 0 },
    { "Mild Breeze", 0 },
    { "Awkwardness", 0 },
    { "Final Doom", 0 }
  };

  Spell special_spells[] = {
    { "Divinity...", 80 },
    { "All Might", 99 },
    { "Chaos Blade", 111 },
    { "The Aether", 122 },
    { "Cataclysm", 150 }
  };

  // Enemy Statistics
  int enemyStunnedTurns = 0;

  std::unordered_map<Attacks,AttackMove> GENERIC_MOVES = {
    {Attacks::BITE, {"Bites", 7} },
    {Attacks::BOMB_BLAST, {"B. Blasts", 13} },
    {Attacks::SHORTBOW, {"Bows", 10} },
    {Attacks::HEAVY_STRIKE, {"H. Strikes", 15} },
    {Attacks::THRUST, {"Thrusts", 12} },
    {Attacks::SHIELD_BASH, {"S. Bashes", 10} },
    {Attacks::BOUNCE, {"Bounces", 7} },
    {Attacks::LUNGE, {"Lunges", 8} },
    {Attacks::HURL, {"Hurls", 11} }
  };

  Enemy enemyTypes[] = {
    Enemy("Goblin", 6, 30, std::vector<AttackMove>{GENERIC_MOVES.at(Attacks::BITE), GENERIC_MOVES.at(Attacks::SHORTBOW), GENERIC_MOVES.at(Attacks::BOMB_BLAST)}, GoblinHead),
    Enemy("Slime", 4, 50, std::vector<AttackMove>{GENERIC_MOVES.at(Attacks::BOUNCE), GENERIC_MOVES.at(Attacks::LUNGE)}, SlimeHead),
    Enemy("Bandit", 7, 40, std::vector<AttackMove>{GENERIC_MOVES.at(Attacks::HEAVY_STRIKE), GENERIC_MOVES.at(Attacks::LUNGE)}, BanditHead),
    Enemy("Skeleton", 9, 30, std::vector<AttackMove>{GENERIC_MOVES.at(Attacks::SHORTBOW), GENERIC_MOVES.at(Attacks::HURL)}, SkeletonHead),
    Enemy("Knight", 8, 65, std::vector<AttackMove>{GENERIC_MOVES.at(Attacks::SHIELD_BASH), GENERIC_MOVES.at(Attacks::HEAVY_STRIKE), GENERIC_MOVES.at(Attacks::THRUST)}, KnightHead)
  };

  int enemyType = random(0,5);
  String currentEnemy = enemyTypes[enemyType].name;
  int currentEnemyHp = enemyTypes[enemyType].hp;
  int currentEnemyAtk = enemyTypes[enemyType].atk;

  do {
    manageInputs();

    if (w_buttonState == HIGH && prevWhiteState == LOW) {
      inGame = false;
      running = false;
    }

    if (b_buttonState == HIGH && prevBlueState == LOW) {
      actionMade = true;
    }

    if (r_buttonState == HIGH && prevRedState == LOW) {
      menuOptions++;
      menuOptions = constrain(menuOptions, 0, 3);
      if (menuOptions == 3) menuOptions = 0;
    }


    unsigned long now = millis();

    // --- Game Logic ---
    if (now - lastFrameTime >= frameDelay) {
      lastFrameTime = now;

      // Draw Assets
      display.clearDisplay();

      if(runCount % 2 == 1 && (runCount > 1 && runCount <= 7) && fightEnd)
      {
        display.setCursor(0,32);
        display.println("Item & Spell Restock!");
        spellCount += 3;
        itemCount += 2;
        playerHp += 45;
        playerHp = constrain(playerHp, 1, maxHp);
        display.display();
        delay(1000);
        display.clearDisplay();
      }
      else if(runCount % 3 == 0 && (runCount > 7) && fightEnd)
      {
        display.setCursor(0,32);
        display.println("Item & Spell Restock!");
        spellCount += 4;
        itemCount += 3;
        playerHp += 45;
        playerHp = constrain(playerHp, 1, maxHp);
        display.display();
        delay(1000);
        display.clearDisplay();
      }

      fightEnd = false;

      display.drawBitmap(54, 20, enemyTypes[enemyType].bitmapSprite, 16, 16, WHITE);

      drawStats(playerHp, currentEnemyHp, runCount);

      // Show Players' Options
      if (playersTurn && !actionMade) {
        // Boxes
        display.setTextSize(1);       // Set text size
        display.setTextColor(WHITE);  // Set text color
        display.setCursor(4, 55);
        display.println("Fight");

        if (menuOptions == 0) display.drawRect(0, 52, 37, 12, SSD1306_WHITE);

        display.setTextSize(1);       // Set text size
        display.setTextColor(WHITE);  // Set text color
        display.setCursor(53, 55);
        display.println("Magic");

        if (menuOptions == 1) display.drawRect(49, 52, 36, 12, SSD1306_WHITE);

        display.setTextSize(1);       // Set text size
        display.setTextColor(WHITE);  // Set text color
        display.setCursor(99, 55);
        display.println("Item");

        if (menuOptions == 2) display.drawRect(96, 52, 29, 12, SSD1306_WHITE);
        display.display();
      }

      if (actionMade) {
        display.drawRect(0, 40, 127, 24, SSD1306_WHITE);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(3, 45);

        int dmg = 0;
        bool useMajorSpell = (random(1, 12) >= 11);
        int spellCast = 0;
        int itemRoll = random(0, 21);
        int healAmt = 0;

        switch (menuOptions) {
          case 0:
            // Basic Attack
            dmg = random(playerAtk - 3, playerAtk + 3);
            display.print("You struck for ");
            currentEnemyHp -= dmg;
            display.print(dmg);
            display.println("hp!");
            break;
          case 1:
            if(spellCount <=0)
            {
              display.print("No more spells!");
              break;
            }

            if (!useMajorSpell) {
              // Use a common spell
              spellCast = random(0, 12);

              if (spellCast != 7) {
                dmg = random(common_spells[spellCast].baseDmg - 3, common_spells[spellCast].baseDmg + 5);
              } else if (spellCast == 7) {
                dmg = random(0, 35);
              }

              display.print("You cast ");
              display.print(common_spells[spellCast].name);

              // Normal Text Display
              descriptionText();

              if (spellCast > 7) {
                dmg = 0;
                switch (spellCast) {
                  // {"Small Talk", 0}, {"Mild Breeze", 0}, {"Awkward Stare", 0}, {"Final Doom", 0}
                  case 8:
                    display.print("How's the weather?");
                    break;
                  case 9:
                    display.print("Windy today huh?");
                    break;
                  case 10:
                    display.print("You stare impolitely");
                    break;
                  case 11:
                    display.display();
                    delay(1500);
                    display.print("You fail.");
                    break;
                  default:
                    display.print("No spell found matches...");
                    break;
                }
              } else {
                display.print("You dealt ");
                display.print(dmg);
                display.println("hp!");
              }
            } else {
              // Use a major spell
              spellCast = random(0, 5);
              dmg = random(special_spells[spellCast].baseDmg, special_spells[spellCast].baseDmg + 35);

              display.print("You cast ");
              display.print(special_spells[spellCast].name);

              descriptionText();

              display.print("You dealt ");
              display.print(dmg);
              display.println("hp!");
            }
            dmg = constrain(dmg, 0, 999);
            currentEnemyHp -= dmg;

            spellCount--;
            break;
          case 2:
            // Items
            if(itemCount <= 0)
            {
              display.print("No more items!");
              break;
            }
            
            if (itemRoll <= HP_POT) {
              display.print("You use heal. pot.!");

              descriptionText();

              healAmt = random(15, 45);
              display.print("You heal for ");
              display.print(healAmt);
              playerHp += healAmt;
              playerHp = constrain(playerHp, 1, maxHp);
            } else if (itemRoll <= STRENGTH_POT) {
              display.print("You use strgt. pot.!");

              descriptionText();

              display.print("+2 atk dmg!");
              playerAtk += 2;
            } else if (itemRoll <= HARMING_POT) {
              display.print("You use harm. pot.!");

              descriptionText();

              display.print("You deal 25 dmg!");
              currentEnemyHp -= 25;
            } else if (itemRoll <= DODGE_POT) {
              display.print("You use dodge pot.!");

              descriptionText();

              dodgeCounts = 3;
              display.print("Dodge 3 atks (maybe)");
              // Implement Logic when Enemies are implemented
            } else if (itemRoll <= STUN_POT) {
              display.print("You use stun pot.!");

              descriptionText();
              enemyStunnedTurns = 3;
              display.print("Stun for 3 turns!");
              // Implement Logic when Enemies are implemented
            } else if (itemRoll == DRAGON_BUFF) {
              display.print("You use Dragon Buff");

              descriptionText();

              maxHp += 25;
              playerHp += 45;
              playerHp = constrain(playerHp, 1, maxHp);
              playerAtk += 3;
              spellCount += 3;

              display.print("+Max Hp +Dmg +Spells");
            }

            itemCount--;
            break;
        }

        display.display();

        delay(1500);
        playersTurn = false;
        actionMade = false;
      }

      if (!playersTurn) {

        display.clearDisplay();
        drawStats(playerHp, currentEnemyHp, runCount);

        if(currentEnemyHp > 0 && enemyStunnedTurns <= 0)
        {
          // Enemy's Action
          String move;
          int enemyDmg = 0;
          enemyTypes[enemyType].chooseMove(move, enemyDmg);

          display.drawRect(0, 40, 127, 24, SSD1306_WHITE);
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(3, 45);

          display.print(currentEnemy);
          display.print(" ");
          display.print(move);

          descriptionText();

          if(dodgeCounts > 0 && random(1,11) <= 4)
          {
            dodgeCounts--;
            enemyDmg = 0;
            display.print("But you dodged!");
          }
          else
          {
            display.print("They dealt ");
            display.print(enemyDmg);
            display.println("hp!");
          }

          display.display();

          delay(1500);

          playerHp -= enemyDmg;
        }
        else if(currentEnemyHp <= 0)
        {
          display.drawRect(0, 40, 127, 24, SSD1306_WHITE);
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(3, 45);

          display.print(currentEnemy);
          display.println(" has fallen.");

          display.display();

          delay(1000);

          // Reroll enemy
          enemyType = random(0,5);
          currentEnemy = enemyTypes[enemyType].name;
          currentEnemyHp = enemyTypes[enemyType].hp;
          currentEnemyAtk = enemyTypes[enemyType].atk;
          runCount++;
          fightEnd = true;
        }

        if(enemyStunnedTurns > 0) enemyStunnedTurns--;

        playersTurn = true;
      }

      if(playerHp <= 0)
      {
        display.clearDisplay();

        display.drawRect(0, 40, 127, 24, SSD1306_WHITE);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(3, 45);

        display.println("You have fallen.");

        display.display();

        delay(1250);

        // Reset Game State
        runCount = 1;
        spellCount = originalSpellCount;
        itemCount = originalItemCount;
        maxHp = originalMaxHp;
        playerHp = maxHp;
        playerAtk = originalPlayerAtk;
        enemyType = random(0,5);
        currentEnemy = enemyTypes[enemyType].name;
        currentEnemyHp = enemyTypes[enemyType].hp;
        currentEnemyAtk = enemyTypes[enemyType].atk;
      }
    }

    prevBlueState = b_buttonState;
    prevRedState = r_buttonState;
    prevWhiteState = w_buttonState;


  } while (running);
}


void descriptionText() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(3, 55);
}

void drawStats(int playerHp, int enemyHp, int runCount){
  // Player Stats
  display.setTextSize(1);       // Set text size
  display.setTextColor(WHITE);  // Set text color
  display.setCursor(0, 0);
  display.println("Hp: ");

  display.setTextSize(1);       // Set text size
  display.setTextColor(WHITE);  // Set text color
  display.setCursor(20, 0);
  display.println(playerHp);

  // Run Count
  display.setTextSize(1);       // Set text size
  display.setTextColor(WHITE);  // Set text color
  display.setCursor(0, 12);
  display.println("Run: ");

  display.setTextSize(1);       // Set text size
  display.setTextColor(WHITE);  // Set text color
  display.setCursor(27, 12);
  display.println(runCount);

  // Enemy Stats
  display.setTextSize(1);       // Set text size
  display.setTextColor(WHITE);  // Set text color
  display.setCursor(52, 0);
  display.println("Enemy Hp: ");

  display.setTextSize(1);       // Set text size
  display.setTextColor(WHITE);  // Set text color
  display.setCursor(107, 0);
  display.println(enemyHp);
}

void manageInputs() {
  b_buttonState = digitalRead(blueButton);
  r_buttonState = digitalRead(redButton);
  w_buttonState = digitalRead(whiteButton);
}