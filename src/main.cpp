#include <heltec.h>
#define SensorPin 3
unsigned long int avgValue;
float b;
int buf[10],temp;

void readTurbidity(); 
void readpH();
void readTDS();

void setup() {
  
  Serial.begin(9600);

 }

void loop() {

  readTurbidity();
  readpH();
  readTDS();

}

void readpH() {
  for(int i=0;i<10;i++)
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)       
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; 
  phValue=3.5*phValue;                   
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");
  delay(800);
  Serial.println(analogRead(3));
}

void readTurbidity() {

  int sensorValue = analogRead(1);
  float voltage = sensorValue * (5.0 / 1024.0);
 
  Serial.println ("Sensor Output (V):");
  Serial.println (voltage);
  Serial.println();
  delay(1000);

}

void readTDS() {
  Serial.println(analogRead(2));

}
