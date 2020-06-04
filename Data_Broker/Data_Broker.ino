#include <SD.h>
#include <MemoryFree.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "SoftwareSerial.h"
#include "Ethernet.h"
#include "SPI.h"
#include "Dns.h"
#include "Dhcp.h"

SoftwareSerial loRa(5, 6);
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

#define mqttUsername "llamington"

EthernetClient client;

Adafruit_MQTT_Client mqtt(&client, "io.adafruit.com", 1883, mqttUsername, "4a179569d20d440988bc9cb7d1a75a8f");

#define halt(s) { Serial.println(F( s )); while(1);  }


const byte loRaM0 = 12;
const byte loRaM1 = 9;
const byte rainPin = 7;
const byte chipSelect = 4;
unsigned int tips = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(loRaM0, OUTPUT);
  pinMode(loRaM1, OUTPUT);
  pinMode(rainPin, INPUT);
  Serial.begin(9600);
  loRa.begin(9600);
  Ethernet.begin(mac);
  if (!SD.begin(chipSelect)) {
    Serial.println(F("Card failed, or not present"));
    // don't do anything more:
    while (1);
  }
  Serial.println(F("card initialized."));
  delay(2000);
  Serial.print(F("Initialised"));
  
}

void loop() {
  Adafruit_MQTT_Publish publishArray[] = {Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/air-humidity"),
  Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/air-temperature"), Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/ultraviolet-a"),
  Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/ultraviolet-b"), Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/ultraviolet-index"),
  Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/soil-humidity"), Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/soil-temperature"),
  Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/soil-ph"), Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/battery-percentage")};
  String received;
  byte startString;
  const char startDelimiter[] = {'H', 'T', 'A', 'B', 'I', 'M', 'S', 'P', 'C'};
  float receivedArray[9];
  // put your main code here, to run repeatedly:
  MQTT_connect();
  digitalWrite(loRaM0, LOW);
  digitalWrite(loRaM1, LOW);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if(digitalRead(rainPin)) {
    tips++;
    delay(500);
    Serial.println(tips);
  }
  if(loRa.available() > 0) {
    delay(500);
    if(dataFile){
      dataFile.println(loRa.available());
      dataFile.println(freeMemory());
    }
    received = loRa.readString();
    Serial.println(received);
    if(dataFile){
      dataFile.println(received);
    }
    for(int i = 0; i <= 8; i++) {
      startString = received.indexOf(startDelimiter[i]); // finds index of starting delimiter
      receivedArray[i] = received.substring(startString+1, received.indexOf('>', startString)).toFloat();
      if(dataFile){
        dataFile.println(String(startDelimiter[i]) + ": " + receivedArray[i]);
      }
      publishArray[i].publish(receivedArray[i]);
    }
  }
  delay(100);
}
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print(F("Connecting to MQTT... "));

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println(F("Retrying MQTT connection in 5 seconds..."));
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.println(F("MQTT Connected!"));
}
