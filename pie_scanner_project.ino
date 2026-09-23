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
  delay(500);
}

void loop() {

  // X sweeps from 0 to 180
  for (x_pos = 0; x_pos <= 90; x_pos ++) {

    Xservo.write(x_pos);
    delay(5);
    Serial.print(" ");
    Serial.print(x_pos);
    Serial.print(" ");
    Serial.print(y_pos);
    Serial.print(" ");
    Serial.print(read_distance());
    Serial.println(" ");

    
  }

  // Y moves down 1 degree
  y_pos += 1;
  Yservo.write(y_pos);
  Xservo.write(0);
  delay(100);

  /*
  // X sweeps from 180 back to 0
  for (x_pos = 90; x_pos >= 0; x_pos --) {

    Xservo.write(x_pos);
    delay(5);
    Serial.print(" ");
    Serial.print(x_pos);
    Serial.print(" ");
    Serial.print(y_pos);
    Serial.print(" ");
    Serial.print(read_distance());
    Serial.println(" ");
  }

  // Y moves down 1 degree
  y_pos += 1;
  Yservo.write(y_pos);
  delay(50);
  */

  // Stop once Y reaches 180
  if (y_pos >= 90) {
    while (true) {
      // Stop here
    }
  }
}

int read_distance() {
  float distance = 0;
  for (int i = 1; i <= 5; i++) {
    int rawValue = analogRead(sensorPin); // Read the raw analog value (0-1023)
    float voltage = rawValue * (5.0 / 1023.0); // Convert raw value to voltage
    // Approximate distance calculation based on GP2Y0A02YK0F datasheet characteristics
    // Note: The output is non-linear; this formula provides a reasonable approximation for 20-150cm.
    distance += 61.543 * pow(voltage, -1.106);
    delay(5);
  }
  distance = distance / 5;
  return distance;
}
