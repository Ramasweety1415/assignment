int t_p=5;
int e_p=18;
float ss=0.034;
long durn;
float dist_cm;

void setup() { 

  Serial.begin(115200);
  pinMode(t_p,OUTPUT);
  pinMode(e_p,INPUT);

}

void loop()
 { 
digitalWrite(t_p,LOW);
delayMicroseconds(2);
digitalWrite(t_p,HIGH);
delayMicroseconds(10);
digitalWrite(t_p,LOW);
durn=pulseIn(e_p,HIGH);
dist_cm=durn*ss/2;
Serial.print("distance= ");
Serial.println(dist_cm);
  delay(1000);
 }  

