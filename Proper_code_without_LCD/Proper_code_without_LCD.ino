#include <DHT.h>  // include the DHT library

const int FLOAT_SWITCH_PIN = 2;  // pin connected to float switch
const int SOIL_MOISTURE_PIN = A0;  // pin connected to soil moisture sensor
const int DHT_PIN = 3;  // pin connected to the DHT sensor
const int MOTOR1_CONTROL_PIN = 9;  // pin used to control motor 1
const int MOTOR2_CONTROL_PIN = 10;  // pin used to control motor 2
const int MOTOR3_CONTROL_PIN = 11;  // pin used to control motor 3
const float TEMPERATURE_THRESHOLD = 32;  // temperature threshold in degrees Celsius

DHT dht(DHT_PIN, DHT11);  // create a DHT object

void setup() {
  pinMode(FLOAT_SWITCH_PIN, INPUT);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(MOTOR1_CONTROL_PIN, OUTPUT);
  pinMode(MOTOR2_CONTROL_PIN, OUTPUT);
  pinMode(MOTOR3_CONTROL_PIN, OUTPUT);
  dht.begin();
}

void loop() {
  // Read the float switch state
  int floatSwitchState = digitalRead(FLOAT_SWITCH_PIN);

  // If the tank is full, turn off motor 1. Otherwise, turn it on.
  if (floatSwitchState == HIGH) {
    digitalWrite(MOTOR1_CONTROL_PIN, LOW);
  } else {
    digitalWrite(MOTOR1_CONTROL_PIN, HIGH);
  }

  // Read the soil moisture level
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);

  // If the soil is dry, turn on motor 2. Otherwise, turn it off.
  if (soilMoisture < 500) {  // adjust this threshold as needed
    digitalWrite(MOTOR2_CONTROL_PIN, HIGH);
  } else {
    digitalWrite(MOTOR2_CONTROL_PIN, LOW);
  }

  // Read the temperature from the DHT sensor
  float temperature = dht.readTemperature();

  // If the temperature is above the threshold and the soil is not moist, turn on motor 3.
  // Otherwise, turn it off.
  if (temperature > TEMPERATURE_THRESHOLD && soilMoisture >= 500) {
    digitalWrite(MOTOR3_CONTROL_PIN, HIGH);
  } else {
    digitalWrite(MOTOR3_CONTROL_PIN, LOW);
  }
}
