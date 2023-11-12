module matrix_mod
  implicit none

  type :: matrix_type
    integer :: rows
    integer :: cols
    real(8), allocatable :: data(:,:)
    contains
      procedure, pass(self) :: get_row
  end type matrix_type

contains

  subroutine create_matrix(m, rows, cols, alloc_stat)
      type(matrix_type), pointer :: m
      integer, intent(in) :: rows, cols
      integer, intent(out), optional :: alloc_stat
      allocate(m)
      m%rows = rows
      m%cols = cols
      allocate(m%data(rows, cols))
      m%data = 0.0
  end subroutine create_matrix

  subroutine destroy_matrix(m)
    type(matrix_type), pointer :: m
    if (allocated(m%data)) then
      deallocate(m%data)
    endif
    if (associated(m)) then
      deallocate(m)
      m => null()  ! Nullify the pointer
    endif
  end subroutine destroy_matrix

  subroutine set_row(m, row, rowData)
    type(matrix_type), intent(inout) :: m
    integer, intent(in) :: row
    real(8), intent(in) :: rowData(:)

    print *, "Row is ", row
    print *, "Row data is ", rowData
    if (row < 1 .or. row > m%rows) then
      print *, "Error: Row index out of bounds."
      return
    endif

    if (size(rowData) /= m%cols) then
      print *, "Error: Row data size does not match number of columns."
      return
    endif

    m%data(row, :) = rowData
  end subroutine set_row

  subroutine get_row(self, row, rowData)
    class(matrix_type), intent(in) :: self
    integer, intent(in) :: row
    real(8), intent(out) :: rowData(:)

    print *, "Row is ", row
    if (row < 1 .or. row > self%rows) then
      print *, "Error: Row index out of bounds."
      return
    endif

    if (size(rowData) /= self%cols) then
      print *, "Error: Output row data size does not match number of columns."
      return
    endif

    rowData = self%data(row, :)
  end subroutine get_row

  subroutine set_column(m, col, colData)
    type(matrix_type), intent(inout) :: m
    integer, intent(in) :: col
    real(8), intent(in) :: colData(:)

    if (col < 1 .or. col > m%cols) then
      print *, "Error: Column index out of bounds."
      return
    endif

    if (size(colData) /= m%rows) then
      print *, "Error: Column data size does not match number of rows."
      return
    endif

    m%data(:, col) = colData
  end subroutine set_column

  subroutine get_column(m, col, colData)
    type(matrix_type), intent(in) :: m
    integer, intent(in) :: col
    real(8), intent(out) :: colData(:)

    if (col < 1 .or. col > m%cols) then
      print *, "Error: Column index out of bounds."
      return
    endif

    if (size(colData) /= m%rows) then
      print *, "Error: Output column data size does not match number of rows."
      return
    endif

    colData = m%data(:, col)
  end subroutine get_column

end module matrix_mod
