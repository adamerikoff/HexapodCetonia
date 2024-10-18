#include <Servo.h>

Servo s1;

void setup() {
  s1.attach(D0);  // Attach the servo to pin D0
}

void loop() {
  // Rotate from 0 to 180 degrees in steps of 10 degrees
  for (int pos = 0; pos <= 180; pos += 10) {
    s1.write(pos);  // Move to the current position
    delay(1000);    // Wait for 1 second
  }

  // Rotate back from 180 to 0 degrees in steps of 10 degrees
  for (int pos = 180; pos >= 0; pos -= 10) {
    s1.write(pos);  // Move to the current position
    delay(1000);    // Wait for 1 second
  }
}
