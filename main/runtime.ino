Logger logger(DEBUG);
Relay relay(RELAY_PIN);
Knob knob(ENC_CLK_PIN, ENC_DT_PIN, ENC_SW_PIN);
Buzzer buzzer(BUZZER_PIN);
Display display(LED_ADDRESS, LED_WIDTH, LED_HEIGHT);

// uint32_t bootTime;

// unsigned long timer_pageRender = 0;

// void handleKnobRotation(bool direction) {

// }

void setup() {
  logger.begin();
  display.begin();

  display.print("SUBURBS:");
  display.print("RAINFALL", 0, 1);

  buzzer.playToneA();

  logger.print(F("Rainfall initializing..."));
  logger.print(F("Entering loop..."));

  #ifdef DEBUG_TONES
		int i = 50;
		while(true) {
			logger.print(i);
			buzzer.sound(i);
			delay(1000);
			i += 50;
		}
	#endif
}
  
void loop() {
  

}
