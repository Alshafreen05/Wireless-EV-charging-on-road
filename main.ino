#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int voltagePin = A0;
int currentPin = A1;

float voltage;
float current;

void setup()
{

Serial.begin(9600);

lcd.init();
lcd.backlight();

lcd.setCursor(0,0);
lcd.print("EV Charger");
delay(2000);

Serial.println("AT");
delay(1000);

Serial.println("AT+CMGF=1");
delay(1000);

}

void sendSMS(String message)
{
Serial.println("AT+CMGF=1");
delay(1000);

Serial.println("AT+CMGS=\"8489123844\"");
delay(1000);

Serial.print(message);
delay(500);

Serial.write(26);
delay(5000);
}

void loop()
{

int voltageValue = analogRead(voltagePin);
voltage = voltageValue * (25.0 / 1023.0);

int currentValue = analogRead(currentPin);
float sensorVoltage = currentValue * (5.0 / 1023.0);
current = (sensorVoltage - 2.5) / 0.185;

if(current < 0) current = 0;

lcd.clear();

lcd.setCursor(0,0);
lcd.print("V:");
lcd.print(voltage);

lcd.setCursor(8,0);
lcd.print("I:");
lcd.print(current);

delay(2000);

/* VOLTAGE CONDITIONS */

if(voltage >=10 && voltage <=12)
{
lcd.setCursor(0,1);
lcd.print("Voltage Normal");

sendSMS("Car charging voltage normal");

delay(15000);
}

else if(voltage <=5)
{
lcd.setCursor(0,1);
lcd.print("Low Voltage");

sendSMS("Low voltage charging stopped");

delay(15000);
}

/* CURRENT CONDITIONS */

if(current < 0.15)
{
lcd.setCursor(0,1);
lcd.print("Low Current   ");
}

else if(current >=0.15 && current <=0.20)
{
lcd.setCursor(0,1);
lcd.print("Normal Current");
}

else if(current >0.20)
{
lcd.setCursor(0,1);
lcd.print("High Current  ");

sendSMS("Alert: Charging current HIGH");

delay(15000);
}

}
