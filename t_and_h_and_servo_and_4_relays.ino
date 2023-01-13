#include <Servo.h>
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

Servo servo;

char auth[] = "YourAuthToken"; // Replace with your Blynk auth token
char ssid[] = "YourNetworkName"; // Replace with your Wi-Fi name
char pass[] = "YourNetworkPassword"; // Replace with your Wi-Fi password

const int relay1 = D1;
const int relay2 = D2;
const int relay3 = D3;
const int relay4 = D4;

#define DHTPIN D2          // Digital pin 4

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

BLYNK_WRITE(V3) {
  int pinValue = param.asInt();
  digitalWrite(relay1, pinValue);
}

BLYNK_WRITE(V4) {
  int pinValue = param.asInt();
  digitalWrite(relay2, pinValue);
}

BLYNK_WRITE(V5) {
  int pinValue = param.asInt();
  digitalWrite(relay3, pinValue);
}

BLYNK_WRITE(V6) {
  int pinValue = param.asInt();
  digitalWrite(relay4, pinValue);
}

BLYNK_WRITE(V0) {
  servo.write(param.asInt());
}

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, h);  //V5 is for Humidity
  Blynk.virtualWrite(V1, t);  //V6 is for Temperature
}

void setup() {
  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);

// Set pin modes
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);
servo.attach(D0); //set the D1 pin of the servo to D0

// Initial state for relays
digitalWrite(relay1, LOW);
digitalWrite(relay2, LOW);
digitalWrite(relay3, LOW);
digitalWrite(relay4, LOW);

Serial.begin(9600); // See the connection status in Serial Monitor
dht.begin();

// Setup a function to be called every second
timer.setInterval(1000L, sendSensor);
}

void loop() {
Blynk.run();
timer.run();
}
