#include <Stepper.h>

// Define the number of steps per revolution for the 28BYJ-48 motor
#define STEPS_PER_REV 2048  // This motor has 2048 steps per revolution

// Initialize the Stepper library on pins 8, 9, 10, and 11
Stepper stepper(STEPS_PER_REV, 8, 10, 9, 11);

const int trigPin = 3;
const int echoPin = 4;

long duration;
int distance;

// Motor and scanning parameters
const int SCAN_ANGLE = 90; // Degrees to scan in one direction (180 total)
const int STEPS_PER_DEGREE = STEPS_PER_REV / 360;
const int SCAN_STEP = 10;  // Number of degrees to step per scan iteration

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  Serial.println("Starting room scan...");

  // Set the speed of the motor (adjustable)
  stepper.setSpeed(10);  // Speed in RPM (rotations per minute)
  Serial.println("Stepper motor speed set.");

  // Setup ultrasonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  Serial.println("Ultrasonic sensor pins configured.");
}

void loop() {
  // Sweep through the scan angle and take distance measurements
  for (int angle = -SCAN_ANGLE; angle <= SCAN_ANGLE; angle += SCAN_STEP) {
    rotateMotorToAngle(angle);  // Rotate the motor to the current angle
    measureDistance();          // Measure distance with the ultrasonic sensor
    delay(500);                 // Small delay between measurements
  }
  
  // After scanning in one direction, return to the center position
  Serial.println("Scan completed. Returning to center position.");
  rotateMotorToAngle(0);  // Move motor back to the center
  delay(2000);            // Wait for 2 seconds before repeating the scan
}

void rotateMotorToAngle(int angle) {
  int stepsToMove = angle * STEPS_PER_DEGREE;  // Calculate steps to rotate to the angle
  Serial.print("Rotating to angle: ");
  Serial.println(angle);
  stepper.step(stepsToMove);
}

void measureDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Debug logging for distance
  Serial.print("Distance at current angle: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if a wall is detected or not
  if (distance < 30) {  // If distance is less than 30 cm, assume a wall is present
    Serial.println("Wall detected!");
  } else {
    Serial.println("No wall detected.");
  }
}
