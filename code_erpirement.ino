#define BLYNK_TEMPLATE_ID "TMPLpO7hbx3F"
#define BLYNK_DEVICE_NAME "Stepper Motor"
#define BLYNK_AUTH_TOKEN "SbCXJSuCvkUk2Cgb-SnAKomowcvpadkk"

#define BLYNK_PRINT Serial
#include <Servo.h>
#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
Servo servo;
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "PRANAY";
char pass[] = "noobpranay";

BLYNK_WRITE(V0){
  servo.write(param.asInt());
  }

Stepper my_Stepper(500, D1, D2, D3, D4);

bool Right = false;
bool Left = false;

BLYNK_WRITE(V3)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(D5, LOW);
    Serial.println("LED ON");
  }
  if(value == 0)
  {
     digitalWrite(D5, HIGH);
     Serial.println("LED OFF");
  }
}

BLYNK_WRITE(V4)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(D6, LOW);
    Serial.println("LED ON");
  }
  if(value == 0)
  {
     digitalWrite(D6, HIGH);
     Serial.println("LED OFF");
  }
}

BLYNK_WRITE(V5)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(D7, LOW);
    Serial.println("LED ON");
  }
  if(value == 0)
  {
     digitalWrite(D7, HIGH);
     Serial.println("LED OFF");
  }
}

BLYNK_WRITE(V6)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(D8, LOW);
    Serial.println("LED ON");
  }
  if(value == 0)
  {
     digitalWrite(D8, HIGH);
     Serial.println("LED OFF");
  }
}



void setup(){

  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass); 

    pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  servo.attach(D0);// baudrate for serial comunication
  

  my_Stepper.setSpeed(500);                            // Speed for stepper motor
  
}


BLYNK_WRITE(V1){                                      // read input from virtual pin V1
  Right = param.asInt();                              // assigning incoming value from pin V§1 to a variable
  }
  
BLYNK_WRITE(V2){                                      // read input from virtual pin V2
  Left = param.asInt();                               // assigning incoming value from pin V0 to a variable
  }
  
void Stepper1 (int Direction, int Rotation){          // function for stepper motor control with 2 parameters
  for (int i = 0; i < Rotation; i++){                 // for loop 
  my_Stepper.step(Direction * 200);                   // 200 is 360 degree => change value if smaller then 360 degree is needing
  Blynk.run();
  }
}

void loop() {   
  
  Blynk.run();
  
  if (Right){                                          // if condition 
  Stepper1(1, 10);                                     // steppermotor rotates 10 times 360 degree right
  Serial.println("Right turn");
  }
  delay(10);                                           // delay 20ms
  
  if (Left){                                           // if condition 
  Stepper1(-1, 10);                                    // steppermotor rotates 10 times 360 degree left
  Serial.println("Left turn");
  }
  delay(10);                                           // delay 20ms
}
