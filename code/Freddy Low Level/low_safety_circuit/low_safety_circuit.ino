const int motor_left1 = 3;
const int motor_left2 = 4;

const int motor_right1 = 5;
const int motor_right2 = 6;

const int MAX_SAFE_VOLTAGE = 100;

int voltage = 0;

void power_on()
{
    analogWrite(motor_left1, 255);
    analogWrite(motor_left2, 0);

    analogWrite(motor_right1, 0);
    analogWrite(motor_right2, 255);
}

void power_off()
{
    analogWrite(motor_left1, 0);
    analogWrite(motor_left2, 0);

    analogWrite(motor_right1, 0);
    analogWrite(motor_right2, 0);
}

bool dangerous_situation()
{
    return voltage > MAX_SAFE_VOLTAGE;
}

void setup()
{
    Serial.begin(9600);

    pinMode(motor_left1, OUTPUT);
    pinMode(motor_left2, OUTPUT);

    pinMode(motor_right1, OUTPUT);
    pinMode(motor_right2, OUTPUT);

    randomSeed(analogRead(A0));
}

void loop()
{
    int spike = random(0, 20);

    voltage += spike;

    Serial.print("Voltage: ");
    Serial.println(voltage);

    if (dangerous_situation())
    {
        power_off();

        Serial.println("Power off. Overvoltage fault detected.");

        while (true)
        {
            // Stay shut down
        }
    }
    else
    {
        power_on();

        Serial.println("System safe.");
    }

    delay(500);
}