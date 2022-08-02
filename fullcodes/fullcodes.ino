#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11);
#define MQ2pin (0)
LiquidCrystal_I2C lcd(0x27,20,4);
int _timeout;
String _buffer;
String number = "+250788750979";

int green = 3;
int red = 4;
int buzzer = 5;
int valve = 12;

float sensorValue;
int sensorThreshold = 0,pstatus=0;
void setup() {
  Serial.begin(9600);
  _buffer.reserve(50);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(valve, OUTPUT);
  digitalWrite(valve, HIGH);
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Gas leakage");
  lcd.setCursor(5,1);
  lcd.print("detector");
  delay(3000);
  lcd.clear();
  lcd.print("System");
  lcd.setCursor(0,1);
  lcd.print("Starting");
  delay(20000);
}

void loop() {
  sensorValue = analogRead(MQ2pin);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Normal");
  lcd.setCursor(0,1);
  lcd.print(sensorValue);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  noTone(buzzer);
  if (sensorValue > sensorThreshold && pstatus==0)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas leakage");
    lcd.setCursor(0,1);
    lcd.print("Detected");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas leakage");
    lcd.setCursor(0,1);
    lcd.print(sensorValue);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    pstatus=1;
  }
  if (sensorValue > sensorThreshold && pstatus==1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas leakage");
    lcd.setCursor(0,1);
    lcd.print("Detected");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas leakage");
    lcd.setCursor(0,1);
    lcd.print(sensorValue);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    pstatus=2;
    sendsms();
  }
  if (sensorValue > sensorThreshold && pstatus==2)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas leakage");
    lcd.setCursor(0,1);
    lcd.print("Detected");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas leakage");
    lcd.setCursor(0,1);
    lcd.print(sensorValue);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    pstatus=3;
    call();
  }
  if (sensorValue > sensorThreshold && pstatus==3)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas leakage");
    lcd.setCursor(0,1);
    lcd.print("Detected");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas leakage");
    lcd.setCursor(0,1);
    lcd.print(sensorValue);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    delay(1000);
    tone(buzzer, 1000, 500);
    digitalWrite(valve, LOW);
    pstatus=4;
    sendclosesms();
  }
  delay(2000);
}
void sendsms(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sending SMS");
  delay(500);
  sim.println("AT+CMGF=1");
  delay(200);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(200);
  String SMS = "Hello, gas leakage detected please check";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(200);
  _buffer = _readSerial();
  delay(2000);
  }
void sendclosesms(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Close SMS send");
  lcd.clear();
  lcd.setCursor(0,0);
  delay(500);
  lcd.print("Sending SMS");
  sim.println("AT+CMGF=1");
  delay(200);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(200);
  String SMS = "Hello, gas leakage detected and gas is closed to avoid accident please check";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(200);
  _buffer = _readSerial();
  delay(2000);
  delay(2000);
  }
void call(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calling");
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
  delay(2000);
  }
String _readSerial() {
_timeout = 0;
while (!sim.available() && _timeout < 12000 )
{
delay(13);
_timeout++;
}
if (sim.available()) {
return sim.readString();
}
}
