#include <stdio.h>

// Assuming the Fortran functions have been declared with bind(C)
// and their names are unchanged in the linking process

// Declarations of Fortran functions
extern void *c_create_matrix(int rows, int cols);
extern void c_destroy_matrix(void **mat);
extern void c_set_row(void **mat, int row, double *values);
extern void c_set_col(void **mat, int col, double *values);
extern void c_get_column(void **p, int col, double *values);
extern void c_get_row(void **p, int row, double *values);

int main() {
  /* Create a new point using the Fortran function */
  void *mat = c_create_matrix(3, 3);
  if (mat == NULL) {
    fprintf(stderr, "Failed to create matrix\n");
    return 1;
  }

  /* Set the values of the matrix */
  /* double values[3] = {1.0, 2.0, 3.0}; */
  /* c_set_row(mat, 1, values); */
  /* c_set_row(mat, 1, values); */

  /* /\* Get the values of the matrix *\/ */
  double values2[3];
  /* c_get_row(mat, 0, values2); */
  /* printf("The first row is: %f, %f, %f\n", values2[0], values2[1], values2[2]); */

  /* Print the whole matrix */
  printf("The whole matrix is:\n");
  for (int i = 0; i < 3; i++) {
    c_get_row(mat, i+1, values2);
    printf("%f, %f, %f\n", values2[0], values2[1], values2[2]);
  }

  /* Destroy the matrix */
  c_destroy_matrix(&mat);
  return 0;
}
