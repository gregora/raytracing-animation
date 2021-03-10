import math


f = open("script3.txt", "w")
x = y = 0
z = 2
pitch = yaw = roll = 0
pitch = 0
for i in range(0, 360):
    x = -40*math.cos(float(i)*3.14 / 180) + 40
    y = -40*math.sin(float(i)*3.15 / 180)

    yaw = i
    f.write("camera-direction %s. %s. %s.\n" % (yaw, pitch, roll))
    f.write("camera-move %s. %s. %s.\n" % (x, y, z))
    f.write("sky-color 0.05 0.2 0.3\n")
    f.write("render\n")
f.close()
