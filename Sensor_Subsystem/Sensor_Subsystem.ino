#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>
#include <Adafruit_VEML6075.h>
#include <Servo.h>

Adafruit_VEML6075 uv = Adafruit_VEML6075();
Servo phServo;
const int loRaM0 = 12;
const int loRaM1 = 9;
const int phRelay = 2;
const int phIn = A0;
const int soilMoistureIn = A2;
const int soilTemperatureIn = A1;
const int batteryTest = 3;
const int batteryRead = A3;
int soilMoistureRaw;
int soilRelativeHumidity;
int phRaw;
float uvIndex;
float ph;
float phVoltage;
float uvA;
float uvB;
int ntcRaw;
float ntcVoltage;
float ntcResistance;
float soilTemperature;
int batteryVoltageRaw;
float batteryVoltage;
int batteryPercentage;

void setup() {
  // put your setup code here, to run once:
  pinMode(loRaM0, OUTPUT);
  pinMode(loRaM1, OUTPUT);
  pinMode(phRelay, OUTPUT);
  pinMode(batteryTest, OUTPUT);
  phServo.attach(10);
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(loRaM0, LOW);
  digitalWrite(loRaM1, LOW);
  digitalWrite(phRelay, HIGH);
  digitalWrite(batteryTest, LOW);
  phRaw = analogRead(phIn);
  phVoltage = analogVoltage(phRaw);
  //Serial.println(phVoltage);
  ph = voltageToPh(phVoltage);
  //Serial.println(ph);
  soilMoistureRaw = analogRead(soilMoistureIn);
  soilRelativeHumidity = map(soilMoistureRaw, 855, 385, 0, 100);
  //Serial.println(soilMoistureRaw);
  ntcRaw = analogRead(soilTemperatureIn);
  ntcVoltage = analogVoltage(ntcRaw);
  ntcResistance = voltageDividerResistance(ntcVoltage);
  soilTemperature = steinhart(ntcVoltage);
  batteryVoltageRaw = analogRead(batteryRead);
  batteryVoltage = analogVoltage(batteryVoltageRaw);
  batteryPercentage = voltagePercentage(batteryVoltage);
  Serial.println(batteryPercentage);
  
  //Serial.println(soilRelativeHumidity);
  delay(2000);
  uvIndex = uv.readUVI();
  uvA = uv.readUVA();
  uvB = uv.readUVB();
  
}

float analogVoltage(int x) {
  return x*3.3/1023;
}
float voltageToPh(float x) {
  return 29.347*sq(x)-21.914*x+7.4785;
}
float voltageDividerResistance(float x) {
  return (3.3*pow(10, 4))/x-pow(10, 3);
}
float steinhart(float x) {
  return 1/(1/298.15+(1/3950)*log((x/10*pow(10, 3))));
}
int voltagePercentage(float x) {
  return x*100/3.25;
}
