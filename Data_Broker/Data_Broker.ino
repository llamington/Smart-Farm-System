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
Adafruit_MQTT_Publish publishArray[] = {Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/air-humidity"),
Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/air-temperature"), Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/ultraviolet-a"),
Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/ultraviolet-b"), Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/ultraviolet-index"),
Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/soil-humidity"), Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/soil-temperature"),
Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/soil-ph"), Adafruit_MQTT_Publish(&mqtt, mqttUsername "/feeds/battery-percentage")};
#define halt(s) { Serial.println(F( s )); while(1);  }


const byte loRaM0 = 12;
const byte loRaM1 = 9;
const byte rainPin = 7;
unsigned int tips = 0;
const char startDelimiter[] = {'H', 'T', 'A', 'B', 'I', 'M', 'S', 'P', 'C'};
const String address[] = {"air-humidity", "air-temperature", "ultraviolet-a", "ultraviolet-b", "ultraviolet-index", "soil-humidity", "soil-temperature", "soil-ph", "battery-percentage"};
float receivedArray[9];
// float floatReceivedArray[100];

String received;
byte startString;
//int endString;


void setup() {
  // put your setup code here, to run once:
  pinMode(loRaM0, OUTPUT);
  pinMode(loRaM1, OUTPUT);
  pinMode(rainPin, INPUT);
  Serial.begin(9600);
  loRa.begin(9600);
  Ethernet.begin(mac);
  delay(2000);
  Serial.print(F("Initialised"));
  
}

void loop() {
  // put your main code here, to run repeatedly:
  MQTT_connect();
  digitalWrite(loRaM0, LOW);
  digitalWrite(loRaM1, LOW);
  if(digitalRead(rainPin)) {
    tips++;
    delay(500);
    Serial.println(tips);
  }
  if(loRa.available() > 0) {
    received = loRa.readString();
    for(int i = 0; i <= 8; i++) {
      startString = received.indexOf(startDelimiter[i]); // finds index of starting delimiter
      //endString = received.indexOf('>', startString); //reads from the first string until first delimiter
      receivedArray[i] = received.substring(startString+1, received.indexOf('>', startString)).toFloat();
      //floatReceivedArray[i] = receivedArray[i].toFloat();
      Serial.println(address[i] + ": " + receivedArray[i]);
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
