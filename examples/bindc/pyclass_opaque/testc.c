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
extern double c_euclidean_distance(void *p1, void *p2);

int main() {
  /* Create a new point using the Fortran function */
  void *pt = c_new_point(1.0, 2.0);
  if (pt == NULL) {
    fprintf(stderr, "Failed to create pt\n");
    return 1;
  }
  void *pt2 = c_new_point(2.0, 5.0);
  if (pt2 == NULL) {
    fprintf(stderr, "Failed to create pt2\n");
    return 1;
  }
  /* Calculate the euclidean distance between pt and pt2 */
  double edist = c_euclidean_distance(pt, pt2);
  printf("Euclidean distance between pt and pt2: %f\n", edist);
  /* Retrieve the x and y values using the Fortran function */
  double x = c_get_x(&pt);
  double y = c_get_y(&pt);

  printf("Pt coordinates: x = %f, y = %f\n", x, y);

  /* Set the x and y values using the Fortran function */
  c_set_x(&pt, 5.0);
  c_set_y(&pt, 6.0);

  printf("Pt coordinates after set: x = %f, y = %f\n", c_get_x(&pt),
         c_get_y(&pt));

  /* Clean up and delete the pt using the Fortran function */
  c_delete_point(&pt);
  c_delete_point(&pt2);

  return 0;
}
