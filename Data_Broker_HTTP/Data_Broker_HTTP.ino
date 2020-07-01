#include <SoftwareSerial.h>
#include <Ethernet.h>
#include <SPI.h>

SoftwareSerial loRa(5, 6);
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
char server[] = "192.168.1.11";

EthernetClient client;


const byte loRaM0 = 3;
const byte loRaM1 = 9;
const byte rainPin = 7;
unsigned int tips = 0;

IPAddress ip(192,168,1,254);
byte gateway[] = { 
  150,101,0,4 }; // internet access via router
byte subnet[] = { 
  255, 255, 255, 0 }; //subnet mask

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
  Ethernet.begin(mac, ip, gateway, subnet);
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
    Serial.print("hello");
    delay(500);
    Serial.println(loRa.available());
    received = loRa.readString();
    Serial.println(received);
    /* if (client.connect(server, 5000)) {
      client.print("GET /?data=");
      client.print(received);
      client.println(" HTTP/1.1");
      client.println("Host: 192.168.1.11");
      client.println("Connection: Close");
      client.println();
      client.println();
      client.stop();
      Serial.println("Sent Request");
    }
    else {
      Serial.println("Connection Failed");
    } */
  } 
}
