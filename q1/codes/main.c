#include <stdio.h>
#include "collinear.c"
int areCollinear(Point3D* p1, Point3D* p2, Point3D* p3);
int main() {
    Point3D p1 = {2, 3, -4};
    Point3D p2 = {1, -2, 3};
    Point3D p3 = {3, 8, -11};

    if (areCollinear(&p1, &p2, &p3)) {
        printf("The points are collinear.\n");
    } else {
        printf("The points are not collinear.\n");
    }

    return 0;
}




