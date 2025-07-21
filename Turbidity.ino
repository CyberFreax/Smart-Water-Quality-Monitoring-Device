
void setup() {
  Serial.begin(9600);
 
}
void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1024.0);
 
  Serial.println ("Sensor Output (V):");
  Serial.println (voltage);

  if (voltage >= 4) {
    Serial.println("Water is clean and fit for drinking.");
  } else if (voltage >= 3.5) {
    Serial.println("Water is slightly turbid. Consider filtering.");
  } else {
    Serial.println("Water is highly turbid and NOT safe for drinking!");
  }
  Serial.println();
  delay(1000);
}