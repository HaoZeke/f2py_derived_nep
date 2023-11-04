program test_point
    use, intrinsic :: iso_c_binding
    use point_module
    use c_wrappers
    implicit none

    type(c_ptr) :: p_cptr
    real(c_double) :: x, y
    real(c_double) :: retrieved_x, retrieved_y

    ! Test creating a new point
    x = 1.0_c_double
    y = 2.0_c_double
    p_cptr = c_new_point(x, y)
    if (.not. c_associated(p_cptr)) then
        print *, "Error creating new point"
        stop
    end if

    ! Retrieve the x and y values using the Fortran function
    retrieved_x = c_get_x(p_cptr)
    retrieved_y = c_get_y(p_cptr)
    print *, "Point created: (", retrieved_x, ", ", retrieved_y, ")"

    ! Test setting and getting the x value
    call c_set_x(p_cptr, 3.0_c_double)
    retrieved_x = c_get_x(p_cptr)
    if (retrieved_x /= 3.0_c_double) then
        print *, "Error with set_x or get_x"
        stop
    end if
    print *, "X value set and retrieved correctly."

    ! Test setting and getting the y value
    call c_set_y(p_cptr, 4.0_c_double)
    retrieved_y = c_get_y(p_cptr)
    if (retrieved_y /= 4.0_c_double) then
        print *, "Error with set_y or get_y"
        stop
    end if
    print *, "Y value set and retrieved correctly."

    ! Test deleting the point
    call c_delete_point(p_cptr)
    if (c_associated(p_cptr)) then
        print *, "Error deleting point"
        stop
    end if
    print *, "Point deleted successfully."

    print *, "All tests passed successfully."

end program test_point
