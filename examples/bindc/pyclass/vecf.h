#ifndef VECF_H_
#define VECF_H_

#include<stdio.h>
#include<stdlib.h>

// bind(c) compatible struct declaration
typedef struct {
    double x, y, z;
} cartesian;

// In Fortran
void unit_step(cartesian *arg);

#endif // VECF_H_
