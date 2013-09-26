CC = gcc
FC = gfortran

CFLAGS = -g -std=c99
FFLAGS = -g -std=f2008 -ffree-form

LIBS = library.o

.PHONY: clean

all: app.x

app.x: app.f module.mod $(LIBS)
	$(FC) $(FFLAGS)    $< -o $@ $(LIBS)

module.mod: module.f
	$(FC) $(FFLAGS) -c $< -o $@

library.o: library.c library.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f *.o *.mod *.x
	-rm -rf *.dSYM # Mac only

