🌱 PlantPal – Smart Urban Plant Care System
PlantPal is a smart, IoT-enabled plant care system designed to automate irrigation for urban gardens using real-time soil and weather data. Built using affordable, open-source hardware and integrated with the Blynk platform, it ensures efficient, data-driven watering to conserve water and promote healthy plant growth.

🔧 Features
🌡 DHT11 Sensor – Measures ambient temperature and humidity.

🌱 Soil Moisture Sensor – Monitors moisture level in the soil.

☁️ Weather Forecast Integration – Pulls real-time weather data from Blynk Cloud to avoid watering before rain.

💧 Automated Pump Control – Activates a water pump only when the plant needs water.

📱 Blynk App Dashboard – Displays sensor data, alerts, and allows manual override.

🧠 How It Works
The ESP8266 microcontroller reads soil and atmospheric data from sensors.

The system checks weather forecasts via the Blynk IoT platform.

If the soil is dry and no rain is expected, the pump is triggered to water the plant.

Data is displayed in real time on the Blynk mobile app, with options for manual control.

🛠 Hardware Used
ESP8266 NodeMCU

DHT11 Temperature & Humidity Sensor

Soil Moisture Sensor

Relay Module

Mini Water Pump

Power Supply (5V–12V)

Jumper Wires, Breadboard (or PCB for final version)

📲 Software & Tools
Arduino IDE

Blynk IoT Platform (mobile app + cloud)

Weather API (via Blynk)

GitHub (for code management)

🚀 Current Status
✅ Prototype built and tested
✅ Functional with real-time automation
🔜 Final casing/enclosure in progress
🔜 Preparing for pilot deployment and feedback

👥 Team
Tanmay S U – Hardware and electronics

Dyutikar G V – Software development and IoT integration

Hridan Saikia – UI/UX design via Blynk

[Open Role] – Looking to onboard a team member for marketing and business development

📦 Future Plans
3D-printed casing for durable deployment

Expand to smart garden kits for multiple plants

Add fertilizer control and light monitoring in future versions

List on online marketplaces (e.g., Amazon, Flipkart)

🤝 Contributing
We welcome contributions, suggestions, and collaborations! Feel free to fork, raise issues, or open pull requests to make PlantPal better.

📜 License
This project is open-source and available under the MIT License.
