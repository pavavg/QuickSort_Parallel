
GCC = gcc
CFLAGS = -O3

CMAIN=qsort

all: qsort-main.o qsort-sequential.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN) -fopenmp

%.o: %.c
	$(GCC) -c $(CFLAGS) $^ -fopenmp

clean:
	rm -f *.o *~ $(CMAIN)
