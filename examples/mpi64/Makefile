FLAGS = -g -O2 -Wall

CC = mpicc
FC = mpif90
LD = $(CC)

# C99 is required for our coding style.
CFLAGS = $(FLAGS) -std=c99
FFLAGS = $(FLAGS) -std=f95
LDFLAGS = 

.PHONY: all clean realclean

LIBRARY = libbigmpi.a
OBJECTS = type_contiguous_x.o
HEADERS = verbose_abort.h
TESTS   = test_type_contig.x

all: $(LIBRARY) $(TESTS)


%.x: %.c bigmpi_mpix.h
	$(CC) $(CFLAGS) $< $(LIBRARY) -o $@


$(LIBRARY): $(OBJECTS)
	-ar -r $(LIBRARY) $(OBJECTS)


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@


clean: 
	-rm -f $(OBJECTS)


realclean: clean 
	-rm -f $(TESTS) 
	-rm -f $(LIBRARY)


