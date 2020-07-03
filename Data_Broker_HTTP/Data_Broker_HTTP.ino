#include <SoftwareSerial.h>
#include <Ethernet.h>
#include <SPI.h>

SoftwareSerial loRa(5, 6);
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
char server[] = "192.168.1.9";

EthernetClient client;


const byte loRaM0 = 3;
const byte loRaM1 = 9;
const byte rainPin = 7;
unsigned int tips = 0;

String received;
byte startString;


void setup() {
  // put your setup code here, to run once:
  pinMode(loRaM0, OUTPUT);
  pinMode(loRaM1, OUTPUT);
  pinMode(rainPin, INPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  loRa.begin(9600); 
  Ethernet.begin(mac);
  delay(2000);
  Serial.print(F("Initialised")); 
  
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
  if(loRa.available()) {
    delay(500);
    Serial.println(loRa.available());
    received = loRa.readString();
    Serial.println(received);
     if (client.connect(server, 5000)) {
      client.print(F("GET /?data="));
      client.print(received);
      client.println(F(" HTTP/1.1"));
      client.println(F("Host: 192.168.1.11"));
      client.println(F("Connection: Close"));
      client.println();
      client.println();
      client.stop();
      Serial.println(F("Sent Request"));
    }
    else {
      Serial.println(F("Connection Failed"));
    } 
  } 
}
