module matrix_mod
  implicit none

  type :: matrix_type
    integer :: rows
    integer :: cols
    real, allocatable :: data(:,:)
  end type matrix_type

contains

  subroutine create_matrix(m, rows, cols)
    type(matrix_type), intent(out) :: m
    integer, intent(in) :: rows, cols

    m%rows = rows
    m%cols = cols
    allocate(m%data(rows, cols))
  end subroutine create_matrix

  subroutine destroy_matrix(m)
    type(matrix_type), intent(inout) :: m
    if (allocated(m%data)) then
      deallocate(m%data)
    endif
    m%rows = 0
    m%cols = 0
  end subroutine destroy_matrix

  subroutine set_row(m, row, rowData)
    type(matrix_type), intent(inout) :: m
    integer, intent(in) :: row
    real, intent(in) :: rowData(:)

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

  subroutine get_row(m, row, rowData)
    type(matrix_type), intent(in) :: m
    integer, intent(in) :: row
    real, intent(out) :: rowData(:)

    if (row < 1 .or. row > m%rows) then
      print *, "Error: Row index out of bounds."
      return
    endif

    if (size(rowData) /= m%cols) then
      print *, "Error: Output row data size does not match number of columns."
      return
    endif

    rowData = m%data(row, :)
  end subroutine get_row

  subroutine set_column(m, col, colData)
    type(matrix_type), intent(inout) :: m
    integer, intent(in) :: col
    real, intent(in) :: colData(:)

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
    real, intent(out) :: colData(:)

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
