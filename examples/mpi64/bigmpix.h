/* See LICENSE in top directory.
 * 
 * Author(s):
 *
 * Jeff R. Hammond 
 * Leadership Computing Facility 
 * Argonne National Laboratory
 * jhammond@anl.gov
 */

#ifndef INCLUDE_BIGMPIX_H
#define INCLUDE_BIGMPIX_H

#include <stdint.h>
#include <limits.h>

#include <mpi.h>

int MPIX_Type_contiguous_x(MPI_Count count, MPI_Datatype oldtype, MPI_Datatype * newtype);

#endif // INCLUDE_BIGMPIX_H
