#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int red_led = 13;
const int green_led = 12;
const int blue_led = 11;
const int led_button = 10;

int ledState = 0;

float baselineTemp = 30.0;
const int temperature_sensor = A1;
const int nmosGatePin = 3;
int lcd_button = 4;
int motor = 3;
const int sensorPin = A0;

int sensorValue = 0;

void setup()
{
  pinMode(temperature_sensor, INPUT);
  Serial.begin(9600);
  pinMode(nmosGatePin, OUTPUT);
  
  pinMode(led_button, INPUT_PULLUP);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
  
  pinMode(lcd_button, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
}

void loop()
{
  int buttonState = digitalRead(led_button);
  
  if (buttonState == LOW && ledState < 4) {
  	ledState++;
    
    digitalWrite(red_led, LOW);
   	digitalWrite(green_led, LOW);
   	digitalWrite(blue_led, LOW);
    
    switch (ledState) {
    	case 1:
       		digitalWrite(red_led, HIGH);
       		break;
     	case 2:
       		digitalWrite(green_led, HIGH);
       		break;
     	case 3:
       		digitalWrite(blue_led, HIGH);
       		break;
     	case 4:
       		ledState = 0;
       		break;
    }
    delay(500);
  }
  
  float celsius = map(((analogRead(temperature_sensor) - 20) * 3.04), 0, 1023, -40, 125);
  
  if (isnan(celsius)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.println("°C");
  
  if (celsius >= baselineTemp) {
  	digitalWrite(nmosGatePin, HIGH);
  } else {
    digitalWrite(nmosGatePin, LOW);
  }
  
  sensorValue = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue); 
  delay(1000);
}