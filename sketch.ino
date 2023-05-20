
int pinSensor =2;
int pinLed =12;
int pinBuzzer=13;
int pirSensor=0;

void setup()
{ 
  pinMode(2, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop()
{ 

  pinSensor = digitalRead(pinSensor);
  if (pinSensor == HIGH)
  { 

    digitalWrite(pinLed, HIGH);
    tone(pinBuzzer,1000,500);

  }

  digitalWrite(pinLed, LOW);

}
