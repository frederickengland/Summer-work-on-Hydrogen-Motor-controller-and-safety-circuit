#include <Encoder.h>

const int encoderA = 2;
const int encoderB = 5;

const int motor_left1 = 3;
const int motor_left2 = 4; // change this back to the encoder motor

// Potentiometer
int potPin = A3;
int potVal = 0;

Encoder myEncoder(encoderA, encoderB);

unsigned long lastTime = 0;
float deltaTime = 0.0;

float integral = 0.0;
float derivative = 0.0;
float previousError = 0.0;

float pos = 0;
float setpoint = 0;
float output = 0;

float ticksPerDegree = 44.0 * 193.0 / 360.0 / 3.0;
float error = 0;

// PID gains
float Kp = 2.0;
float Ki = 0.0;
float Kd = 0.1;

int clamp_value(int value, int minimum, int maximum)
{
    return max(minimum, min(value, maximum));
}

void set_motor(int pin1, int pin2, int speed)
{
    int pwm = map(abs(speed), 0, 255, 0, 255);

    if (speed >= 0)
    {
        analogWrite(pin1, pwm);
        analogWrite(pin2, 0);
    }
    else
    {
        analogWrite(pin1, 0);
        analogWrite(pin2, pwm);
    }
}

void setup()
{
    pinMode(motor_left1, OUTPUT);
    pinMode(motor_left2, OUTPUT);

    Serial.begin(9600);

    lastTime = millis();

    Serial.println("PID Controller Ready");
}

void loop()
{
    unsigned long currentTime = millis();
    deltaTime = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;

    // Read current position
    pos = myEncoder.read() / ticksPerDegree;

    // Read potentiometer
    potVal = analogRead(potPin);

    // Convert to desired position
    setpoint = map(potVal, 0, 1023, 0, 180);

    // Calculate error
    error = setpoint - pos;

    // Integral term
    integral += error * deltaTime;

    // Derivative term
    derivative = (error - previousError) / deltaTime;
    previousError = error;

    // PID controller
    output = (Kp * error) + (Ki * integral) + (Kd * derivative);

    // Limit output
    output = constrain(output, -255, 255);

    // Drive motor
    set_motor(motor_left1, motor_left2, (int)output);

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