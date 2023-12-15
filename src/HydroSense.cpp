// Import required libraries
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Wire.h>


#include <SPI.h>
/*#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// Replace with your network credentials
const char* ssid = "CoStCoE";
const char* password = "CSAEA@244C";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readTurbidity() {
  int sensorValue = analogRead(A0);
  float Turbidity = sensorValue * (5.0 / 1024.0);

  if (Turbidity >= 20) {
    return String("");
  }
  else {
    return String(Turbidity);
  }
}

String readTDS() {

}

String readTemp() {
  int sensorPin = A0;  // LM35 connected to Analog Pin A0
  int sensorValue = analogRead(sensorPin);   // read the sensor value
  float temperatureC = (sensorValue * 5.0) / 1023 * 100;   // convert to temperature in Celsius
  
  if (temperatureC >= 100) {
    return String("");
  }
  else {
    return String(temperatureC);
  }

}

String readPh() {

}
void setup(){
  // Serial port for debugging purposes
  Serial.begin(9600);
  
  bool status; 
  

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTurbidity().c_str());
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}
