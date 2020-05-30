#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>
#include <Adafruit_VEML6075.h>

SoftwareSerial loRa(5, 6);

Adafruit_BME280 bme;
Adafruit_VEML6075 uv = Adafruit_VEML6075();
const int loRaM0 = 12;
const int loRaM1 = 9;
const int phIn = A0;
const int soilMoistureIn = A2;
const int soilTemperatureIn = A1;
const int batteryTest = 3;
const int batteryRead = A3;
int soilMoistureRaw;
float soilRelativeHumidity;
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
float batteryPercentage;
float humidity;
float pressure;
float temperature;
char startDelimiter[] = {'H', 'T', 'A','B', 'I', 'M', 'S', 'P', 'C'}; //Starting delimiter to send to through serial before value
String value[9];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("Initialising..."));
  loRa.begin(9600);
  pinMode(loRaM0, OUTPUT);
  pinMode(loRaM1, OUTPUT);
  //pinMode(phRelay, OUTPUT);
  pinMode(batteryTest, OUTPUT);
  bme.begin(0x76);
  uv.begin();
  delay(2000);
  Serial.println(F("Initialised"));
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(loRaM0, LOW);
  digitalWrite(loRaM1, LOW);
  //digitalWrite(phRelay, HIGH);
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
  soilTemperature = steinhart(ntcResistance);
  batteryVoltageRaw = analogRead(batteryRead);
  batteryVoltage = analogVoltage(batteryVoltageRaw);
  batteryPercentage = voltagePercentage(batteryVoltage);
 // Serial.println(batteryPercentage);
  //Serial.println(soilRelativeHumidity);
  uvIndex = uv.readUVI();
  uvA = uv.readUVA();
  uvB = uv.readUVB();
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure();
  //Serial.println(uvB);
  //Serial.println("T" + temperature + ">");
  float values[] = {humidity, temperature, uvA, uvB, uvIndex, soilRelativeHumidity, soilTemperature, ph, batteryPercentage};
   for(int i = 0; i < 9; i++) {
    //Serial.println(values[i]);
    //Serial.print(values[i]);
    value[i] = String(values[i], 2);
    Serial.println(startDelimiter[i] + value[i] + '>');
    loRa.print(startDelimiter[i] + value[i] + '>');
  }
  delay(10000);
}

float analogVoltage(int x) {
  return x*3.3/1023.0;
}
float voltageToPh(float x) {
  return 29.347*sq(x)-21.914*x+7.4785;
}
float voltageDividerResistance(float x) {
  return (x*10.0E3)/(3.3-x);
}
float steinhart(float x) {
  return 1.0/((1.0/298.15)-(1.0/3950.0)*log((x/10.0E3))) - 273.15;
}
float voltagePercentage(float x) {
  return x*100.0/3.25;
}
