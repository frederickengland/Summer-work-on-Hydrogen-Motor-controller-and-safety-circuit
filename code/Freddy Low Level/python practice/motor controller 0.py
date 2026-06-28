throttle = 100   # forward power
steering = 0     # -50 = left, +50 = right

def calculate_turning(throttle, steering):

    motor_left = throttle - steering
    motor_right = throttle + steering

    return motor_left, motor_right


left, right = calculate_turning(throttle, steering)

print("Left Motor:", left)
print("Right Motor:", right)

# next step ensuring calculation is within 100