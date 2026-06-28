throttle = 0
steering = 0

reference = 0                     # What speed I want to go
measured = 0                      # Current speed I'm going
error = 0                         # Difference between reference and measured
# So this control system is stablising the motors and ensuring they're working as exact as they can be by reading data from the encoders

def clamp(value, minimum, maximum):
    return max(minimum, min(value, maximum))


def calculate_turning(throttle, steering):
    motor_left = throttle - steering
    motor_right = throttle + steering

    # Keep motor values within valid range
    motor_left = clamp(motor_left, -100, 100)
    motor_right = clamp(motor_right, -100, 100)

    return motor_left, motor_right


error = reference - measured      # Calculate Error

if error > 0:
    throttle = 100                # Move forwards
elif error < 0:
    throttle = -100               # Move backwards
else:
    throttle = 0                  # Stop


def main():

    print("What is the steering?")
    steering = int(input())

    if steering > 540 or steering < -540:
        print("Steering value not valid")

    else:
        # Convert steering wheel range into motor steering range
        steering_scaled = steering / 5.4

        left, right = calculate_turning(throttle, steering_scaled)

        print("Error:", error)
        print("Throttle:", throttle)
        print("Left Motor:", left)
        print("Right Motor:", right)


main()