#include <Servo.h>

const int m1a = 5;
const int m1b = 6;

const int m2a = 10;
const int m2b = 9;

int servoPosition = 0;

const int trig = 4;
const int echo = 3;

float leftDistance;
float frontDistance;
float rightDistance;

void setup() {
    serial.begin(9600);

    pinSetup();

    Servo servo;
    servo.attach(11);

}

void loop() {
    getDistances();

    if (right_dis <= 6&& left_dis <= 6&& front_dis>5){
        forward();
    }
    else if(right_dis > 6&&left_dis <= 6&& front_dis<=5){
        turnRight();
    }
    else if (left_dis >6&&right_dis <= 6&& front_dis<=5){
        turnLeft();
    }
    else if (left_dis <=6&&right_dis <= 6&& front_dis <=6){
        reverse();
    }
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