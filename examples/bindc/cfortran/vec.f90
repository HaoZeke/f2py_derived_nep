  module vec
    use, intrinsic :: iso_c_binding
    implicit none

    type, bind(c) :: cartesian
       real(c_double) :: x, y, z
    end type cartesian

    contains
      subroutine unit_step(arg) bind(c)
        type(cartesian), intent(inout) :: arg
        print*, "Modifying derived type"
         arg%x = arg%x + 1
         arg%y = arg%y + 1
         arg%z = arg%z + 1
      end subroutine unit_step
end module vec
