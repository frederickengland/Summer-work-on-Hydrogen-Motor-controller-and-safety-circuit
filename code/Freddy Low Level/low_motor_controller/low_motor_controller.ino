// const int motor_left1 = 3;
// const int motor_left2 = 4;

// const int motor_right1 = 5;
// const int motor_right2 = 6;

// #define VRX_PIN A1
// #define VRY_PIN A0

// int throttle = 0;
// int steering = 0;


// int clamp_value(int value, int minimum, int maximum)
// {
//     return max(minimum, min(value, maximum));
// }


// void calculate_turning(int throttle,int steering,int &motor_left_pwr,int &motor_right_pwr)
// {
//     motor_left_pwr = throttle - steering;
//     motor_right_pwr = throttle + steering;

//     motor_left_pwr = clamp_value(motor_left_pwr, -100, 100);
//     motor_right_pwr = clamp_value(motor_right_pwr, -100, 100);
// }


// void set_motor(int pin1, int pin2, int speed)
// {
//     int pwm = map(abs(speed), 0, 100, 0, 255);

//     if (speed >= 0)
//     {
//         analogWrite(pin1, pwm);
//         analogWrite(pin2, 0);
//     }
//     else
//     {
//         analogWrite(pin1, 0);
//         analogWrite(pin2, pwm);
//     }
// }


// void setupp()
// {
//     Serial.begin(9600);

//     pinMode(motor_left1, OUTPUT);
//     pinMode(motor_left2, OUTPUT);

//     pinMode(motor_right1, OUTPUT);
//     pinMode(motor_right2, OUTPUT);
// }


// void loopp()
// {
//     int xValue = analogRead(VRX_PIN);
//     int yValue = analogRead(VRY_PIN);

//     steering = map(xValue, 0, 1023, -100, 100);
//     throttle = map(yValue, 0, 1023, -100, 100);

//     int left;
//     int right;

//     calculate_turning(throttle,steering,left,right);

//     Serial.print("Left Motor: ");
//     Serial.println(left);

//     Serial.print("Right Motor: ");
//     Serial.println(right);

//     set_motor(motor_left1, motor_left2, left);
//     set_motor(motor_right1, motor_right2, right);

//     delay(50);
// }