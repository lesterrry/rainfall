Logger logger(DEBUG);
Relay relay(RELAY_PIN);
Knob knob(ENC_CLK_PIN, ENC_DT_PIN, ENC_SW_PIN);
Buzzer buzzer(BUZZER_PIN);
Display display(LED_ADDRESS, LED_WIDTH, LED_HEIGHT);
Timer timer(DEFAULT_TIMER_VALUE, MAX_TIMER_VALUE);
ProgressBar bar(DEFAULT_TIMER_VALUE);

MemoryEntry memorizedInitialSecondsLeft(EEPROM_INITIAL_TIMER_VALUE_ADDRESS);

unsigned long lastMillis = 0;
bool alertHigh = false;

void printRelayStatus() {
  display.print(relay.getState() ? '|' : 'O', 15, 0);
}

void printTimeLeft() {
  display.clear();
  display.print(timer.timeLeft());
  printRelayStatus();
  display.print(bar.getString(), 0, 1);
}

void resetTimer() {
  buzzer.silent();
  display.setBacklight();
  relay.on();
}

void setup() {
  pinMode(ENC_VCC_PIN, OUTPUT);
  digitalWrite(ENC_VCC_PIN, HIGH);

  logger.begin();
  display.begin();

  display.print(F("SUBURBS:"));
  display.print(F("RAINFALL"), 0, 1);

  logger.print(F("Rainfall initializing..."));

  buzzer.playToneB();

  delay(500);
  
  uint16_t memorizedInitialSecondsLeftValue = memorizedInitialSecondsLeft.read();
  logger.print("EEPROM: " + String(memorizedInitialSecondsLeftValue));

  if (memorizedInitialSecondsLeftValue > 0 && memorizedInitialSecondsLeftValue < MAX_TIMER_VALUE) {
    timer.setSecondsLeft(memorizedInitialSecondsLeftValue);
  }

  #ifdef CLEAR_EEPROM
    memorizedInitialSecondsLeft.write(0);
  #endif
  #ifdef DEBUG_TONES
    int i = 50;
    while(true) {
      logger.print(i);
      buzzer.sound(i);
      delay(1000);
      i += 50;
    }
	#endif

  relay.on();

  display.clear();
  
  knob.reset();

  logger.print(F("Entering loop..."));
}
  
void loop() {
  unsigned long currentMillis = millis();

  knob.update();

  if (knob.isRight()) {
    if (timer.adjust(300) > 0) resetTimer();
    buzzer.beep(4);
    bar.updateMaxValue(timer.getSecondsLeft());
    printTimeLeft();
  } else if (knob.isLeft()) {
    buzzer.beep(3);
    timer.adjust(-300);
    bar.updateMaxValue(timer.getSecondsLeft());
    printTimeLeft();
  } else if (knob.isClick()) {
    buzzer.beep(6, 100);
    memorizedInitialSecondsLeft.write(timer.getLastSet());
    display.clear();
    display.print(F("SAVED: "));
    display.print(timer.lastSet(), 0, 1);
    delay(1500);
  } else if (knob.isDown()) {
    buzzer.beep(6, 200);
    memorizedInitialSecondsLeft.write(0);
    display.clear();
    display.print(F("ERASED: "));
    display.print(Timer::formatSeconds(DEFAULT_TIMER_VALUE), 0, 1);
    delay(1500);
  }

  if (currentMillis - lastMillis >= 1000) {
    if (!timer.tick()) {  // timer has finished
      relay.off();
      
      buzzer.playAlert(alertHigh);
      display.setBacklight(alertHigh);
      alertHigh = !alertHigh; 
    }

    bar.tick();

    printTimeLeft();

    lastMillis = currentMillis;
  }
}
