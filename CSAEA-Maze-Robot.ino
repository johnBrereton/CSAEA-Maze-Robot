#include <Servo.h>

//Variables
const int motor1a = 10;
const int motor1b = 9;

const int motor2a = 6;
const int motor2b = 5;

const int turnTime = 625;

Servo servo;
int servoPosition = 0;

const int trig = 4;
const int echo = 3;

float leftDistance;
float frontDistance;
float rightDistance;

//Setup
void setup() {
  Serial.begin(9600);
  
  pinSetup();
}

//Loop
void loop() {
  getForwardDistance();
  driveUpdate();
}

void getForwardDistance() {
  frontDistance = distance();
  Serial.println(frontDistance);
}

void straightWall(){
  servo.write(90);
  frontDistance = distance();
}

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

  // Return servo to center position
  servo.write(90);
  delay(750);

}

void driveUpdate() {
  if (frontDistance > 5) {
    forward();
  }

  else {
    stopMotors();
    scan();
    
    // If the front and left sides are blocked turn right
    if (rightDistance > 10) {
      turnLeft();
    }

    // If the right and front sides are blocked turn left
    else if (leftDistance > 10) {
      turnRight();
    }
  
    else {
      backUpAndScan();
    }
  }
  
}

void backUpAndScan() {
  
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



// Move robot forward
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
