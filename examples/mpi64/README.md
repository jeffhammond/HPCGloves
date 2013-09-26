BigMPI: Support for 64b integer count arguments in MPI

# Rationale

The MPI Forum declined to nearly double the size of the standard
in order to add a new variant of every function that currently
takes an C integer argument specify a count that can exceed the
range of a signed integer (usually 2^31).

As a result, programmers are required to deal with "large counts"
themselves, likely using one of two mechanisms:

(1) By creating a contiguous datatype that holds the large count
    worth of data without ever requiring a user argument that will
    overrun.

(2) Chopping a single message into many smaller ones such that
    each smaller message does not have an invalid argument.

# Features
 
We address (1) by providing the necessary function to efficiently
create this user-defined datatype.  The function name is consistent
with the MPICH rules for additional MPI-like functions outside
the standard (MPIX\_Foo) and with the MPI standard style for the MPI-3
functions provided to enable large count support 
(MPI\_Foo becomes MPI\_Foo\_x).

The following function takes the (count,type) pair from the user
that would lead to an overrun due to count exceeding the range of
a C integer and turns it into a user-defined datatype that can
be provided to any MPI communication function with newcount=1.


int MPIX\_Type\_contiguous\_x(MPI\_Count      count,
                              MPI\_Datatype   oldtype,
                              MPI\_Datatype * newtype)
                        
 Input Parameters
                                                           
  count             replication count (nonnegative integer)
  oldtype           old datatype (handle)
                                                           
Output Parameter
                                                           
  newtype           new datatype (handle)
                                                           
# Usage

See test\_type\_contig.c







