#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
char auth[] = "YOUR_AUTH_TOKEN";

// Your WiFi credentials.
char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";

// The pins for the relays
const int relayPins[] = {D1, D2, D3, D4};

// The pin for the DHT11 sensor
const int dhtPin = D5;

// The LCD I2C address
const int lcdAddress = 0x27;

// The SDA and SCL pins for the I2C module
const int sdaPin = D6;
const int sclPin = D7;

// The DHT sensor object
DHT dht(dhtPin, DHT11);

// The LCD object
LiquidCrystal_I2C lcd(lcdAddress, 16, 2);

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
  
  Wire.begin(sdaPin, sclPin);
  
  Blynk.begin(auth, ssid, pass);
  
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop() {
  Blynk.run();
  
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  
  delay(1000);
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  digitalWrite(relayPins[0], pinValue);
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  digitalWrite(relayPins[1], pinValue);
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt();
  digitalWrite(relayPins[2], pinValue);
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt();
  digitalWrite(relayPins[3], pinValue);
}
