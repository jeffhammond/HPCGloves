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
#include <assert.h>

#include <mpi.h>
#include "bigmpix.h"

// int MPIX_Type_contiguous_x(MPI_Count count, MPI_Datatype oldtype, MPI_Datatype * newtype);

int main(int argc, char * argv[])
{
    int provided;
    MPI_ASSERT(MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided));

    int rank, size;
    MPI_ASSERT(MPI_Comm_rank(MPI_COMM_WORLD, &rank));
    MPI_ASSERT(MPI_Comm_size(MPI_COMM_WORLD, &size));

    int logn = (argc>1) ? atoi(argv[1]) : 32;
    size_t count = (size_t)1<<logn; /* explicit cast required */
    printf("count = %zu \n", count );

    MPI_Datatype bigtype;
    MPI_ASSERT(MPIX_Type_contiguous_x( (MPI_Count)count, MPI_CHAR, &bigtype));
    MPI_ASSERT(MPI_Type_commit(&bigtype));

    char * rbuf = NULL;
    char * sbuf = NULL;

#ifdef USE_MPI_ALLOC_MEM
    MPI_ASSERT(MPI_Alloc_mem( (MPI_Aint)count * sizeof(char), MPI_INFO_NULL, &rbuf));
    MPI_ASSERT(MPI_Alloc_mem( (MPI_Aint)count * sizeof(char), MPI_INFO_NULL, &sbuf));
#else
    rbuf = malloc( count * sizeof(char)); assert(rbuf!=NULL);
    sbuf = malloc( count * sizeof(char)); assert(sbuf!=NULL);
#endif

    for (size_t i=0; i<count; i++)
        rbuf[i] = 'a';
    for (size_t i=0; i<count; i++)
        sbuf[i] = 'z';

    MPI_Request requests[2];
    MPI_Status statuses[2];

    if (rank==(size-1)) {
        MPI_ASSERT(MPI_Irecv(rbuf, 1, bigtype, 0,      0, MPI_COMM_WORLD, &(requests[1]) ));
    }
    if (rank==0) {
        MPI_ASSERT(MPI_Isend(sbuf, 1, bigtype, size-1, 0, MPI_COMM_WORLD, &(requests[0]) ));
    }

    MPI_Count ocount;

    if (size==1) {
        MPI_ASSERT(MPI_Waitall(2, requests, statuses));
        MPI_ASSERT(MPI_Get_elements_x( &(statuses[1]), MPI_CHAR, &ocount));
        printf("ocount = %lld \n", ocount);
    }
    else {
        if (rank==(size-1)) {
            MPI_ASSERT(MPI_Wait( &(requests[1]), &(statuses[1]) ));
            MPI_ASSERT(MPI_Get_elements_x( &(statuses[1]), MPI_CHAR, &ocount));
            MPI_Count errors = 0;
            for (MPI_Count i=0; i<count; i++)
                errors += ( rbuf[i] != 'z' );
            printf("errors = %lld \n", errors);
        } else if (rank==0) {
            MPI_ASSERT(MPI_Wait( &(requests[0]), &(statuses[0]) ));
            MPI_ASSERT(MPI_Get_elements_x( &(statuses[0]), MPI_CHAR, &ocount));
        }
        if (rank==0 || rank==(size-1) )
            printf("ocount = %lld \n", ocount);
    }

#ifdef USE_MPI_ALLOC_MEM
    MPI_ASSERT(MPI_Free_mem(rbuf));
    MPI_ASSERT(MPI_Free_mem(sbuf));
#else
    free(rbuf);
    free(sbuf);
#endif

    MPI_ASSERT(MPI_Type_free(&bigtype));

    MPI_ASSERT(MPI_Finalize());

    return 0;
}
