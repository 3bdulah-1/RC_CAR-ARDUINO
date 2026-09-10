#include <Servo.h>
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;
int whiteRight = 6;
int whiteLeft = 7;
int redRight = 8;
int redLeft = 9;
Servo scannerServo;
int servoPin = 10;
int trigPin = 11;
int echoPin = 12;
int buzzer = 13;
int limitDistance = 20;
int turnTime = 500;
bool autoMode = false;
void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(whiteRight, OUTPUT);
  pinMode(whiteLeft, OUTPUT);
  pinMode(redRight, OUTPUT);
  pinMode(redLeft, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  scannerServo.attach(servoPin);
  scannerServo.write(90);
  stopCar();
  digitalWrite(whiteRight, LOW);
  digitalWrite(whiteLeft, LOW);
  digitalWrite(redRight, LOW);
  digitalWrite(redLeft, LOW);
  digitalWrite(buzzer, LOW);
}
void loop()
{
  if (Serial.available() > 0)
  {
    char command = Serial.read();   
    if (command == 'M')
    {
      autoMode = false;
      stopCar();
      digitalWrite(redRight, LOW);
      digitalWrite(redLeft, LOW);
    }
    else if (command == 'A')
    {
      autoMode = true;
    }
    else if (autoMode == false)
    {
      if (command == 'F')
      {
        forward();
        digitalWrite(redRight, LOW);
        digitalWrite(redLeft, LOW);
      }
      else if (command == 'B')
      {
        backward();
        digitalWrite(redRight, HIGH);
        digitalWrite(redLeft, HIGH);
      }
      else if (command == 'R')
      {
        right();
        digitalWrite(redRight, LOW);
        digitalWrite(redLeft, LOW);
      }
      else if (command == 'L')
      {
        left();
        digitalWrite(redRight, LOW);
        digitalWrite(redLeft, LOW);
      }
      else if (command == 'S')
      {
        stopCar();
        digitalWrite(redRight, LOW);
        digitalWrite(redLeft, LOW);
      }
      else if (command == 'W')
      {
        digitalWrite(whiteRight, HIGH);
        digitalWrite(whiteLeft, HIGH);
      }
      else if (command == 'w')
      {
        digitalWrite(whiteRight, LOW);
        digitalWrite(whiteLeft, LOW);
      }
      else if (command == 'P')
      {
        digitalWrite(buzzer, HIGH);
      }
      else if (command == 'p')
      {
        digitalWrite(buzzer, LOW);
      }
    }
  }
  if (autoMode == true)
  {
    autoDrive();
  }
}

void autoDrive()
{
  scannerServo.write(90);
  delay(100);
  int frontDistance = getDistance();
  if (frontDistance > limitDistance)
  {
    forward();
    digitalWrite(redRight, LOW);
    digitalWrite(redLeft, LOW);
    return;
  }
  stopCar();
  delay(300);
  scannerServo.write(170);
  delay(500);
  int rightDistance = getDistance();
  scannerServo.write(10);
  delay(500);
  int leftDistance = getDistance();
  scannerServo.write(90);
  delay(200);
  if (rightDistance > leftDistance)
  {
    right();
    delay(turnTime);
    stopCar();
    delay(200);
  }
  else
  {
    left();
    delay(turnTime);
    stopCar();
    delay(200);
  }
  forward();
  delay(100);
}
int getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0)
  {
    return 400;
  }
  int distance = duration * 0.034 / 2;
  return distance;
}
void forward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void backward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void left()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void stopCar()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}