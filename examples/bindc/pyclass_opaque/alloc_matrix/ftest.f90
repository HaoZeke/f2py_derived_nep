program test_matrix
  use matrix_mod
  implicit none

  type(matrix_type) :: mat
  real, allocatable :: row_data(:), col_data(:)
  integer :: i

  ! Create a 3x3 matrix
  call create_matrix(mat, 3, 3)

  ! Set data to the first row
  allocate(row_data(3))
  row_data = [1.0, 2.0, 3.0]
  call set_row(mat, 1, row_data)

  ! Set data to the second column
  allocate(col_data(3))
  col_data = [4.0, 5.0, 6.0]
  call set_column(mat, 2, col_data)

  ! Print the matrix data
  do i = 1, 3
    print *, mat%data(i, :)
  end do

  ! Destroy the matrix
  call destroy_matrix(mat)

  ! Free allocated vectors
  deallocate(row_data)
  deallocate(col_data)

end program test_matrix
