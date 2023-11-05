#include <stdio.h>

// Assuming the Fortran functions have been declared with bind(C)
// and their names are unchanged in the linking process

// Declarations of Fortran functions
extern void *c_new_point(double x, double y);
extern void c_delete_point(void **p);
extern double c_get_x(void **p);
extern void c_set_x(void **p, double x);
extern double c_get_y(void **p);
extern void c_set_y(void **p, double y);

int main() {
  // Create a new point using the Fortran function
  void *point = c_new_point(3.0, 4.0);
  if (point == NULL) {
    fprintf(stderr, "Failed to create point\n");
    return 1;
  }
  /* Retrieve the x and y values using the Fortran function */
  double x = c_get_x(&point);
  double y = c_get_y(&point);

  printf("Point coordinates: x = %f, y = %f\n", x, y);

  /* Set the x and y values using the Fortran function */
  c_set_x(&point, 5.0);
  c_set_y(&point, 6.0);

  printf("Point coordinates after set: x = %f, y = %f\n", c_get_x(&point),
         c_get_y(&point));

  // Clean up and delete the point using the Fortran function
  c_delete_point(&point);

  return 0;
}
