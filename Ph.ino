#define SensorPin A0  // pH meter analog output connected to Arduino analog pin A0

unsigned long int avgValue;  // Store the average value of the sensor feedback
int buf[10];  // Array to store samples
int temp;     // Temporary variable for sorting

void setup() {
  pinMode(13, OUTPUT);       // On-board LED for indication
  Serial.begin(9600);        // Start serial communication
  Serial.println("Ready");   // Test message
}

void loop() {
  for (int i = 0; i < 10; i++) {       // Take 10 samples
    buf[i] = analogRead(SensorPin);
    delay(10);
  }

  // Sort the array from smallest to largest
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }

  // Average the middle 6 values (to remove noise)
  avgValue = 0;
  for (int i = 2; i < 8; i++) {
    avgValue += buf[i];
  }

  float voltage = (float)avgValue * 5.0 / 1024 / 6;  // Convert to voltage
  float phValue = 3.5 * voltage;                     // Convert voltage to pH value

  Serial.print("pH Value: ");
  Serial.println(phValue, 2);  // Print with 2 decimal places

  digitalWrite(13, HIGH);  // Blink LED to show activity
  delay(800);
  digitalWrite(13, LOW);
  delay(200);
}
