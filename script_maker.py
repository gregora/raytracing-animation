import math


f = open("script2.txt", "w")
x = y = 0
z = 200
pitch = yaw = roll = 0
pitch = -20
for i in range(0, 800):
    x = -450*math.cos(float(i)*3.14 / 180) + 450
    y = -450*math.sin(float(i)*3.15 / 180)

    yaw = i
    f.write("camera-direction %s. %s. %s.\n" % (yaw, pitch, roll))
    f.write("camera-move %s. %s. %s.\n" % (x, y, z))
    f.write("sky-color 0.2 0.8 1\n")
    f.write("render\n")
f.close()
