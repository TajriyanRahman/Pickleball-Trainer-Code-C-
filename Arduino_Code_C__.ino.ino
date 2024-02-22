const int buttonPin = A1;  // pin number of the pushbutton
const int ledCount = 14;   // total number of LEDs
int leds[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, A2, A3, A4, A5};  // array to hold pin numbers

bool programRunning = false;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void flashLights() {
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(leds[i], HIGH);
    }
    delay(1000);  // Lights stay on for 1 second
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(leds[i], LOW);
    }
    delay(1000);  // Lights stay off for 1 second
  }
}

void loop() {
  // Wait for the button to be pressed
  if (digitalRead(buttonPin) == HIGH && !programRunning) {
    programRunning = true;

    // Flash the lights
    flashLights();

    // Randomly shuffle the pins
    for (int i = ledCount - 1; i >= 0; i--) {
      int randIndex = random(i + 1);
      int temp = leds[i];
      leds[i] = leds[randIndex];
      leds[randIndex] = temp;
    }

    // Turn on each light in the shuffled sequence for 10 seconds
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(leds[i], HIGH);
      delay(10000);  // Lights stay on for 10 seconds
      digitalWrite(leds[i], LOW);

      // Random delay between 10 and 15 seconds before the next light
      delay(random(10000, 15001));
    }

    // Reset the program state
    programRunning = false;
  }
}
