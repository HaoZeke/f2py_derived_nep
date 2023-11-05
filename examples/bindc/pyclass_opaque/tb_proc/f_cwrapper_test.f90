program test_point
   use, intrinsic :: iso_c_binding
   use point_module
   use c_wrappers
   implicit none

   type(c_ptr) :: p_cptr, p_cptr2
   real(c_double) :: x, y, dist
   real(c_double) :: retrieved_x, retrieved_y

   ! Test creating a new point
   x = 1.0_c_double
   y = 2.0_c_double
   p_cptr = c_new_point(x, y)
   if (.not. c_associated(p_cptr)) then
      print *, "Error creating new point"
      stop
   end if

! Test creating a second new point
   x = 2.0_c_double
   y = 5.0_c_double
   p_cptr2 = c_new_point(x, y)
   if (.not. c_associated(p_cptr2)) then
      print *, "Error creating new point for distance test"
      stop
   end if

! Test calculating the Euclidean distance between two points
   dist = c_euclidean_distance(p_cptr, p_cptr2)
   print *, "Euclidean distance between the two points: ", dist

! Optionally, check if the distance is close to the expected value
! Note: Replace 'expected_distance' with the actual expected value calculated separately.
   if (abs(dist - 3.1622776601683795d0) > 1e-14_c_double) then
      print *, "Error in calculating the Euclidean distance"
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

   ! Test deleting the second point
   call c_delete_point(p_cptr2)
   if (c_associated(p_cptr2)) then
      print *, "Error deleting second point"
      stop
   end if
   print *, "Second point deleted successfully."

   print *, "All tests for c_euclidean_distance passed successfully."


   print *, "All tests passed successfully."

end program test_point
