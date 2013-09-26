! See LICENSE in top directory.
! 
! Author(s):
! 
! Jeff R. Hammond 
! Leadership Computing Facility 
! Argonne National Laboratory
! jhammond@anl.gov
!
module blis
    use iso_c_binding
    implicit none
    interface 
        subroutine bli_foo(thing) bind(c, name='bli_foo')
            import :: c_ptr
            type (c_ptr), value :: thing
        end subroutine ! bli_foo
    end interface
end module blis
