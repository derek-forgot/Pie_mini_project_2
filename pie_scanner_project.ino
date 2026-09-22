#include <Servo.h>
#include <math.h>

Servo Xservo;
Servo Yservo;

const int sensorPin = A0;

int x_pos = 0;
int y_pos = 0;

void setup() {
  Xservo.attach(9);
  Yservo.attach(10);

  Xservo.write(0);
  Yservo.write(0);

  Serial.begin(115200);
}

void loop() {

  // X sweeps from 0 to 180
  for (x_pos = 0; x_pos <= 180; x_pos += 1) {

    Xservo.write(x_pos);

    int rawValue = analogRead(sensorPin);
    float voltage = rawValue * (5.0 / 1023.0);
    float distance = 61.543 * pow(voltage, -1.106);

    Serial.print("X: ");
    Serial.print(x_pos);
    Serial.print("  Y: ");
    Serial.print(y_pos);
    Serial.print("  Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(2);
  }

  // Y moves down 1 degree
  y_pos += 1;
  Yservo.write(y_pos);
  delay(2);

  // X sweeps from 180 back to 0
  for (x_pos = 180; x_pos >= 0; x_pos -= 1) {

    Xservo.write(x_pos);

    int rawValue = analogRead(sensorPin);
    float voltage = rawValue * (5.0 / 1023.0);
    float distance = 61.543 * pow(voltage, -1.106);

    Serial.print("X: ");
    Serial.print(x_pos);
    Serial.print("  Y: ");
    Serial.print(y_pos);
    Serial.print("  Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(2);
  }

  // Y moves down 1 degree
  y_pos += 1;
  Yservo.write(y_pos);
  delay(2);

  // Stop once Y reaches 180
  if (y_pos >= 180) {
    while (true) {
      // Stop here
    }
  }
}
