Logger logger(DEBUG);
Relay relay(RELAY_PIN);
Knob knob(ENC_CLK_PIN, ENC_DT_PIN, ENC_SW_PIN);
Buzzer buzzer(BUZZER_PIN);
Display display(LED_ADDRESS, LED_WIDTH, LED_HEIGHT);
Timer timer(DEFAULT_TIMER_VALUE, MAX_TIMER_VALUE);

unsigned long lastMillis = 0;
bool alertHigh = false;

void printTimeLeft() {
  display.clear();
  display.print(timer.timeLeft(), 0, 0);
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

  display.print("SUBURBS:");
  display.print("RAINFALL", 0, 1);

  buzzer.playToneB();

  delay(500);

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

  logger.print(F("Entering loop..."));
}
  
void loop() {
  unsigned long currentMillis = millis();

  knob.update();

  if (knob.isRight()) {
    buzzer.beep(4);
    if (timer.adjust(300) > 0) resetTimer();
    printTimeLeft();
  } else if (knob.isLeft()) {
    buzzer.beep(3);
    timer.adjust(-300);
    printTimeLeft();
  } else if (knob.isClick()) {
    buzzer.beep(6, 100);

  }

  if (currentMillis - lastMillis >= 1000) {
    if (!timer.tick()) {  // timer has finished
      relay.off();
      display.clear();
      display.print("DONE", 0, 0);
      
      buzzer.playAlert(alertHigh);
      display.setBacklight(alertHigh);
      alertHigh = !alertHigh; 
    } else {
      printTimeLeft();
    }

    lastMillis = currentMillis;
  }
}
