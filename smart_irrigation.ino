#include <LiquidCrystal.h>
const int temperatureSensor = A0;
const int moistureSensor = A1;
const int waterPump = 13;
const int redLed_Temperature = 12;
const int redLed_Moisture = 9;
const int greenLed_Temperature = 11;
const int greenLed_Moisture = 10;
const int buzzer = 8;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
void setup() {
Serial.begin(9600);
pinMode(buzzer, OUTPUT);
lcd.begin(16, 2);
lcd.print("Smart Irrigation");
lcd.setCursor(0,1);
lcd.print(" System");
delay(3000);
pinMode(redLed_Moisture, OUTPUT);
pinMode(greenLed_Moisture, OUTPUT);
pinMode(redLed_Temperature, OUTPUT);
pinMode(greenLed_Temperature, OUTPUT);
pinMode(waterPump, OUTPUT);
delay(2000);
lcd.clear();
lcd.print("Temp=");
lcd.setCursor(8,0);
lcd.print("Moist=");
lcd.setCursor(0,1);
lcd.print("Water Pump");
} void loop() {
float temperatureValue = analogRead(temperatureSensor) * 500.0 / 1023.0;
float moistureValue = analogRead(moistureSensor) * 100.0 / 539.0;
lcd.setCursor(2,0);
lcd.print(temperatureValue);
lcd.setCursor(10,0);
lcd.print(moistureValue);
lcd.setCursor(11,1);
if (temperatureValue > 35){
digitalWrite(waterPump, HIGH);
digitalWrite(redLed_Temperature, HIGH);
digitalWrite(greenLed_Temperature, LOW);
lcd.print("- ON ");
}
else if(temperatureValue < 30){
digitalWrite(waterPump, LOW);
digitalWrite(redLed_Temperature, LOW);
digitalWrite(greenLed_Temperature, HIGH);
lcd.print("- OFF");
}
if (moistureValue > 85){
noTone(buzzer);
digitalWrite(waterPump, LOW);
digitalWrite(redLed_Moisture, LOW);
digitalWrite(greenLed_Moisture, HIGH);
lcd.setCursor(11,1);
lcd.print("- OFF");
}
else if (moistureValue < 35){
tone(buzzer,1500);
digitalWrite(waterPump, HIGH);
digitalWrite(redLed_Moisture, HIGH);
digitalWrite(greenLed_Moisture, LOW);
lcd.setCursor(11,1);
lcd.print("- ON ");
}
else{
noTone(buzzer);
}
delay(1000);
}