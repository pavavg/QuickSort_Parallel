
GCC = gcc
CFLAGS = -O3

CMAIN=qsort

all: qsort-main.o qsort-sequential.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN)  -lpthread

%.o: %.c
	$(GCC) -c $(CFLAGS) $^  -lpthread

clean:
	rm -f *.o *~ $(CMAIN)
