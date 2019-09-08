#include <SoftwareSerial.h>
#include <Ethernet.h>

SoftwareSerial loRa(5, 6);

float uvIndex;
float ph;
float phVoltage;
float uvA;
float uvB;
float soilTemperature;
float batteryPercentage;
float humidity;
float pressure;
float temperature;
float soilRelativeHumidity;
const int loRaM0 = 12;
const int loRaM1 = 9;
const int rainPin = 7;
int tips = 0;
String loRaBuffer;
String stringValues[8];
String floatValues[8];
char startDelimiter[] = {'H', 'T', 'A', 'B', 'I', 'M', 'S', 'P', 'C'};
float values[] = {humidity, temperature, uvA, uvB, uvIndex, soilRelativeHumidity, soilTemperature, ph, batteryPercentage};
String hello;


void setup() {
  // put your setup code here, to run once:
  pinMode(loRaM0, OUTPUT);
  pinMode(loRaM1, OUTPUT);
  pinMode(rainPin, INPUT);
  Serial.begin(9600);
  loRa.begin(9600);
  delay(2000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(loRaM0, LOW);
  digitalWrite(loRaM1, LOW);
  if(digitalRead(rainPin)) {
    tips++;
    delay(500);
    Serial.println(tips);
  }
  while(loRa.available() > 0) {
    Serial.println(loRa.readString());
  }
  /* while(loRa.available() > 0) {
      for(int i = 0; i <= 8; i++) {
       while(loRa.read() != startDelimiter[i]) {
        loRa.read();
    }
    stringValues[i] = loRa.readStringUntil('>');
    Serial.println(stringValues[i]);
  }
   delay(1000);
} */
}
