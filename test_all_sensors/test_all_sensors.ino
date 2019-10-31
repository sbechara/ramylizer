// Pin to read the sensor value from
const int analogPin0 = 0;
const int analogPin1 = 1;
const int analogPin2 = 2;
const int analogPin3 = 3;
const int analogPin4 = 4;
const int analogPin5 = 5;

int sensorReading = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {
  
  sensorReading = analogRead(analogPin2);
  Serial.println(sensorReading);
  
  delay(500);
}
