// Blink details
#define BLYNK_TEMPLATE_ID "blynk"
#define BLYNK_TEMPLATE_NAME "PlantPal"
#define BLYNK_AUTH_TOKEN "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

//Wifi and weathfer API credentials 
#define WIFI_SSID "TeenTechTribe"
#define WIFI_PASS "Passsword"
#define WEATHER_API_KEY "6e0139b28a28446fa3e62318250706"
#define WEATHER_URL "http://api.weatherapi.com/v1/current.json?key=" WEATHER_API_KEY "&q=Bengaluru"

#define SOIL_SENSOR_PIN A0  
#define RELAY_PIN D5  
#define MANUAL_OVERRIDE_PIN V6  

bool manualOverride = false;

BLYNK_WRITE(MANUAL_OVERRIDE_PIN) {
  int value = param.asInt();
  Serial.print(" ");
  Serial.println(value);

  if (value == 1 && !manualOverride) {
    Serial.println("Triggering manual watering...");
    manualOverride = true;
    manualWatering();
  } else {
    Serial.println("No manual action taken.");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
  Serial.println("Boot success full!");
}

void readSoilMoisture() {
    int soilMoistureRaw = analogRead(SOIL_SENSOR_PIN);
    int soilMoisturePercent = map(soilMoistureRaw, 0, 1023, 0, 100);  

    Blynk.virtualWrite(V1, soilMoisturePercent);
    Serial.print("Soil moisture :"); Serial.print(soilMoisturePercent); Serial.println(" %");
}

void waterPlants() {
  digitalWrite(RELAY_PIN, LOW);  
  Blynk.virtualWrite(V5, 1);
  Blynk.logEvent("plant_watering", "Watering plants now ! ");
  Serial.println(" Watering plants...");
  delay(3000); 
  digitalWrite(RELAY_PIN, HIGH);
  Blynk.virtualWrite(V5, 0);
  Serial.println(" Watering complmete.");
}


void manualWatering() {
  digitalWrite(RELAY_PIN, LOW);         
  Blynk.virtualWrite(V5, 1);            
  Serial.println("Manual watering started (pump is on)");
  delay(3000);                          
  digitalWrite(RELAY_PIN, HIGH);        
  Blynk.virtualWrite(V5, 0);           
  Serial.println("Manual watering stopped (pump is off)");
  manualOverride = false;
  Blynk.virtualWrite(MANUAL_OVERRIDE_PIN, 0);
}


void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, WEATHER_URL);
    int httpCode = http.GET();

    if (httpCode == 200) {
      String payload = http.getString();
      
     
      int tempStart = payload.indexOf("\"temp_c\":") + 9;
      int tempEnd = payload.indexOf(",", tempStart);
      String temperature = payload.substring(tempStart, tempEnd);

      int humidityStart = payload.indexOf("\"humidity\":") + 11;
      int humidityEnd = payload.indexOf(",", humidityStart);
      String humidity = payload.substring(humidityStart, humidityEnd);

      int condStart = payload.indexOf("\"text\":\"") + 8;
      int condEnd = payload.indexOf("\"", condStart);
      String condition = payload.substring(condStart, condEnd);

      Blynk.virtualWrite(V2, temperature); 
      Blynk.virtualWrite(V3, humidity);    
      Blynk.virtualWrite(V4, condition);   

      readSoilMoisture(); 

      bool rainExpected = condition.indexOf("Rain") != -1;

    
      if (manualOverride || (analogRead(SOIL_SENSOR_PIN) < 600 && !rainExpected)) {
        waterPlants();
      }
    } else {
      Serial.println(" Failed to retrieve weather data!");
    }

    http.end();
  }

  Blynk.run();
  delay(10000); // delay for next moisture check
}
