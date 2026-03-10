#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// RFID Pins
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Servo
Servo myServo;

// LCD (I2C address usually 0x27)
LiquidCrystal_I2C lcd(0x27,16,2);

// Ultrasonic Sensor
#define trigPin 6
#define echoPin 7

// LEDs and Buzzer
#define greenLED 3
#define redLED 4
#define buzzer 5

long duration;
int distance;

// Replace with your RFID card UID
byte authorizedUID[4] = {0xA3,0x12,0xBC,0x44};

void setup()
{

Serial.begin(9600);

SPI.begin();
mfrc522.PCD_Init();

myServo.attach(8);

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

pinMode(greenLED, OUTPUT);
pinMode(redLED, OUTPUT);
pinMode(buzzer, OUTPUT);

lcd.init();
lcd.backlight();

lcd.setCursor(0,0);
lcd.print("SMART DOOR LOCK");
delay(2000);
lcd.clear();

myServo.write(0); // Door locked
}

void loop()
{

// Measure distance

digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance = duration * 0.034 / 2;

// If person detected within 1 meter

if(distance < 100)
{

lcd.setCursor(0,0);
lcd.print("Verify Your ID ");

if ( ! mfrc522.PICC_IsNewCardPresent())
return;

if ( ! mfrc522.PICC_ReadCardSerial())
return;

if(checkCard())
{
accessGranted();
}
else
{
accessDenied();
}

mfrc522.PICC_HaltA();

}

else
{
lcd.setCursor(0,0);
lcd.print("No Person Near ");
digitalWrite(greenLED, LOW);
digitalWrite(redLED, LOW);
}

}

// Function to check RFID UID

boolean checkCard()
{

for(byte i=0;i<4;i++)
{
if(mfrc522.uid.uidByte[i] != authorizedUID[i])
return false;
}

return true;

}

// Access Granted

void accessGranted()
{

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Access Granted");

digitalWrite(greenLED, HIGH);

tone(buzzer,1000);
delay(500);
noTone(buzzer);

myServo.write(90);   // Open door
delay(5000);

myServo.write(0);    // Close door

digitalWrite(greenLED, LOW);

lcd.clear();

}

// Access Denied

void accessDenied()
{

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Access Denied");

for(int i=0;i<3;i++)
{
digitalWrite(redLED,HIGH);
tone(buzzer,500);
delay(300);

digitalWrite(redLED,LOW);
noTone(buzzer);
delay(300);
}

lcd.clear();

}