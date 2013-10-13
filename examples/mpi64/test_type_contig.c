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

#include <mpi.h>
#include "bigmpix.h"

// int MPIX_Type_contiguous_x(MPI_Count count, MPI_Datatype oldtype, MPI_Datatype * newtype);

int main(int argc, char * argv[])
{
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int logn = (argc>1) ? atoi(argv[1]) : 32;
    MPI_Count count = (MPI_Count)1<<logn; /* explicit cast required */
    printf("count = %lld \n", count);

    MPI_Finalize();

    return 0;
}
