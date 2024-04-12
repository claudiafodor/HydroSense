#include <heltec.h>
#include <string>
#define SensorPin 3
#define TEMPERATURE 18.0
unsigned long int avgValue;
float b;
int buf[10],temp;

void telemetry();

void setup() {
  
  Serial.begin(9600);

 }

void loop() {
  telemetry();
}

float readpH() {
  return analogRead(1)*(5.0/1024/6)*3.5;
}

float readTurbidity() {

  int sensorValue = analogRead(2);
  float voltage = sensorValue * (5.0 / 1024.0);

  // Convert percentage to ppm (since 1% = 1000 ppm)
  double ppm = voltage * 1000.0;

  // According to the formula, 1 ppm = 0.13 NTU
  double ntu = ppm * 0.13;
 
  return ntu;
}

float readTDS() {
  int sensorValue = analogRead(3);
    
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
}