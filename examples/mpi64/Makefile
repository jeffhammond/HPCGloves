FLAGS = -g -O2 -Wall

CC = mpicc
FC = mpif90
LD = $(CC)

# C99 is required for our coding style.
CFLAGS = $(FLAGS) -std=c99 -DUSE_MPI_ALLOC_MEM 
FFLAGS = $(FLAGS) -std=f95
LDFLAGS = 

.PHONY: all clean realclean

LIBRARY = libbigmpi.a
OBJECTS = type_contiguous_x.o
HEADERS = verbose_abort.h
TESTS   = test_type_contig.x 

all: $(LIBRARY) $(TESTS)

$(LIBRARY): $(OBJECTS)
	-ar -r $(LIBRARY) $(OBJECTS)


%.x: %.c bigmpix.h Makefile
	$(CC) $(CFLAGS) $< $(LIBRARY) -o $@


%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@


clean: 
	-rm -f $(OBJECTS)
	-rm -f $(TESTS) 
	-rm -f $(LIBRARY)
	-rm -rf *.dSYM # Mac only

realclean: clean

