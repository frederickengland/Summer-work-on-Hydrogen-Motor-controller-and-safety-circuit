throttle = 0
steering = 0

def clamp(value, minimum, maximum):
    return max(minimum, min(value, maximum))


def calculate_turning(throttle, steering):

    motor_left = throttle - steering
    motor_right = throttle + steering

    # Keep motor values within valid range
    motor_left = clamp(motor_left, -100, 100)
    motor_right = clamp(motor_right, -100, 100)

    return motor_left, motor_right


print("What is the throttle on?")
throttle = int(input())

print("What is the steering?")
steering = int(input())


if steering > 540 or steering < -540:
    print("Steering value not valid")

else:
    # Convert steering wheel range into motor steering range
    steering_scaled = steering / 5.4

    left, right = calculate_turning(throttle, steering_scaled)

    print("Left Motor:", left)
    print("Right Motor:", right)