! See LICENSE in top directory.
! 
! Author(s):
! 
! Jeff R. Hammond 
! Leadership Computing Facility 
! Argonne National Laboratory
! jhammond@anl.gov
! 
program app
    use iso_c_binding
    use blis
    implicit none
    type(c_ptr) :: thing
    call bli_foo(thing)
    write(*,*) 'ALL DONE'
end program app
