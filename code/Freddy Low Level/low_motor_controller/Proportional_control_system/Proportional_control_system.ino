#include <Encoder.h>

int encoderA = 3;
int encoderB = 2;

int motorA = 6;
int motorB = 5;
int motorE = 11;

// Potentiometer
int potPin = A3;
int potVal = 0;

Encoder myEncoder(encoderA, encoderB);

float pos = 0;
float setpoint = 0;
float output = 0;

float ticksPerDegree = 44.0 * 193.0 / 360.0 / 3.0;
float error = 0;

// Proportional gain
float Kp = 2.0;

void forward(int pwm)
{
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, LOW);
    analogWrite(motorE, pwm);
}

void reverse(int pwm)
{
    digitalWrite(motorA, LOW);
    digitalWrite(motorB, HIGH);
    analogWrite(motorE, pwm);
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

    Serial.println("Proportional Controller Ready");
}

void loop()
{
    // Read current position
    pos = myEncoder.read() / ticksPerDegree;

    // Read potentiometer
    potVal = analogRead(potPin);

    // Convert to desired position
    setpoint = map(potVal, 0, 1023, 0, 180);

    // Calculate error
    error = setpoint - pos;

    // Proportional controller
    output = Kp * error;

    // Limit output to PWM range
    output = constrain(output, -255, 255);

    if (abs(error) < 2)
    {
        stopMotor();
    }
    else if (output > 0)
    {
        forward((int)output);
    }
    else
    {
        reverse((int)abs(output));
    }

    Serial.print("Setpoint: ");
    Serial.print(setpoint);

    Serial.print(", Position: ");
    Serial.print(pos);

    Serial.print(", Error: ");
    Serial.print(error);

    Serial.print(", OutputPower: ");
    Serial.println(output);

    delay(100);
}