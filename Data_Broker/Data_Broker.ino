#include <SoftwareSerial.h>
#include <Ethernet.h>

SoftwareSerial loRa(5, 6);

const int loRaM0 = 12;
const int loRaM1 = 9;
const int rainPin = 7;
int tips = 0;
void setup() {
  // put your setup code here, to run once:
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
  
}
