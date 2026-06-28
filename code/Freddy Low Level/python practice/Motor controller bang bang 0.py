reference = 0 # speed i want to go
measure = 0 # speed I'm at currently
error = reference - measure # difference between reference and measure

if error == 0:
    print("continue as normal")
if error > 0: # reference more than meausre
    print("speeding up")
if error < 0: # measure more than reference
    print("Slow down")