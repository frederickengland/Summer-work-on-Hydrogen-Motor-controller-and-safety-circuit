safe = True
power = "on"

def dangerous_situation():
    return not safe


while not dangerous_situation():
    power = "on"
    print("Drivetrain running")

    # Example fault
    safe = False


power = "off"
print("EMERGENCY SHUTDOWN")