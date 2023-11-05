! cwrappers.f90
module c_wrappers
  use, intrinsic :: iso_c_binding, only: c_ptr, c_int, c_double, c_null_ptr, &
                                         c_loc, c_associated, c_f_pointer
  use matrix_mod
  implicit none

contains

   function c_create_matrix(rows, cols) bind(C)
     integer(c_int), value :: rows, cols
     type(c_ptr) :: c_create_matrix
     type(matrix_type), pointer :: m

     call create_matrix(m, rows, cols)
     if (.not. allocated(m%data)) then
       c_create_matrix = c_null_ptr
       return
     endif

     c_create_matrix = c_loc(m)
   end function c_create_matrix

   subroutine c_destroy_matrix(mat_cptr) bind(C)
     type(c_ptr), intent(inout) :: mat_cptr
     type(matrix_type), pointer :: m

     if (.not. c_associated(mat_cptr)) return
     call c_f_pointer(mat_cptr, m)
     if (allocated(m%data)) then
       call destroy_matrix(m)
     endif
     mat_cptr = c_null_ptr
   end subroutine c_destroy_matrix

  subroutine c_set_row(mat_cptr, row, row_data) bind(C)
    type(c_ptr), intent(in) :: mat_cptr
    integer(c_int), intent(in), value :: row
    real(c_double), intent(in) :: row_data(:)
    type(matrix_type), pointer :: m

    call c_f_pointer(mat_cptr, m)
    call set_row(m, row, row_data)
  end subroutine c_set_row

  subroutine c_set_column(mat_cptr, col, col_data) bind(C)
    type(c_ptr), intent(in) :: mat_cptr
    integer(c_int), intent(in), value :: col
    real(c_double), intent(in) :: col_data(:)
    type(matrix_type), pointer :: m

    call c_f_pointer(mat_cptr, m)
    call set_column(m, col, col_data)
  end subroutine c_set_column

  subroutine c_get_row(mat_cptr, row, row_data) bind(C)
    type(c_ptr), intent(in) :: mat_cptr
    integer(c_int), intent(in), value :: row
    real(c_double), intent(out) :: row_data(:)
    type(matrix_type), pointer :: m

    call c_f_pointer(mat_cptr, m)
    call get_row(m, row, row_data)
  end subroutine c_get_row

  subroutine c_get_column(mat_cptr, col, col_data) bind(C)
    type(c_ptr), intent(in) :: mat_cptr
    integer(c_int), intent(in), value :: col
    real(c_double), intent(out) :: col_data(:)
    type(matrix_type), pointer :: m

    call c_f_pointer(mat_cptr, m)
    call get_column(m, col, col_data)
  end subroutine c_get_column

end module c_wrappers
