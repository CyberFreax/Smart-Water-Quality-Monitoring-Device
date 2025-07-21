#include <OneWire.h>
#include <DallasTemperature.h>

// Define the digital pin for KY-001 Data Output (DO)
#define ONE_WIRE_BUS 2  

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();  // Request temperature reading

  float Celsius = sensors.getTempCByIndex(0);
  
  // Check if the sensor is connected
  if (Celsius == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: KY-001 sensor not detected!");
  } else {
    float Fahrenheit = sensors.toFahrenheit(Celsius);
    Serial.print("Temperature: ");
    Serial.print(Celsius);
    Serial.print(" °C  /  ");
    Serial.print(Fahrenheit);
    Serial.println(" °F");
  }

  delay(1000);  // Wait 1 second before next reading
}
    