module point_module
    implicit none

    type :: Point
        real(8) :: x
        real(8) :: y
    end type Point

contains

    subroutine create_point(x, y, p, alloc_stat)
        real(8), intent(in) :: x, y
        type(Point), pointer :: p
        integer, intent(out), optional :: alloc_stat

        allocate(p, stat=alloc_stat)
        if (present(alloc_stat) .and. alloc_stat /= 0) then
            return
        endif
        p%x = x
        p%y = y
    end subroutine create_point

    subroutine destroy_point(p)
        type(Point), pointer :: p
        if (associated(p)) then
           deallocate(p)
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

    ! Additional subroutines for move_point, etc. would go here.

end module point_module
