from ctypes import *
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Load the shared object file
collinear_lib = CDLL('./collinear.so')

# Define the Point3D structure
class Point3D(Structure):
    _fields_ = [("x", c_int), ("y", c_int), ("z", c_int)]

# Define the argument and return types of the C function
collinear_lib.areCollinear.argtypes = [POINTER(Point3D), POINTER(Point3D), POINTER(Point3D)]
collinear_lib.areCollinear.restype = c_int

def check_collinearity(p1, p2, p3):
    return collinear_lib.areCollinear(byref(p1), byref(p2), byref(p3))

# Define three 3D points
point1 = Point3D(2, 3, -4)
point2 = Point3D(1, -2, 3)
point3 = Point3D(3, 8, -11)

# Check if they are collinear
collinear = check_collinearity(point1, point2, point3)

# Print result
if collinear:
    print("The points are collinear.")
else:
    print("The points are not collinear.")

# Visualization
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot points
ax.scatter([point1.x, point2.x, point3.x], 
           [point1.y, point2.y, point3.y], 
           [point1.z, point2.z, point3.z], color='r')

# Add labels for each point
ax.text(point1.x, point1.y, point1.z, "(2, 3, -4)", color='black', fontsize=12)
ax.text(point2.x, point2.y, point2.z, "(1, -2, 3)", color='black', fontsize=12)
ax.text(point3.x, point3.y, point3.z, "(3, 8, -11)", color='black', fontsize=12)

# Plot lines between points for better visualization
ax.plot([point1.x, point2.x], [point1.y, point2.y], [point1.z, point2.z], color='b')
ax.plot([point2.x, point3.x], [point2.y, point3.y], [point2.z, point3.z], color='b')

# Labels
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.savefig("fig_1.png")
plt.show()

