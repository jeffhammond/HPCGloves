Wrapping C library calls into F2003 modules 

# Rationale

Wrapping C libraries into Fortran can be painful because of 
some of the shortcomings of Fortran, but otherwise because
interoperability between languages has historically been an
area where much voodoo was required (underscores are just the
beginning...).

# Features
 
Not dealing with undercores.

Type safety (one hopes).

# Usage

This example demonstrates how one can wrap a library call
that is implemented in library.c and declare in library.h
within a Fortran application app.f using the module defined
in module.f.

One does not need the library implementation source code,
only the declaration; it is included here as part of the
example.  The C library declaration is only required to
generate module.f; it is not required by the Fortran 
application and is only included so that the example works.


