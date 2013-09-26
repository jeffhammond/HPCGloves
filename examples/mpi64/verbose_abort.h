/* See LICENSE in top directory.
 * 
 * Author(s):
 *
 * Jeff R. Hammond 
 * Leadership Computing Facility 
 * Argonne National Laboratory
 * jhammond@anl.gov
 */

#ifndef INCLUDE_VERBOSE_ABORT_H
#define INCLUDE_VERBOSE_ABORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpi.h>

#ifdef CHECK_MPI_RETURN_CODES
/* this is only valid if MPI_ERRORS_RETURN */
static void MPIX_Verbose_abort(int errorcode)
{
    /* We do not check error codes here
     * because if MPI is in a really sorry state,
     * all of them might fail. */

    int rank;
    MPI_Comm_rank(MPI_COMM_RANK, &rank);

    int errorclass;
    int resultlen;
    char errorstring[MPI_MAX_ERROR_STRING];

    memset(errorstring, 0, MPI_MAX_ERROR_STRING); /* optional */

    MPI_Error_class(errorcode, &errorclass);
    fprintf(stderr, "%d: MPI failed (%d: %s) \n", rank, errorclass, errorstring);

    MPI_Error_string(errorcode, char *string, int *resultlen)
    fprintf(stderr, "%d: MPI failed (%d: %s) \n", rank, errorclass, errorstring);

    fflush(stderr); /* almost certainly redundant with the following... */
    MPI_Abort(MPI_COMM_WORLD, errorclass);
    
    return;
}
#define MPI_ASSERT(rc)  \
        ((void) ((rc==MPI_SUCCESS) ? 0 : MPIX_Verbose_abort(rc) ))
#else
/* Assume MPI_ERRORS_ARE_FATAL, which is the default behavior. */
/* Define MPI_ASSERT to (void)0 in case someone foolishly tries
 * to check its return value. */
#define MPI_ASSERT(rc) (rc)
#endif

#endif // INCLUDE_VERBOSE_ABORT_H
