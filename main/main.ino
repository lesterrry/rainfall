/******************************
Suburbs: rainfall
Interactive sleep-timer relay

me@aydar.media
******************************/

#define DEBUG 0

#undef DEBUG_TONES
#undef CLEAR_EEPROM

#define RELAY_PIN                          7
#define LED_ADDRESS                        0x27
#define LED_WIDTH                          16
#define LED_HEIGHT                         2
#define ENC_VCC_PIN                        8
#define ENC_CLK_PIN                        11
#define ENC_DT_PIN                         10
#define ENC_SW_PIN                         9
#define BUZZER_PIN                         2
#define EEPROM_INITIAL_TIMER_VALUE_ADDRESS 0
#define DEFAULT_TIMER_VALUE                5400  // 1.5h
#define MAX_TIMER_VALUE                    18000 // 5h
#define MAX_ALERT_TIMES                    60    // 1m

#include <cmath>
#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <GyverEncoder.h>
#include <LiquidCrystal_I2C.h>
