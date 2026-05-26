const int motor_left = 1;
const int motor_right = 2;

bool overheating = false;
bool overcurrent = false;
bool sensor_fault = false;

void power_on(int motor_left, int motor_right)
{
int throttle = 100;
int pwm = throttle * 2.55;
    analogWrite(motor_left, pwm);
    analogWrite(motor_right, pwm);
}


void power_off(int motor_left, int motor_right)
{
int throttle = 0;
int pwm = throttle * 2.55;
    analogWrite(motor_left, pwm);
    analogWrite(motor_right, pwm);
}


bool dangerous_situation()
{
    if (overcurrent)
    {
        return true;
    }

    if (overheating)
    {
        return true;
    }

    if (sensor_fault)
    {
        return true;
    }

    return false;
}


void setup()
{
    Serial.begin(9600);

    pinMode(motor_left, OUTPUT);
    pinMode(motor_right, OUTPUT);
}


void loop()
{
    if (dangerous_situation())
    {
        power_off(motor_left, motor_right);

        Serial.println("Power off. Fault detected.");
    }
    else
    {
        power_on(motor_left, motor_right);

        Serial.println("System safe. Continuing driving.");
    }
}