#define TRIG_PIN 13
#define ECHO_PIN 12

float duration, distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Ensure the trigger pin is low before starting
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10us HIGH pulse to trigger the sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the duration of the echo pulse in microseconds
  duration = pulseIn(ECHO_PIN, HIGH, 30000);  // Timeout after 30ms

  // If no pulse detected, pulseIn() returns 0
  if (duration == 0) {
    Serial.println("No object detected");
  } else {
    // Calculate distance in cm (speed of sound ~343 m/s)
    distance = (duration * 0.0343) / 2;

    // Print the distance
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);  // Wait for 500ms before the next reading
}
