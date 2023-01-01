int Index;


void setup()

{

  pinMode(6, OUTPUT); //Enable

  pinMode(5, OUTPUT); //Step

  pinMode(4, OUTPUT); //Direction


  digitalWrite(6,LOW);

}


void loop()

{

  digitalWrite(4,HIGH);


  for(Index = 0; Index < 20000; Index++)

  {

    digitalWrite(5,HIGH);

    delayMicroseconds(200);

    digitalWrite(5,LOW);

    delayMicroseconds(200);

  }

  delay(10000);


  digitalWrite(4,LOW);


  for(Index = 0; Index < 20000; Index++)

  {

    digitalWrite(5,HIGH);

    delayMicroseconds(200);

    digitalWrite(5,LOW);

    delayMicroseconds(200);

  }

  delay(10000);

}
