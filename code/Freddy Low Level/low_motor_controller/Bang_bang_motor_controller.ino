#include <Encoder.h>

int encoderA = 3;
int encoderB = 2;

int motorA = 6;
int motorB = 5;
int motorE = 11;

Encoder myEncoder(encoderA, encoderB);

float reference = 1000;
float measure = 0;
float error = 0;

void fast()
{
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, LOW);
    analogWrite(motorE, 255);
}

void slow()
{
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, LOW);
    analogWrite(motorE, 55);
}

void medium()
{
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, LOW);
    analogWrite(motorE, 125);
}

void setup()
{
    pinMode(motorA, OUTPUT);
    pinMode(motorB, OUTPUT);
    pinMode(motorE, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    measure = myEncoder.read();

    error = reference - measure;

    if (error == 0)
    {
        medium();
    }

    if (error > 0)
    {
        fast();
    }

    if (error < 0)
    {
        slow();
    }

    Serial.print("Position: ");
    Serial.println(measure);
}