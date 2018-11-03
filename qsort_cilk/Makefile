
GCC = gcc
CFLAGS = -O3

CMAIN=qsort

all: qsort-main.o qsort-sequential.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN) -fcilkplus

%.o: %.c
	$(GCC) -c $(CFLAGS) $^ -fcilkplus

clean:
	rm -f *.o *~ $(CMAIN)
