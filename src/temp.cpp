/*#include <heltec.h>
int sensorPin = A0;  // LM35 connected to Analog Pin A0
float temperatureC;   // variable to store temperature in Celsius
float temperatureF;   // variable to store temperature in Fahrenheit

unsigned long previousMillis = 0;  // will store last time temperature was updated
const long interval = 7000;  // interval at which to update temperature (milliseconds)

void setup() {
  Serial.begin(9600);   // initialize serial communication
}

void loop() {
  unsigned long currentMillis = millis();  // get the current time

  // Check if 7 seconds have passed since the last update
  if (currentMillis - previousMillis >= interval) {
    // Save the last time temperature was updated
    previousMillis = currentMillis;

    int sensorValue = analogRead(sensorPin);   // read the sensor value

    temperatureC = (sensorValue * 5.0) / 1023 * 100;   // convert to temperature in Celsius
    temperatureF = (temperatureC * 9 / 5) + 32;   // convert to temperature in Fahrenheit

    Serial.print("Temperature in Celsius: ");
    Serial.print(temperatureC);
    Serial.print("°C");

    Serial.print("  |  ");

    Serial.print("Temperature in Fahrenheit: ");
    Serial.print(temperatureF);
    Serial.println("°F");
  }
  // The loop will continue running, but the temperature update will only happen every 7 seconds.
}
*/