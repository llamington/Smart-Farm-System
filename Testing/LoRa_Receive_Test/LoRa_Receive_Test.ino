#include <SoftwareSerial.h>
const int loRaM0 = 12;
const int loRaM1 = 9;
SoftwareSerial loRa(5,6);
String serialBuffer;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(loRaM0, OUTPUT);
  pinMode(loRaM1, OUTPUT);
  loRa.begin(9600);
  Serial.println("initialising");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(loRaM0, LOW);
  digitalWrite(loRaM1, LOW);
  if(loRa.available() > 0) {
    serialBuffer = loRa.readString();
    Serial.println(serialBuffer);
  }
  delay(1000);
}
