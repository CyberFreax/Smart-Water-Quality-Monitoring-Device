#include <EEPROM.h>
#include "GravityTDS.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ONE_WIRE_BUS 7
#define TdsSensorPin A1
#define TurbiditySensorPin A0
#define PhSensorPin A3  // pH sensor pin set to A3

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
GravityTDS gravityTds;

float tdsValue = 0;
float phValue = 0;
float temperature = 0;
int phBuf[10];
int temp;

void setup()
{
  Serial.begin(115200);
  sensors.begin();
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);
  gravityTds.setAdcRange(1024);
  gravityTds.begin();

  // Initialize I2C using default A4/A5 pins
  Wire.begin();

  // OLED initialization
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Water Test Starting...");
  display.display();
  delay(2000);
}

void loop()
{
  // ==== Temperature + TDS ====
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  gravityTds.setTemperature(temperature);
  gravityTds.update();
  tdsValue = gravityTds.getTdsValue();

  // ==== Turbidity ====
  int turbiditySensorValue = analogRead(TurbiditySensorPin);
  float turbidityVoltage = turbiditySensorValue * (5.0 / 1024.0);

  // ==== pH Reading ====
  unsigned long int avgPh = 0;
  for (int i = 0; i < 10; i++) {
    phBuf[i] = analogRead(PhSensorPin);  // Reading from A3
    delay(10);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (phBuf[i] > phBuf[j]) {
        temp = phBuf[i];
        phBuf[i] = phBuf[j];
        phBuf[j] = temp;
      }
    }
  }
  for (int i = 2; i < 8; i++) {
    avgPh += phBuf[i];
  }
  float phVoltage = (float)avgPh * 5.0 / 1024 / 6;
  phValue = 3.5 * phVoltage;

  // ==== Check Conditions ====
  bool isDrinkable = (tdsValue <= 350 && turbidityVoltage >= 3.9 && phValue >= 6.5 && phValue <= 8.5);

  // ==== Display Result on OLED ====
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  if (isDrinkable) {
    display.println("Drinkable");
  } else {
    display.println("Not");
    display.println("Drinkable");
  }

  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("pH: ");
  display.print(phValue, 2);
  display.display();

  // ==== Output All Readings to Serial Monitor ====
  Serial.print("TDS: ");
  Serial.print(tdsValue, 0);
  Serial.print(" ppm, ");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, ");
  Serial.print("Turbidity Voltage: ");
  Serial.print(turbidityVoltage, 2);
  Serial.print(" V, ");
  Serial.print("pH Value: ");
  Serial.println(phValue, 2);

  // ==== Check Drinkability ====
  if (isDrinkable) {
    Serial.println("Water is Drinkable");
  } else {
    Serial.println("Water is NOT Drinkable");
  }

  Serial.println();
  delay(2000);
}
