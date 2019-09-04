#include <SoftwareSerial.h>
const int loRaM0 = 12;
const int loRaM1 = 9;
byte byteArray[] = {0xC1, 0x00, 0x04}; //change this array with the desired command
SoftwareSerial loRa(5,6);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  loRa.begin(9600);
  pinMode(loRaM0, OUTPUT);
  pinMode(loRaM1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(loRaM0, LOW);
  digitalWrite(loRaM1, HIGH);
  for(int i; i <= sizeof(byteArray) - 1; i++) {
    loRa.write(byteArray[i]);
    //Serial.print(byteArray[i], HEX);
  }   
  byte hi[32];
  if(loRa.available() > 0) {
    loRa.readBytes(hi, sizeof(hi));
  }
  for(int i; i <= sizeof(hi) - 1; i++) {
    Serial.print(hi[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(1000);

}
