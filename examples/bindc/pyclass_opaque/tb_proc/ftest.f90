program test_point_module
   use point_module
   implicit none

   type(Point), pointer :: pt, pt2
   real(8) :: x_val, y_val, eucdistl
   integer :: alloc_status

   ! Test creating a new point
   call create_point(1.0d0, 2.0d0, pt, alloc_status)
   call create_point(2.0d0, 5.0d0, pt2, alloc_status)

   if ((.not. associated(pt)) .or. (.not. associated(pt2))) then
      print *, "Point creation failed with status ", alloc_status
      stop
   else
      print *, "Point created: (", pt%x, ", ", pt%y, ")"
      print *, "Point created: (", pt2%x, ", ", pt2%y, ")"
   end if

   ! Test calculating the Euclidean distance between two points
   eucdistl = pt%euclidean_distance(pt2)
   print *, "Euclidean distance between points is ", eucdistl
   if (abs(eucdistl - 3.1622776601683795d0) > 1e-14) then
      error stop "Euclidean distance is wrong"
   end if

   ! Test modifying the point's x and y values
   call set_x(pt, 5.0d0)
   call set_y(pt, 10.0d0)

   ! Test getting the point's x and y values
   x_val = get_x(pt)
   y_val = get_y(pt)

   print *, "After setting new values:"
   print *, "x =", x_val, "y =", y_val

   ! Check if the values are as expected
   if (x_val == 5.0d0 .and. y_val == 10.0d0) then
      print *, "Point values updated correctly."
   else
      print *, "Error in updating point values."
   end if

   ! Test destroying the point
   call destroy_point(pt)

   if (.not. associated(pt)) then
      print *, "Point destroyed successfully."
   else
      print *, "Error in destroying point."
   end if

end program test_point_module
