
#define LED_1 7 // LEDs
#define LED_2 6
#define LED_3 5
#define LED_4 4
#define LED_5 3
#define LED_6 2

#define SPEAKER_PIN 8 // Speaker output

#define LEFT_BUTTON 11   // Left blinker button
#define RIGHT_BUTTON 10  // Right blinker button

const int LEDS[] = {LED_1, LED_2, LED_3, LED_4, LED_5, LED_6};
const int NUM_LEDS = sizeof(LEDS) / sizeof(LEDS[0]);

bool rightBlinkerOn = false;
bool leftBlinkerOn = false;

void setup() {
  //  Init LED ports to outputs
  for(int i = 0; i < NUM_LEDS; i++){
    pinMode(LEDS[i], OUTPUT);
  }

  // Init Blinker button ports to Inputs
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
}

void blinkerSoundOn() {
  tone(SPEAKER_PIN, 1300, 15);  // 300 Hz tone for 15ms
}

void blinkerSoundOff() {
  tone(SPEAKER_PIN, 1000, 15);  // 200 Hz tone for 15ms
}

void turnOffBlinker(){
  for(int i = 0; i < NUM_LEDS; i++){
    digitalWrite(LEDS[i], LOW);
  }
}

void rightBlinkerSequence(){
  blinkerSoundOn();
  for(int i = 0; i < NUM_LEDS; i++){ // Loop forwards
    digitalWrite(LEDS[i], HIGH); // Turn LED on
    delay(100);
  }
  delay(100);
  blinkerSoundOff();
  turnOffBlinker();
  delay(300);
}

void leftBlinkerSequence(){
  blinkerSoundOn();
  for(int i = NUM_LEDS - 1; i >= 0; i--){  // Loop backwards
    digitalWrite(LEDS[i], HIGH);  // Turn LED on
    delay(100);
  }
  delay(100);
  blinkerSoundOff();
  turnOffBlinker();
  delay(300);
}

void loop() {
  static bool leftButtonPrevState = HIGH;
  static bool rightButtonPrevState = HIGH;

  bool leftButtonState = digitalRead(LEFT_BUTTON);
  bool rightButtonState = digitalRead(RIGHT_BUTTON);

  // Check if left button is pressed
  if (leftButtonState == LOW && leftButtonPrevState == HIGH) {
    leftBlinkerOn = !leftBlinkerOn; // Toggle left blinker
    rightBlinkerOn = false; // Turn off right blinker
  }

  // Check if right button is pressed
  if (rightButtonState == LOW && rightButtonPrevState == HIGH) {
    rightBlinkerOn = !rightBlinkerOn; // Toggle right blinker
    leftBlinkerOn = false; // Turn off left blinker
  }

  leftButtonPrevState = leftButtonState;
  rightButtonPrevState = rightButtonState;

  if (leftBlinkerOn) {
    leftBlinkerSequence();
  } 
  else if (rightBlinkerOn) {
    rightBlinkerSequence();
  } 
  else {
    turnOffBlinker();
  }
}
