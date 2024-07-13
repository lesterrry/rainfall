/******************************
Suburbs: rainfall
Interactive sleep-timer relay

me@aydar.media
******************************/

#define DEBUG 1

#define VERSION "0.1.0"

// #define DEBUG_TONES

#define RELAY_PIN           7
#define LED_ADDRESS         0x27
#define LED_WIDTH           16
#define LED_HEIGHT          2
#define ENC_VCC_PIN         8
#define ENC_CLK_PIN         11
#define ENC_DT_PIN          10
#define ENC_SW_PIN          9
#define BUZZER_PIN          2
#define DEFAULT_TIMER_VALUE 10//5400  // 1.5h
#define MAX_TIMER_VALUE     18000     // 5h

#include <SPI.h>
#include <Wire.h>
#include <GyverEncoder.h>
#include <LiquidCrystal_I2C.h>
