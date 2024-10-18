void setup() {
  Serial.begin(115200);  // Start the serial communication at 115200 baud rate
}

void loop() {
  Serial.println("Hello, World!");  // Print "Hello, World!" to the Serial Monitor
  delay(1000);  // Wait for 1 second (1000 milliseconds)
}
