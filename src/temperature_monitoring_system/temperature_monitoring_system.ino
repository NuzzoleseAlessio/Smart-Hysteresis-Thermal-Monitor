#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

const int sensorPin = A0;
const int ledPin = 13;
const int buzzerPin = 8; 

// Hysteresis parameters
const float activation = 30.0; 
const float deactivation = 28.0; 

// State variable
bool alarmOn = false;

void setup() {
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT); 
  
  lcd.print("Thermometer");
  delay(1500);
  lcd.clear();
}

void loop() {
  // Reading and conversion
  int firstReading = analogRead(sensorPin);
  float voltage = firstReading * (5.0 / 1024.0);
  float temperatureC = (voltage - 0.5) * 100;

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print(" C  "); 

  // --- HYSTERESIS LOGIC ---
  if (temperatureC >= activation) {
    alarmOn = true;  // Turn alarm on
  } else if (temperatureC <= deactivation) {
    alarmOn = false; // Turn alarm off
  }
  // If the temperature is between 28 and 30 degrees, the alarm will not be deactivated

  // --- ACTIVATION ---
  lcd.setCursor(0, 1);
  if (alarmOn == true) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 100); 
    lcd.print("ALARM ON! ");
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);     
    lcd.print("State: OK       ");
  }

  delay(500); 
}