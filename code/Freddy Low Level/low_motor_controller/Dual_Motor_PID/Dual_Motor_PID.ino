#include <Encoder.h>

const int encoderA = 2;
const int encoderB = 5;
const int encoderC = 6;
const int encoderD = 8;

const int motor_left1 = 3;
const int motor_left2 = 4;
const int motor_right1 = 7;
const int motor_right2 = 9;

// Potentiometer
int potPin = A3;
int potVal = 0;

Encoder myEncoderleft(encoderA, encoderB);
Encoder myEncoderright(encoderC, encoderD);

unsigned long lastTime = 0;
float deltaTime = 0.0;

// Left PID
float left_integral = 0.0;
float left_derivative = 0.0;
float left_previousError = 0.0;
float left_pos = 0;
float left_setpoint = 0;
float left_output = 0;
float left_error = 0;

// Right PID
float right_integral = 0.0;
float right_derivative = 0.0;
float right_previousError = 0.0;
float right_pos = 0;
float right_setpoint = 0;
float right_output = 0;
float right_error = 0;

// Universal
float ticksPerDegree = 44.0 * 193.0 / 360.0 / 3.0;

// PID gains
float Kp = 2.0;
float Ki = 0.0;
float Kd = 0.1;

void set_motor(int pin1, int pin2, int speed)
{
    int pwm = constrain(abs(speed), 0, 255);

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
    pinMode(motor_right1, OUTPUT);
    pinMode(motor_right2, OUTPUT);

    pinMode(potPin, INPUT);

    Serial.begin(9600);

    lastTime = millis();

    Serial.println("DUAL PID Controller Ready");
}

void loop()
{
    unsigned long currentTime = millis();
    deltaTime = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;

    // Read current positions
    left_pos = myEncoderleft.read() / ticksPerDegree;
    right_pos = myEncoderright.read() / ticksPerDegree;

    // Read potentiometer
    potVal = analogRead(potPin);

    // Convert to desired position
    left_setpoint = map(potVal, 0, 1023, 0, 180);
    right_setpoint = left_setpoint;

    // LEFT PID
    left_error = left_setpoint - left_pos;

    left_integral += left_error * deltaTime;

    left_derivative = (left_error - left_previousError) / deltaTime;
    left_previousError = left_error;

    left_output = (Kp * left_error) + (Ki * left_integral) + (Kd * left_derivative);

    left_output = constrain(left_output, -255, 255);

    // RIGHT PID
    right_error = right_setpoint - right_pos;

    right_integral += right_error * deltaTime;

    right_derivative = (right_error - right_previousError) / deltaTime;
    right_previousError = right_error;

    right_output = (Kp * right_error) + (Ki * right_integral) + (Kd * right_derivative);

    right_output = constrain(right_output, -255, 255);

    // Drive motors
    set_motor(motor_left1, motor_left2, (int)left_output);
    set_motor(motor_right1, motor_right2, (int)right_output);

    Serial.print("Setpoint: ");
    Serial.print(left_setpoint);

    Serial.print(", Left Position: ");
    Serial.print(left_pos);

    Serial.print(", Right Position: ");
    Serial.print(right_pos);

    Serial.print(", Left Error: ");
    Serial.print(left_error);

    Serial.print(", Right Error: ");
    Serial.print(right_error);

    Serial.print(", Left OutputPower: ");
    Serial.print(left_output);

    Serial.print(", Right OutputPower: ");
    Serial.println(right_output);

    delay(100);
}