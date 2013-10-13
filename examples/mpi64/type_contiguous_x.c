/* See LICENSE in top directory.
 * 
 * Author(s):
 *
 * Jeff R. Hammond 
 * Leadership Computing Facility 
 * Argonne National Laboratory
 * jhammond@anl.gov
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defines INT32_MAX, which is not appropriate for int types. */
#include <stdint.h>

/* Defines INT_MAX */
#include <limits.h>

#include <mpi.h>
#include "bigmpix.h"

#define BIGMPI_MAX INT_MAX

/*
 * Synopsis
 *
 * int MPIX_Type_contiguous_x(MPI_Count      count,
 *                            MPI_Datatype   oldtype,
 *                            MPI_Datatype * newtype)
 *                         
 *  Input Parameters
 *
 *   count             replication count (nonnegative integer)
 *   oldtype           old datatype (handle)
 *
 * Output Parameter
 *
 *   newtype           new datatype (handle)
 *
 */
int MPIX_Type_contiguous_x(MPI_Count count, MPI_Datatype oldtype, MPI_Datatype * newtype)
{
    MPI_Count c = count/BIGMPI_MAX;
    MPI_Count r = count%BIGMPI_MAX;

    MPI_Datatype chunk;
    MPI_ASSERT(MPI_Type_contiguous(BIGMPI_MAX, oldtype, &chunk));

    MPI_Datatype chunks;
    MPI_ASSERT(MPI_Type_contiguous(c, chunk, &chunks));

    MPI_Datatype remainder;
    MPI_ASSERT(MPI_Type_contiguous(r, oldtype, &remainder));

    int typesize;
    MPI_ASSERT(MPI_Type_size(oldtype, &typesize));

    MPI_Aint remdisp                   = (MPI_Aint)c*BIGMPI_MAX*typesize; /* must explicit-cast to avoid overflow */
    int array_of_blocklengths[2]       = {1,1};
    MPI_Aint array_of_displacements[2] = {0,remdisp};
    MPI_Datatype array_of_types[2]     = {chunks,remainder};

    MPI_ASSERT(MPI_Type_create_struct(2, array_of_blocklengths, array_of_displacements, array_of_types, newtype));
    MPI_ASSERT(MPI_Type_commit(newtype));

    MPI_ASSERT(MPI_Type_free(&chunk));
    MPI_ASSERT(MPI_Type_free(&chunks));
    MPI_ASSERT(MPI_Type_free(&remainder));

    return MPI_SUCCESS;
}

