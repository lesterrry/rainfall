Logger logger(DEBUG);
Relay relay(RELAY_PIN);
Knob knob(ENC_CLK_PIN, ENC_DT_PIN, ENC_SW_PIN);
Buzzer buzzer(BUZZER_PIN);
Display display(LED_ADDRESS, LED_WIDTH, LED_HEIGHT);

const uint16_t DEFAULT_TIMER_VALUE = 5400;  // 1.5h

unsigned long timer = 0;
uint16_t elapsedValue = 0; 

// void handleKnobRotation(bool direction) {

// }

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

  display.clear();

  logger.print(F("Entering loop..."));
}
  
void loop() {
  unsigned long current = millis();

  knob.update();

  if (knob.isRight()) {
    buzzer.beep(4);

  } else if (knob.isLeft()) {
    buzzer.beep(3);

  } else if (knob.isClick()) {
    buzzer.beep(6, 100);

  }

  if (current - timer >= 1000) {
    elapsedValue++;
    
    display.print(String(elapsedValue), 0, 0);

    timer = current;
  }
}
