#include <Servo.h>

Servo sg90;
int cleanLDR = A0;
int panelLDR = A1;
int errorMargin = 5;
int servoPin = 9;
int cleaningStart = 0;
int cleaningEnd = 180;
int cleaningSpeed = 15;

void setup() {
  sg90.attach(servoPin);
  pinMode(cleanLDR, INPUT);
  pinMode(panelLDR, INPUT);
  sg90.write(cleaningStart);
  delay(2000);
  Serial.begin(9600);
}

void loop() {
  int cleanIntensity = analogRead(cleanLDR);
  int panelIntensity = analogRead(panelLDR);
  int intensityDifference = cleanIntensity - panelIntensity;

  if (intensityDifference > errorMargin) {
    Serial.println("Cleaning required...");
    startCleaning();
  } else {
    Serial.println("Panel is clean.");
  }

  delay(2000);
}

void startCleaning() {
  for (int pos = cleaningStart; pos <= cleaningEnd; pos++) {
    sg90.write(pos);
    delay(cleaningSpeed);
  }
  for (int pos = cleaningEnd; pos >= cleaningStart; pos--) {
    sg90.write(pos);
    delay(cleaningSpeed);
  }
}
