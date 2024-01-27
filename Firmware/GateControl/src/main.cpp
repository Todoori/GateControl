#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

#define PWM1 16
#define PWM2 17
#define LED1 25
#define LED2 21
#define BTN 20
#define BTN1 6
#define BTN2 7
#define BTN3 8


float RShunt = 0.01 ; //10mR
float shuntvoltage_mV = 0;
float busvoltage = 0;
float current_mA = 0;
int speed = 100; //PWM Value out of 250


void setup(void) 
{
  analogWriteFreq(2000); //2khz

  Serial.begin(115200);
  Serial.println("Hello!");
  
  // Initialize the INA219.
  Serial.println("initialising INA219...");
  Wire1.setSDA(18);
  Wire1.setSCL(19);
  if (! ina219.begin(&Wire1)) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }

  // Initialize Pin Modes  
  Serial.println("initialising Pin Modes...");
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BTN, INPUT);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  Serial.println("Setup finished");
}

void measureShunt()
{
  shuntvoltage_mV = ina219.getShuntVoltage_mV();
  if (shuntvoltage_mV < 0)
    shuntvoltage_mV = 0;
  busvoltage = ina219.getBusVoltage_V();
  current_mA = shuntvoltage_mV/RShunt;
  
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage_mV, 3); Serial.println(" mV");
  Serial.print("Current:       "); Serial.print(current_mA, 3); Serial.println(" mA");
  Serial.println("");
}

void Motorcontrol(int mode)
{

  if (mode == 0) //off (stdby)
  { 
    digitalWrite(PWM2, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(PWM1, LOW);
    digitalWrite(LED1, LOW);
    delay(500);
  }
    if (mode == 1) //Forward
  { 
    //break
    analogWrite(PWM1, 255);
    analogWrite(PWM2, 255);
    delay(200);
    analogWrite(PWM2, 0);
    digitalWrite(LED2, LOW);
    analogWrite(PWM1, speed);
    digitalWrite(LED1, HIGH);
    delay(500);
  }
    if (mode == 2) //Reveerse
  { 
    //break
    analogWrite(PWM1, 255);
    analogWrite(PWM2, 255);
    delay(200);
    analogWrite(PWM1, 0);
    digitalWrite(LED1, LOW);
    analogWrite(PWM2, speed);
    digitalWrite(LED2, HIGH);
    delay(500);
  }
    if (mode == 3) //Break
    {
    analogWrite(PWM1, 255);
    digitalWrite(LED1, HIGH);
    analogWrite(PWM2, 255);
    digitalWrite(LED2, HIGH);
    delay(500);
    }
}



void loop(void) 
{

  measureShunt();

  //Button readings
  if (!digitalRead(BTN))
  {
    Motorcontrol(0);
      if (!digitalRead(BTN1) && speed <235)
      {
        speed = speed + 20;
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(20);
      }
      if (!digitalRead(BTN2) && speed >20)
      {
        speed = speed -20;
        Serial.print("Speed: ");
        Serial.println(speed);
        delay(20);
      }
  }
  if (!digitalRead(BTN1))
  {
    Motorcontrol(1);
  }
    if (!digitalRead(BTN2))
  {
    Motorcontrol(2);
  }
    if (!digitalRead(BTN3))
  {
    Motorcontrol(3);
  }


  delay(100);
}





