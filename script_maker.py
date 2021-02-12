import math


f = open("script2.txt", "w")
f.write("sky-color 0.2 0.8 1\n")
x = y = 0
z = 200
pitch = yaw = roll = 0
pitch = -20
for i in range(0, 360):
    x = -450*math.cos(float(i)*3.14 / 180) + 450
    y = -450*math.sin(float(i)*3.15 / 180)

    yaw = i
    f.write(f"camera-direction {yaw} {pitch} {roll}\n")
    f.write(f"camera-move {x} {y} {z}\n")
    f.write("render\n")
f.close()
