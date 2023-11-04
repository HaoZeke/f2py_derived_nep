#ifndef VECF_H_
#define VECF_H_

#include<stdio.h>
#include<stdlib.h>

// In Fortran
extern void* c_new_point(float x, float y);
extern void c_set_x(void* p, float x);
extern float c_get_x(void* p);
extern void c_delete_point(void* p);

#endif // VECF_H_
