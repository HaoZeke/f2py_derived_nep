#ifndef VECF_H_
#define VECF_H_

#include <stdio.h>
#include <stdlib.h>

/* In Fortran */
extern void *c_new_point(double x, double y);
extern void c_delete_point(void **point);
extern double c_get_x(void *point);
extern void c_set_x(void *point, double x);
extern double c_get_y(void *point);
extern void c_set_y(void *point, double y);
extern double c_euclidean_distance(void *p1, void *p2);


#endif
