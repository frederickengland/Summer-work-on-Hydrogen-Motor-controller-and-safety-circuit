overheating = False
overcurrent = False
overvoltage = False

component_temperature = 0
current_regulator = 0
voltage_regulator = 0

def driving(temperature):
    global overheating, overcurrent, overvoltage
    global current_regulator, voltage_regulator

    for i in range(100):
        temperature += 1
        current_regulator += 1
        voltage_regulator += 1

    if temperature >= 90:
        overheating = True

    if current_regulator >= 80:
        overcurrent = True

    if voltage_regulator >= 70:
        overvoltage = True


def main():
    driving(component_temperature)

    if overcurrent or overheating or overvoltage:
        print("Dangerous situation - shutdown")
    else:
        print("All good - keep driving")


main()