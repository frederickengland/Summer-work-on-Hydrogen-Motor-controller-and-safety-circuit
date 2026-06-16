#include <Encoder.h>

int encoderA = 3;
int encoderB = 2;

Encoder myEncoder(encoderA, encoderB);

// Motor pins
int leftMotorPWM = 6;
int rightMotorPWM = 11;

// Control variables
float desiredSpeed = 100;
float measuredSpeed = 0;
float error = 0;

// Driver input
int steering = 0;

// Controller output
int throttleCommand = 0;

// Encoder tracking
long previousTicks = 0;

void setup()
{
    pinMode(leftMotorPWM, OUTPUT);
    pinMode(rightMotorPWM, OUTPUT);

    Serial.begin(9600);

    Serial.println("Bang-Bang Speed Controller");
}

void loop()
{
    // Measure wheel speed
    long currentTicks = myEncoder.read();

    measuredSpeed = currentTicks - previousTicks;

    previousTicks = currentTicks;

    // Calculate speed error
    error = desiredSpeed - measuredSpeed;

    // Bang-Bang Controller
    if (abs(error) < 5)
    {
        throttleCommand = 0;
    }
    else if (error > 0)
    {
        throttleCommand = 100;
    }
    else
    {
        throttleCommand = -100;
    }

    // example steering input for testing / debugging
    steering = 20;

    // Steering vectorisation
    int leftMotorPower = throttleCommand - steering;
    int rightMotorPower = throttleCommand + steering;

    // Clamp motor outputs
    leftMotorPower = constrain(leftMotorPower, -100, 100);
    rightMotorPower = constrain(rightMotorPower, -100, 100);

    // Convert to PWM
    int leftPWM = map(leftMotorPower, -100, 100, 0, 255);
    int rightPWM = map(rightMotorPower, -100, 100, 0, 255);

    analogWrite(leftMotorPWM, leftPWM);
    analogWrite(rightMotorPWM, rightPWM);

    // Debug output
    Serial.print("Desired Speed: ");
    Serial.print(desiredSpeed);

    Serial.print(", Measured Speed: ");
    Serial.print(measuredSpeed);

    Serial.print(", Error: ");
    Serial.print(error);

    Serial.print(", Throttle: ");
    Serial.print(throttleCommand);

    Serial.print(", Left Motor: ");
    Serial.print(leftMotorPower);

    Serial.print(", Right Motor: ");
    Serial.println(rightMotorPower);

    delay(100);
}