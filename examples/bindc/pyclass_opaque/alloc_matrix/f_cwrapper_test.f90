program test_matrix_c_wrappers
  use, intrinsic :: iso_c_binding, only: c_ptr, c_int, c_double
  use c_wrappers
  implicit none

  type(c_ptr) :: mat_cptr
  integer(c_int) :: rows, cols, i
  real(c_double), allocatable :: row_data(:), col_data(:)

  ! Define matrix size
  rows = 4
  cols = 3

  ! Allocate memory for one row and one column
  allocate(row_data(cols))
  allocate(col_data(rows))

  ! Create a matrix using the C wrapper
  mat_cptr = c_create_matrix(rows, cols)
  if (c_associated(mat_cptr)) then
    print *, "Matrix created successfully."
  else
    print *, "Matrix creation failed."
    stop
  endif

  ! Set data for a row and a column
  row_data = [1.0_c_double, 2.0_c_double, 3.0_c_double]
  call c_set_row(mat_cptr, 1, row_data)

  col_data = [4.0_c_double, 5.0_c_double, 6.0_c_double, 7.0_c_double]
  call c_set_column(mat_cptr, 1, col_data)

  ! Reset arrays to zero to verify that the get functions work
  row_data = 0.0
  col_data = 0.0

  ! Get the row and column data from the matrix
  call c_get_row(mat_cptr, 1, row_data)
  print *, "Row 1 data:", row_data

  call c_get_column(mat_cptr, 1, col_data)
  print *, "Column 1 data:", col_data

  ! Destroy the matrix using the C wrapper
  call c_destroy_matrix(mat_cptr)
  if (.not. c_associated(mat_cptr)) then
    print *, "Matrix destroyed successfully."
  else
    print *, "Matrix destruction failed."
  endif

  ! Deallocate local arrays
  deallocate(row_data, col_data)

end program test_matrix_c_wrappers
