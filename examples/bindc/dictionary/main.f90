program main
  use vec
  implicit none
  type(cartesian) :: cartvec
  cartvec = cartesian(0.1, 0.2, 0.3)
  print*, cartvec
  call unit_step(cartvec)
  print*, cartvec
end program main
