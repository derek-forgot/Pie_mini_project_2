#include <Servo.h>
#include <math.h>

Servo Xservo;
Servo Yservo;

const int sensorPin = A0;

int y_pos = 0;
int x_pos = 0;

void setup() {
  // Attach servos to pins 9 and 10
  Xservo.attach(9);
  Yservo.attach(10);

  // Zero out the servos
  Xservo.write(0);
  Yservo.write(0);

  // Begin Serial out
  Serial.begin(115200);
  delay(500);
}

void loop() {

  // Y sweeps from 0 to 90
  for (y_pos = 0; y_pos <= 90; y_pos ++) {

    // Nudge y
    Xservo.write(y_pos);
    delay(5);

    // Take Reading and send data through serial (the formatting is very specific for MatLab to accept)
    Serial.print(" ");
    Serial.print(y_pos);
    Serial.print(" ");
    Serial.print(x_pos);
    Serial.print(" ");
    Serial.print(read_distance());
    Serial.println(" ");
  }

  // Y moves down 1 degree
  x_pos += 1;
  Yservo.write(x_pos);
  Xservo.write(0);
  delay(100);

  // Stop once Y reaches 180
  if (x_pos >= 90) {
    while (true) {
      // Stop here
    }
  }
}

int read_distance() {
  float distance = 0;                     // Reset distance value
  for (int i = 1; i <= 5; i++) {
    int rawValue = analogRead(sensorPin); // Read the raw analog value (0-1023)
    distance += rawValue;                 // Sum up the readings
    delay(5);                             // Wait for 5ms
  }
  distance = distance / 5;                // Divide the measurement by 5 to average the readings
  return distance;
}
