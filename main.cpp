#include <Servo.h>

bool enabled = false;

const int m1a = 5;
const int m1b = 6;

const int m2a = 10;
const int m2b = 9;

const int turnTime = 2000; // Time in ms required for robot to turn 90 degrees

const int ledR = 11;
const int ledG = 12;
const int ledB = 13;

const int leftLED = 7;
const int rightLED = 8;

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
    if (enabled && digitalRead(2) == HIGH) {
        enabled = false;
        stop();
    }
    else if (!enabled && digitalRead(2) == HIGH) {
        enabled = true;
    }

    if (enabled) {
        getDistances();
        
        driveUpdate();
    }
    
    telemetry();
}

void pinSetup() {
    // Set motor controller pin modes
    pinMode(m1a, OUTPUT);
    pinMode(m1b, OUTPUT);
    pinMode(m2a, OUTPUT);
    pinMode(m2b, OUTPUT);

    // Set servo pin mode and created servo instance with servo library
    pinMode(servo, OUTPUT);
    Servo servo;
    servo.attach(11);

    // Set ultrasonic sensor pin modes
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

void getDistances() {
    // Rotate servo to left position and record distance
    servo.write(20);
    leftDistance = distance();

    // Rotate servo to center position and record distance
    servo.write(70);
    frontDistance = distance();

    // Rotate servo to right position and record distance
    servo.write(160);
    rightDistance = distance();

    // Return servo to center position
    servo.write(70);
}

void driveUpdate() {
    // If the front and left sides are blocked turn right
    if(right_dis > 8 && left_dis <= 8 && front_dis <= 8){
        turnRight();
    }

    // If the right and front sides are blocked turn left
    else if (left_dis > 8 && right_dis <= 8 && front_dis <= 8){
        turnLeft();
    }

    // If there is nothing in front and left and right are blocked proceed forward
    else if (front_dis > 8){
        forward();
    }

    // If all sides are blocked flash red LED
    else if (front_dis <= 8){
        
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

void forward() {
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
}

// Turn the robot left 90 degrees
void turnLeft() {
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);

    blink(leftLED, turnTime);

    digitalWrite(m1a, LOW);
}

// Turn robot right 90 degrees
void turnRight() {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);

    blink(rightLED, turnTime);

    digitalWrite(m2a, LOW);
}

// Stop robot movement and flash red LED
void stop() {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);

    blink(ledR, int 10000);
}

void blink(int led, int totalTime) {
    for (int i = 0; i <= 3; i++) {
        digitalWrite(led, HIGH);
        
        delay(totalTime/8);
        
        digitalWrite(led, LOW);
        
        delay(totalTime/8);
    }
}

void telemetry() {
    Serial.print("=======================");

    // Display robot status
    if (enabled) {
        Serial.print("Robot is enabled");
    }
    else {
        Serial.print("Robot is disabled");
    }
}