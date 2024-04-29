#include <heltec.h>
#include <string>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Wire.h>
#include <SPI.h>
#define TEMPERATURE 18.0

float lastTelemetry = 0;

// Network credentials
const char* ssid = "ORBI21";
const char* password = "Smokecat5!";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


float readpH() {
  return analogRead(3)*(5.0/1024/6)*3.5;
}

float readTurbidity() {

  int sensorValue = analogRead(1);
  float voltage = sensorValue * (5.0 / 1024.0);

  // Convert percentage to ppm (since 1% = 1000 ppm)
  double ppm = voltage * 1000.0;

  // According to the formula, 1 ppm = 0.13 NTU
  double ntu = ppm * 0.13;
 
  return ntu;
}

float readTDS() {
  int sensorValue = analogRead(2);
    
  // Convert the analog value to voltage
  float voltage = sensorValue * (5.0 / 1024.0);
  
  // Apply temperature compensation
  float compensationCoefficient = 1.0 + 0.02 * (TEMPERATURE - 25.0);
  float compensatedVoltage = voltage / compensationCoefficient;

  // Convert voltage to TDS value
  float tdsValue = (133.42 * compensatedVoltage * compensatedVoltage * compensatedVoltage
                    - 255.86 * compensatedVoltage * compensatedVoltage
                    + 857.39 * compensatedVoltage) * 0.5;

  return tdsValue;
}

void telemetry() {
  float pH = readpH();
  float turbidity = readTurbidity();
  float tds = readTDS();

  Serial.print("pH: ");
  Serial.print(pH);
  Serial.print(", Turbidity: ");
  Serial.print(turbidity);
  Serial.print(", TDS: ");
  Serial.println(tds);
  Serial.println(WiFi.localIP());
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(9600);

  delay(5000);

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

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
  server.on("/ph", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(readpH()).c_str());
  });
  server.on("/turbidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(readTurbidity()).c_str());
  });
  server.on("/tds", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(readTDS()).c_str());
  });

  // Start server
  server.begin();
}

void loop() {
  if (lastTelemetry + 10000 < millis()) {
    lastTelemetry = millis();
    telemetry();
  }
}