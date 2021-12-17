#include <Servo.h>

//Variables
const int motor1a = 10;
const int motor1b = 9;

const int motor2a = 6;
const int motor2b = 5;

const int turnTime = 650;

Servo servo;
int servoPosition = 0;

const int trig = 4;
const int echo = 3;

float leftDistance = 0.0;
float frontDistance;
float rightDistance;

void setup() {
  Serial.begin(9600);
  
  pinSetup();
}

void loop() {
  getForwardDistance();
  forward();

  if (frontDistance < 5) {
    stopMotors();
    scan();
    
    // If the front and left sides are blocked turn right
    if (leftDistance > 10) turnRight();
    else if (rightDistance > 10) turnLeft();
    //else backUpAndScan();
  }
}

// *** F U N C T I O N S ***

void scan() {
  // Rotate servo to left position and record distance
  servo.write(10);
  delay(500);
  leftDistance = distance();
  Serial.println(leftDistance);

  // Rotate servo to right position and record distance
  servo.write(170);
  delay(500);
  rightDistance = distance();
  Serial.println(rightDistance);
}

void getForwardDistance() {
  servo.write(90);
  delay(500);
  frontDistance = distance();
  Serial.println(frontDistance);
}

void backUpAndScan() {
  servo.write(10);
  delay(500);
  leftDistance = distance();
  while(leftDistance < 10)
 { 
  backwards();
 }
  
}

float distance() {
  float echoTime; // Stores the echo time of a ping
  float calculatedDistance; // Stores the distance calculated from the echo time

  // Send 10ms ultrasonic pulse
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  echoTime = pulseIn(echo, HIGH);

  calculatedDistance = echoTime / 148.0;

  return calculatedDistance;
}

void forward() {
  digitalWrite(motor1a, HIGH);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, HIGH);
  digitalWrite(motor2b, LOW);
}

void backwards() {
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, HIGH);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, HIGH);
}

// Turn robot left 90 degrees
void turnLeft() {
  digitalWrite(motor1a, HIGH);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, LOW);

  delay(turnTime);

  digitalWrite(motor1a, LOW);
}

// Turn robot right 90 degrees
void turnRight() {
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, HIGH);
  digitalWrite(motor2b, LOW);

  delay(turnTime);

  digitalWrite(motor2a, LOW);
}

// Stop robot movement
void stopMotors() {
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, LOW);
}

//PinSetup
void pinSetup() {
  // Set motor controller pin modes
  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);

  // Set servo pin to 11
  servo.attach(11);

  // Set ultrasonic sensor pin modes
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}
