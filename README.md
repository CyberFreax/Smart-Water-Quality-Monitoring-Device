# Smart-Water-Quality-Monitoring-System 💧

This is my Arduino-powered **Smart Water Quality Monitoring System** — a compact device designed to monitor the quality of water at **railway stations**. It measures pH, TDS, turbidity, and temperature using appropriate sensors and displays the values in real-time on a 0.96" OLED screen.

---

## 🔧 What It Does

- Monitors:
  - pH (acidity/alkalinity)
  - TDS (Total Dissolved Solids)
  - Turbidity (water clarity)
  - Temperature
- Displays real-time readings on an OLED screen
- Ideal for deployment at railway stations and public water points
- Compact, low-power, and easy to assemble

---

## 🧰 Parts Used

- Arduino Nano or Uno – 1  
- pH Sensor – 1  
- TDS Sensor – 1  
- Turbidity Sensor – 1  
- DS18B20 Temperature Sensor – 1  
- 0.96" OLED Display (I2C) – 1  
- Jumper Wires  
- Breadboard or custom PCB  
- Battery Pack (5V) or USB power  

---

## 🚀 How to Use

1. Open the Arduino code in the `Arduino/` folder.

2. Install the required libraries in Arduino IDE:
   - `Adafruit SSD1306`
   - `Adafruit GFX`
   - `DallasTemperature`
   - `OneWire`

3. Connect all sensors as described in the code.

4. Upload the code to your Arduino board.

5. Power it on and view live readings on the OLED screen.

---


## 🙌 Credits

- Created by: [Aaditya Sharma](https://github.com/CyberFreax)
