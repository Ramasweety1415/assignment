/* How to use the DHT-22 sensor with Arduino uno.
   Is a temperature and humidity sensor! 
   See it in original form: 
   https://create.arduino.cc/projecthub/mafzal/temperature-monitoring-with-dht22-arduino-15b013
*/
//LCD I2C library:
#include <LiquidCrystal_I2C.h>
//DHT22 sensor library:
#include <DHT.h>;
//LCD I2C address 0x27, 16 column and 2 rows!
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Constants:
#define DHTPIN 2          //what pin we're connected to
#define DHTTYPE DHT22     //DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //Initialize DHT sensor for normal 16mhz Arduino
//Variables:
int chk;
float H; //Humidity value
float T; //Temperature value
int buzzer = 12;

//Initialize LCD, DHT22 sensor and buzzer:
void setup(){
  lcd.init(); lcd.backlight();  dht.begin();  pinMode(buzzer, OUTPUT);
  //Print some text in Serial Monitor
  Serial.begin(9600);  Serial.println("DHT22 sensor with Arduino Uno R3!");
  pinMode(9, OUTPUT);  pinMode(10, OUTPUT);  pinMode(11, OUTPUT);
}

void loop(){
  delay(2000);
  //Read data and store it to variables hum and temp
  H = dht.readHumidity();  T = dht.readTemperature();
  
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(H);
  Serial.println(" %; ");
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" Celsius.\n");
  
  /*If humidity is higher than 70% & 
  temperature is higher than 30 degrees Celsius 
  then it will show on LCD „Too warm! Cool down!”*/
  if(H >= 70.00 && T >= 30.00){
    digitalWrite(9, HIGH);  digitalWrite(10, LOW);  digitalWrite(11, LOW);
   
    lcd.println("   Too warm!    ");
    lcd.setCursor(0, 1);
    lcd.println("   Cool down!   ");
    lcd.setCursor(0, 0);
   
    digitalWrite(buzzer, 1); tone(buzzer, 900, 100);
    delay(400);
    digitalWrite(buzzer, 0); tone(buzzer, 900, 100);
    delay(400);
    digitalWrite(buzzer, 1); tone(buzzer, 900, 100);
    delay(400);
    digitalWrite(buzzer, 0); tone(buzzer, 900, 100);
    delay(400);
  }else{
  /*If humidity is lower than 70% & 
  temperature is lower than 30 degrees Celsius 
  then it will show on LCD „Temp. & hum. are in normal limits”*/
    digitalWrite(9, LOW);  digitalWrite(10, LOW);  digitalWrite(11, HIGH);
    lcd.println("Temp. & hum. are");  lcd.setCursor(0, 1);
    lcd.println("in normal limits");  lcd.setCursor(0, 0);
    digitalWrite(buzzer, 0);
  }
  
  /*If either humidity is lower than 70%, but 
  temperature is higher than 30 degrees Celsius, 
  then it will show on LCD „Be ware! Temp. too high” or
  humidity is higher than 70%, but 
  temperature is lower than 30 degrees Celsius, then
  it will show on LCD „Be ware! Hum. too high”*/
  if(H < 70.00 && T >= 30.00){
    digitalWrite(9, LOW);  digitalWrite(10, HIGH);  digitalWrite(11, LOW);
    lcd.println("Be ware!        ");  lcd.setCursor(0, 1);
    lcd.println("Temp. too high! ");  lcd.setCursor(0, 0);
    digitalWrite(buzzer, 1); tone(buzzer, 400, 400);  delay(400);
    digitalWrite(buzzer, 0); tone(buzzer, 400, 400);  delay(400);
  }
  if(H >= 70.00 && T < 30.00){
    digitalWrite(9, LOW);  digitalWrite(10, HIGH);  digitalWrite(11, LOW);
    lcd.println("Be ware!        ");  lcd.setCursor(0, 1);
    lcd.println("Hum. too high!  ");  lcd.setCursor(0, 0);
    digitalWrite(buzzer, 1); tone(buzzer, 400, 400);  delay(400);
    digitalWrite(buzzer, 0); tone(buzzer, 400, 400);  delay(400);
  }
}
