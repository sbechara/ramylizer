const int analogPin = 0;
int sensorReading = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  sensorReading = analogRead(analogPin);
  Serial.println(sensorReading);
  delay(10);
}
