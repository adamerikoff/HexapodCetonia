#include <Servo.h>  // Include the Servo library

#define TRIG_PIN 13
#define ECHO_PIN 12
#define SERVO_PIN 11

Servo myServo;  // Create a Servo object
unsigned long previousMillis = 0;  // Store the last time the servo moved
const long interval = 2000;  // Interval at which to move the servo (2 seconds)

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  
  myServo.attach(SERVO_PIN);  // Attach the servo to the specified pin
  myServo.write(0);  // Set the initial position of the servo to 0 degrees
}

void loop() {
  float distance = measureDistance();
  printDistanceOrNotify(distance);

  // Move the servo if the interval has passed
  moveServoIfNeeded();

  delay(500);  // Wait for 500ms before the next distance reading
}

// Function to trigger the sensor and measure distance
float measureDistance() {
  long duration;
  // Ensure the trigger pin is low before starting
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Send a 10us HIGH pulse to trigger the sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Measure the duration of the echo pulse in microseconds
  duration = pulseIn(ECHO_PIN, HIGH, 30000);  // Timeout after 30ms
  // If no pulse detected, return -1
  return (duration == 0) ? -1 : (duration * 0.0343) / 2;
}

// Function to print the distance or notify if no object is detected
void printDistanceOrNotify(float distance) {
  if (distance < 0) {
    Serial.println("No object detected");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
}

// Function to move the servo
void moveServoIfNeeded() {
  static unsigned long lastMoveTime = 0;  // Store the last time the servo moved
  unsigned long currentMillis = millis();  // Get the current time
  // Check if 2 seconds have passed
  if (currentMillis - lastMoveTime >= interval) {
    lastMoveTime = currentMillis;  // Update the last move time
    int pos = getNextServoPosition();  // Get the next position for the servo
    myServo.write(pos);  // Move the servo to the new position
    printServoPosition(pos);  // Print the new position
  }
}

// Function to get the next position of the servo
int getNextServoPosition() {
  static int pos = 0;  // Current position of the servo
  pos += 30;  // Increment the position by 30 degrees
  // Reset position if it exceeds 180 degrees
  if (pos > 180) {
    pos = 0;
  }
  return pos;  // Return the new position
}

// Function to print the current servo position
void printServoPosition(int pos) {
  Serial.print("Servo moved to: ");
  Serial.print(pos);
  Serial.println(" degrees");
}
