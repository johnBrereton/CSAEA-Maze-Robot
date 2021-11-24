#include <Servo.h>

const int m1a = 5;
const int m1b = 6;

const int m2a = 10;
const int m2b = 9;

const int turnTime = 2000; // Time in ms required for robot to turn 90 degrees

const int redLED = 11;
const int leftLED = 7;
const int rightLED = 8;

Servo servo;
int servoPosition = 0;

const int trig = 4;
const int echo = 3;

float leftDistance;
float frontDistance;
float rightDistance;

void setup() {
    Serial.begin(9600);

    pinSetup();
}

void loop() {
    getDistances();
        
    driveUpdate();
}

void pinSetup() {
    // Set motor controller pin modes
    pinMode(m1a, OUTPUT);
    pinMode(m1b, OUTPUT);
    pinMode(m2a, OUTPUT);
    pinMode(m2b, OUTPUT);

    // Set servo pin to 11
    servo.attach(11);

    // Set ultrasonic sensor pin modes
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

void getDistances() {
    // Rotate servo to left position and record distance
    servo.write(10);
    delay(1000);
    leftDistance = distance();

    // Rotate servo to center position and record distance
    servo.write(90);
    delay(1000);
    frontDistance = distance();

    // Rotate servo to right position and record distance
    servo.write(170);
    delay(1000);
    rightDistance = distance();

    // Return servo to center position
    servo.write(90);
    delay(1000);
}

void driveUpdate() {
    // If the front and left sides are blocked turn right
    if(rightDistance > 8 && leftDistance <= 8 && frontDistance <= 8){
        turnRight();
    }

    // If the right and front sides are blocked turn left
    else if (leftDistance > 8 && rightDistance <= 8 && frontDistance <= 8){
        turnLeft();
    }

    // If there is nothing in front and left and right are blocked proceed forward
    else if (frontDistance > 8){
        forward();
    }

    // If all sides are blocked flash red LED
    else if (frontDistance <= 8){
        
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

    calculatedDistance = echoTime/148.0;
    
    return calculatedDistance;
}

// Move robot forward indefinetly
void forward() {
    while(distance() > 8) {
        digitalWrite(m1a, HIGH);
        digitalWrite(m1b, LOW);
        digitalWrite(m2a, HIGH);
        digitalWrite(m2b, LOW);
    }
    digitalWrite(m1a, LOW);
    digitalWrite(m2a, LOW);
}

// Turn robot left 90 degrees
void turnLeft() {
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);

    blink(leftLED, turnTime, 4);

    digitalWrite(m1a, LOW);
}

// Turn robot right 90 degrees
void turnRight() {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);

    blink(rightLED, turnTime, 4);

    digitalWrite(m2a, LOW);
}

// Stop robot movement and flash red LED
void stop() {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);

    blink(redLED, 10000, 10);
}

// Flash specified led 4 times over set period of time
void blink(int led, int totalTime, int pulses) {
    for (int i = 0; i <= 3; i++) {
        digitalWrite(led, HIGH);
        
        delay(totalTime/(pulses*2));
        
        digitalWrite(led, LOW);
        
        delay(totalTime/(pulses*2));
    }
}
