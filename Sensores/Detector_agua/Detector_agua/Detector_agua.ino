int WaterSensor;
float WaterSensorPerc;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
WaterSensor= analogRead(A7);
WaterSensorPerc=map(WaterSensor, 0, 624, 0, 100);
Serial.print("Water sensor raw= ");Serial.println(WaterSensor);

Serial.print("Water sensor = ");Serial.println(WaterSensorPerc);
delay(1000);

}
