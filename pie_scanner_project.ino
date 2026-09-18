#include <Servo.h>
Servo xservo;
Servo yservo;

const int sensorPin = A0; // Select the input pin for the sensor
int xpos = 0;    // variable to store the horizontal servo position
int ypos = 0;    // variable to store the vertical servo position

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  xservo.attach(9);  // attaches the x servo on pin 9 to the Servo object
  yservo.attach(10);  // attaches the y servo on pin 10 to the Servo object
  xservo.write(xpos);  // Zero out x servo
  yservo.write(ypos);  // Zero out y servo
  delay(500);
}

void loop() {
  for (xpos = 0; xpos <= 180; xpos += 1) { // goes from 0 degrees to 180 degrees
    xservo.write(xpos);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15 ms for the servo to reach the position
    Serial.print(xpos);   Serial.print(",");
    Serial.println(read_distance());
  }
  delay(50); // Wait a little for servo to reset
}

int read_distance() {
  float distance = 0;
  for (int i = 1; i <= 5; i++) {
    int rawValue = analogRead(sensorPin); // Read the raw analog value (0-1023)
    float voltage = rawValue * (5.0 / 1023.0); // Convert raw value to voltage
    // Approximate distance calculation based on GP2Y0A02YK0F datasheet characteristics
    // Note: The output is non-linear; this formula provides a reasonable approximation for 20-150cm.
    distance += 61.543 * pow(voltage, -1.106);
    delay(15);
  }
  distance = distance / 5;
  return distance;
}
