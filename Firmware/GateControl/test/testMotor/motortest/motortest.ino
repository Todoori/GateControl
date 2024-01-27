
#define PWM1 16
#define PWM2 17
#define LED1 25
#define LED2 21
#define BTN 20

int mode = 0; //0 = off, 1 =PWM1, 2 = PWM3

void setup() {

  analogWriteFreq(2000); //2khz

  Serial.begin(115200);
  Serial.println("initialising Pin Modes...");
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BTN, INPUT);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

}

void Motorcontrol()
{
  if (mode == 0)
  { 
    digitalWrite(PWM2, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(PWM1, LOW);
    digitalWrite(LED1, LOW);
    delay(500);
  }
    if (mode == 1)
  { 
    analogWrite(PWM2, 0);
    digitalWrite(LED2, LOW);
    delay(500);
    analogWrite(PWM1, 5);
    digitalWrite(LED1, HIGH);
    delay(500);
  }
    if (mode == 2)
  { 
    analogWrite(PWM1, 0);
    digitalWrite(LED1, LOW);
    delay(500);
    analogWrite(PWM2, 20);
    digitalWrite(LED2, HIGH);
    delay(500);
  }
}

void Buttonpressed()
{
  mode ++;
  if (mode == 3)
  {
    mode = 0;
  }
  Serial.print("Mode: ");
  Serial.println(mode);
}

void loop() {
  // put your main code here, to run repeatedly:
if (!digitalRead(BTN))
{
  Buttonpressed();
  Motorcontrol();
}
delay(10);
}
