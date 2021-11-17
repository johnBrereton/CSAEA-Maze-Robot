#include <Servo.h>

const int m1a = 5;
const int m1b = 6;

const int m2a = 10;
const int m2b = 9;

const int servo = 11;
int servoPosition = 0;

const int trig = 4;
const int echo = 3;

float distance = 0;

void setup() {
    serial.begin(9600);

    pinSetup();

    Servo Servo;
    Servo.attach(servo);
}

void loop() {
    getDistances();
}

void pinSetup() {
    pinMode(m1a, OUTPUT);
    pinMode(m1b, OUTPUT);
    pinMode(m2a, OUTPUT);
    pinMode(m2b, OUTPUT);

    pinMode(servo, OUTPUT);

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

void servoUpdate() {
    servo.write(servoPosition);
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

void reverse() {

}

void telemetry() {

}