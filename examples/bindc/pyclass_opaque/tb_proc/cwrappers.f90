! cwrappers.f90
! C interoperable wrappers
module c_wrappers
   use, intrinsic :: iso_c_binding, only: c_ptr, c_double, c_null_ptr, &
                                                                             c_loc, c_associated, c_f_pointer
   use point_module
   implicit none

contains

   ! Wrapper for creating a new point
   function c_new_point(x, y) bind(C, name="c_new_point")
      real(c_double), value :: x, y
      type(c_ptr) :: c_new_point
      type(Point), pointer :: p
      integer :: stat

      call create_point(x, y, p, stat)
      if (stat /= 0) then
         print *, "Allocation failed"
         c_new_point = C_NULL_PTR
         return
      end if

      c_new_point = c_loc(p)
   end function c_new_point

   ! Wrapper to set the x value of a point
   subroutine c_set_x(p_cptr, x) bind(c, name='c_set_x')
      type(c_ptr), intent(in) :: p_cptr
      real(c_double), intent(in), value :: x
      type(Point), pointer :: p

      call c_f_pointer(p_cptr, p)
      call set_x(p, x)
   end subroutine c_set_x

   ! Wrapper to get the x value of a point
   function c_get_x(p_cptr) bind(c, name='c_get_x') result(x)
      type(c_ptr), intent(in) :: p_cptr
      real(c_double) :: x
      type(Point), pointer :: p

      call c_f_pointer(p_cptr, p)
      x = get_x(p)
   end function c_get_x

   ! Wrapper to set the y value of a point
   subroutine c_set_y(p_cptr, y) bind(c, name='c_set_y')
      type(c_ptr), intent(in) :: p_cptr
      real(c_double), intent(in), value :: y
      type(Point), pointer :: p

      call c_f_pointer(p_cptr, p)
      call set_y(p, y)
   end subroutine c_set_y

   ! Wrapper to get the y value of a point
   function c_get_y(p_cptr) bind(c, name='c_get_y') result(y)
      type(c_ptr), intent(in) :: p_cptr
      real(c_double) :: y
      type(Point), pointer :: p

      call c_f_pointer(p_cptr, p)
      y = get_y(p)
   end function c_get_y

   ! Wrapper for deallocating a point
   subroutine c_delete_point(p_cptr) bind(c, name='c_delete_point')
      type(c_ptr), intent(inout) :: p_cptr
      type(Point), pointer :: p

      if (.not. c_associated(p_cptr)) return
      call c_f_pointer(p_cptr, p)
      call destroy_point(p)
      p_cptr = c_null_ptr
   end subroutine c_delete_point

   ! Wrapper to call the type-bound procedure euclidean_distance
   ! TST: Check this in Fortran too
   function c_euclidean_distance(this_cptr, other_cptr) bind(c) result(y)
      type(c_ptr), value :: this_cptr, other_cptr
      real(c_double) :: y
      type(Point), pointer :: p1, p2

      ! Convert C pointers to Fortran pointers
      call c_f_pointer(this_cptr, p1)
      call c_f_pointer(other_cptr, p2)

      ! Now you can use the type-bound procedure
      y = p1%euclidean_distance(p2)
   end function c_euclidean_distance

end module c_wrappers
