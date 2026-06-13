#include <Encoder.h>

int encoderA = 3;
int encoderB = 2;

int motorA = 6;
int motorB = 5;
int motorE = 11;

Encoder myEncoder(encoderA, encoderB);

float pos = 0;
float setpoint = 0;

float output = 0;

float ticksPerDegree = 44.0 * 193.0 / 360.0 / 3.0;
float error = 0;
int current_power = 0;
int power = current_power;
// a function that checks if the number has spiked up randomly checks if number has risen and if so does it remain for more than one instance.


void forward()
{
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, LOW);
    analogWrite(motorE, 255);
}

void reverse()
{
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, HIGH);
    analogWrite(motorE, 255);
}

void stopMotor()
{
    analogWrite(motorE, 0);
}

void setup()
{
    pinMode(motorA, OUTPUT);
    pinMode(motorB, OUTPUT);
    pinMode(motorE, OUTPUT);

    Serial.begin(9600);

    Serial.println("Enter a target angle in degrees:");
}

void loop()
{
    // Convert encoder ticks to degrees
    pos = myEncoder.read() / ticksPerDegree;

    // Read desired position from serial monitor
    if (Serial.available() > 0)
    {
        setpoint = Serial.parseFloat();

        Serial.print("New Setpoint: ");
        Serial.println(setpoint);
    }

    // Calculate control error
    error = setpoint - pos;

    // Bang-Bang Controller
    if (abs(error) < 2.0)
    {
        stopMotor();
        output = 0;
    }
    else if (error > 0)
    {
        forward();
        output = 255;
    }
    else
    {
        reverse();
        output = -255;
    }

    // Run controller at 10 Hz
    delay(100);

    // Debug information
    Serial.print("Setpoint: ");
    Serial.print(setpoint);

    Serial.print(", Position: ");
    Serial.print(pos);

    Serial.print(", Error: ");
    Serial.print(error);

    Serial.print(", OutputPower: ");
    Serial.print(output);

    Serial.println();
}