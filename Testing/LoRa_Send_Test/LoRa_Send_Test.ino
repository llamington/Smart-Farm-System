const int loRaM0 = 12;
const int loRaM1 = 9;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(loRaM0, LOW);
  digitalWrite(loRaM1, LOW);
  Serial.println("Hello World");
  delay(1000);
}
