#include <stdio.h>

typedef struct {
    int x;
    int y;
    int z;
} Point3D;

// Function to check if three points are collinear
int areCollinear(Point3D* p1, Point3D* p2, Point3D* p3) {
    // Use vector cross product to check collinearity
    int cross_x = (p2->y - p1->y) * (p3->z - p1->z) - (p2->z - p1->z) * (p3->y - p1->y);
    int cross_y = (p2->z - p1->z) * (p3->x - p1->x) - (p2->x - p1->x) * (p3->z - p1->z);
    int cross_z = (p2->x - p1->x) * (p3->y - p1->y) - (p2->y - p1->y) * (p3->x - p1->x);
    
    // If cross product is zero, the points are collinear
    return (cross_x == 0 && cross_y == 0 && cross_z == 0);
}
