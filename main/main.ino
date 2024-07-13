/******************************
Suburbs: rainfall
Interactive sleep-timer relay

me@aydar.media
******************************/

#define DEBUG 1

#define VERSION "0.1.0"

// #define DEBUG_TONES
#define DEBUG_MODULES
// #define DEBUG_TONES

#define RELAY_PIN      7
#define LED_ADDRESS    0x27
#define LED_WIDTH      16
#define LED_HEIGHT     2
#define ENC_CLK_PIN    45
#define ENC_DT_PIN     47
#define ENC_SW_PIN     49
#define BUZZER_PIN     2

#include <microDS3231.h>
#include <SPI.h>
#include <Wire.h>
#include <GyverEncoder.h>
#include <LiquidCrystal_I2C.h>
