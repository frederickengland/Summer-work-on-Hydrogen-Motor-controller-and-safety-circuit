power = "on"

# Fault conditions
overheating = False
overcurrent = False
sensor_fault = False


def dangerous_situation():

    if overcurrent:
        return True

    if overheating:
        return True

    if sensor_fault:
        return True

    return False


while not dangerous_situation():

    power = "on"
    print("Drivetrain running")

    # Example fault appearing
    overheating = True


power = "off"
print("EMERGENCY SHUTDOWN")