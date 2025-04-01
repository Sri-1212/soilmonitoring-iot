#define BLYNK_TEMPLATE_ID "TMPL3i5sA80-D"  
#define BLYNK_TEMPLATE_NAME "IOT Based Agriculture System"
#define BLYNK_AUTH_TOKEN "uIauv87Pki2Tq27W2DhnuoiR6VzWqHJ6"  

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN D7     
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "HACKATHON-ISE-25";  
char pass[] = "ise@560064";  

#define LDR_PIN D3
#define RAIN_PIN D6
#define SOIL_PIN A0
#define RELAY_PIN D5

// Initialize DHT sensor


BlynkTimer timer;

void sendSensorData() {
    int ldrValue = analogRead(LDR_PIN);
    int rainValue = analogRead(RAIN_PIN);
    int soilMoistureValue = analogRead(SOIL_PIN);
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    // Send data to Blynk
    Blynk.virtualWrite(V1, ldrValue);
    Blynk.virtualWrite(V2, rainValue);
    Blynk.virtualWrite(V2, soilMoistureValue);
    Blynk.virtualWrite(V3, temp);
    Blynk.virtualWrite(V4, hum);

    // Automatic control of relay based on rain
    if (soilMoistureValue < 500) { // Adjust threshold as needed
        digitalWrite(RELAY_PIN, HIGH); // Turn ON relay
    } else {
        digitalWrite(RELAY_PIN, LOW); // Turn OFF relay
    }
}

void setup() {
    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    
    pinMode(LDR_PIN, INPUT);
    pinMode(RAIN_PIN, INPUT);
    pinMode(SOIL_PIN, INPUT);
    pinMode(DHTPIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    dht.begin();
    timer.setInterval(2000L, sendSensorData);
}

void loop() {
    Blynk.run();
    timer.run();
}


