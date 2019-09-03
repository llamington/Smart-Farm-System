#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
char tempChar[7]; //store temp in a char array
char humidChar[7];
char latitudeChar[15];
char longitudeChar[15];

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  dht.begin();
  pinMode(2, INPUT);
}

void loop() {
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  float latitude = -44.372258;
  float longitude = 171.218825;
  //Serial.println(latitude, 6);
  //Serial.println(longitude, 6);
  String tempString = 'T' + String(temp, 1) + '>'; //add start and finish delimiters to the string
  tempString.toCharArray(tempChar, 7); //turn string to char array
  String latitudeString = 'L' + String(latitude, 6) + '>'; //add start and finish delimiters to the string
 // Serial.print(latitudeString);
  tempString.toCharArray(latitudeChar, 15); //turn string to char array
  String longitudeString = 'l' + String(longitude, 6) + '>'; //add start and finish delimiters to the string
  tempString.toCharArray(longitudeChar, 15); //turn string to char array
  String humidString = 'H' + String(humid, 1) + '>';
  humidString.toCharArray(humidChar, 7);
  
  for(int i = 0; i < 7; i++) { //repeat 7 times:
    Serial.print(tempChar[i]); //print the array at the 'ith' index of the char array
    delay(1); //wait 1ms before printing the next char in the array
  }
  delay(1);
  for(int i = 0; i < 7; i++) {
    Serial.print(humidChar[i]);
    delay(1);
  }
  /* delay(1);
  for(int i = 0; i < 15; i++) { //repeat 7 times:
    Serial.print(longitudeChar[i]); //print the array at the 'ith' index of the char array
    delay(1); //wait 1ms before printing the next char in the array
  }
  delay(1);
    for(int i = 0; i < 15; i++) { //repeat 7 times:
    Serial.print(longitudeChar[i]); //print the array at the 'ith' index of the char array
    delay(1); //wait 1ms before printing the next char in the array
  } */
  delay(5000);
}
