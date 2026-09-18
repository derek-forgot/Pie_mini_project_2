const int sensorPin = A0; // Select the input pin for the sensor

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  int rawValue = analogRead(sensorPin); // Read the raw analog value (0-1023)
  float voltage = rawValue * (5.0 / 1023.0); // Convert raw value to voltage
  
  // Approximate distance calculation based on GP2Y0A02YK0F datasheet characteristics
  // Note: The output is non-linear; this formula provides a reasonable approximation for 20-150cm.
  float distance = 61.543 * pow(voltage, -1.106); 

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V  ->  Approx Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500); // Wait half a second between readings
}
