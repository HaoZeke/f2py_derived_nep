#ifndef POINT_H_
#define POINT_H_

#include "stddef.h"
#include "stdlib.h"

typedef struct {
    double x, y;
} Point;

Point* create_point(double x, double y);
void destroy_point(Point* p);
void move_point(Point* p, double dx, double dy);
double get_x(const Point* p);
void set_x(Point* p, double x);
double get_y(const Point* p);
void set_y(Point* p, double y);

#endif // POINT_H_
