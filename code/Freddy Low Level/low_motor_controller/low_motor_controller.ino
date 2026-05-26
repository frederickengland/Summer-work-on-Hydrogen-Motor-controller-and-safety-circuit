const int pedal = 1;
const int steering_wheel = 2;

const int motor_left = 3;
const int motor_right = 4;

int throttle = 0;
int steering = 0;


int clamp_value(int value, int minimum, int maximum)
{
    return max(minimum, min(value, maximum));
}


void calculate_turning(int throttle, int steering,int &motor_left_pwr,int &motor_right_pwr)
{
    motor_left_pwr = throttle - steering;
    motor_right_pwr = throttle + steering;

    motor_left_pwr = clamp_value(motor_left_pwr, -100, 100);
    motor_right_pwr = clamp_value(motor_right_pwr, -100, 100);
}


void setup()
{
    Serial.begin(9600);

    pinMode(motor_left, OUTPUT);
    pinMode(motor_right, OUTPUT);
}


void loop()
{
    if (steering > 540 || steering < -540)
    {
        Serial.println("Steering value not valid");
    }
    else
    {
        float steering_scaled = steering / 5.4;

        int left;
        int right;

        calculate_turning(throttle,steering_scaled,left,right);

        Serial.print("Left Motor: ");
        Serial.println(left);

        Serial.print("Right Motor: ");
        Serial.println(right);

        // Convert -100 to 100 into PWM range
        int left_pwm = map(left, -100, 100, 0, 255);
        int right_pwm = map(right, -100, 100, 0, 255);

        analogWrite(motor_left, left_pwm);
        analogWrite(motor_right, right_pwm);
    }
}