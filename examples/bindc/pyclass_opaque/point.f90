module point_module
   implicit none

   type :: Point
      real(8) :: x
      real(8) :: y
   contains
      procedure :: euclidean_distance
   end type Point

contains

   subroutine create_point(x, y, p, alloc_stat)
      real(8), intent(in) :: x, y
      type(Point), pointer :: p
      integer, intent(out), optional :: alloc_stat

      allocate (p, stat=alloc_stat)
      if (present(alloc_stat) .and. alloc_stat /= 0) then
         return
      end if
      p%x = x
      p%y = y
   end subroutine create_point

   subroutine destroy_point(p)
      type(Point), pointer :: p
      if (associated(p)) then
         deallocate (p)
         p => null()  ! This line nullifies the Fortran pointer
      end if
   end subroutine destroy_point

   function get_x(p) result(x_value)
      type(Point), intent(in) :: p
      real(8) :: x_value

      x_value = p%x
   end function get_x

   subroutine set_x(p, x)
      type(Point), intent(inout) :: p
      real(8), intent(in) :: x

      p%x = x
   end subroutine set_x

   function get_y(p) result(y_value)
      type(Point), intent(in) :: p
      real(8) :: y_value

      y_value = p%y
   end function get_y

   subroutine set_y(p, y)
      type(Point), intent(inout) :: p
      real(8), intent(in) :: y

      p%y = y
   end subroutine set_y

   real(8) function euclidean_distance(this, other) result(distance)
      class(Point), intent(in) :: this, other
      distance = sqrt((this%x - other%x)**2 + (this%y - other%y)**2)
   end function euclidean_distance

   ! Additional subroutines for move_point, etc. would go here.

end module point_module
