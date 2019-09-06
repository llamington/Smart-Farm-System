#include <SoftwareSerial.h>
#include <Ethernet.h>

SoftwareSerial loRa(5, 6);

const int loRaM0 = 12;
const int loRaM1 = 9;
const int rainPin = 7;
int tips = 0;
String loRaBuffer;

void setup() {
  // put your setup code here, to run once:
  pinMode(loRaM0, OUTPUT);
  pinMode(loRaM1, OUTPUT);
  pinMode(rainPin, INPUT);
  Serial.begin(9600);
  loRa.begin(9600);
  
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
    loRaBuffer = loRa.readStringUntil('>');
    Serial.println(loRaBuffer);
  }
   delay(1000);
  
}
