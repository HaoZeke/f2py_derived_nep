/* C file: point.c */
#include "point.h"

/* Function to create a new Point */
Point* create_point(double x, double y) {
    Point* p = (Point*) malloc(sizeof(Point));
    if (p != NULL) {
        p->x = x;
        p->y = y;
    }
    return p;
}

/* Function to delete a Point */
void destroy_point(Point* p) {
    free(p);
}

/* Function to move the Point */
void move_point(Point* p, double dx, double dy) {
    if (p != NULL) {
        p->x += dx;
        p->y += dy;
    }
}

/* Function to get the coordinates of the Point */
double get_x(const Point* p) {
    return p->x;
}
double get_y(const Point* p) {
    return p->y;
}
/* Function to set the coordinates of the Point */
void set_x(Point* p, double x) {
    p->x = x;
}
void set_y(Point* p, double y) {
    p->y = y;
}
