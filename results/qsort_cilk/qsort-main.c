/**********************************************************************
 *
 * qsort.c -- Sequential implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Time-stamp: <2018-10-10>
 *
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "qsort-sequential.h"
#include <assert.h>
#include <cilk/cilk.h> 
#include <cilk/cilk_api.h> 

/* local function declarations */
int  test( int *a, int n);
void init( int *a, int n);
void print(int *a, int n);


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}


/* --- Entry POINT --- */
int main(int argc, char **argv) {

  /* parse input */
 /* if (argc != 3) {
    printf("Usage: %s q p\n  where n=2^q is problem size and th=2^p is thread number (power of two)\n", 
	   argv[0]);
    exit(1);
  }*/
  
  int maxThreads;
  
 FILE *file_pointer; 
 file_pointer=fopen("Results.txt", "w");
 int p=1;
 int q=16;
  for (int p=1; p<9; p++) {
	maxThreads=1 <<p;
	for (int q=16; q<25; q++) {
  /* variables to hold execution time */
  struct timeval startwtime, endwtime;
  double seq_time, par_time , time_ratio;
 
  /* initiate vector of random integerts */
  int n  = 1<<q;
  int *a = (int *) malloc(n * sizeof(int));
  int *a_p = (int *) malloc(n * sizeof(int));
  int *a_s = (int *) malloc(n * sizeof(int));
 printf("Threads= %d\nArray Size= 2^%d\n",maxThreads,q);
   char nthreads[3]; 
  nthreads[0] = (char)(maxThreads/100+48);
  nthreads[1] = (char)((-10*(maxThreads/100))+maxThreads/10 +48);
  nthreads[2] = (char)(maxThreads%10 +48);
  /* initialize vector */
  init(a, n);
    for (int i=0; i<n; i++){
	  a_p[i]=a[i];
	  a_s[i]=a[i];
  }
	
  /* print vector */
  /* print(a, n); */
  
    //PARALLEL
  /* sort elements in original order */

  __cilkrts_set_param("nworkers", nthreads);
  gettimeofday (&startwtime, NULL);
  qsort_seq(a_p, n);
  gettimeofday (&endwtime, NULL);
__cilkrts_end_cilk();

  /* get time in seconds */
  par_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                      + endwtime.tv_sec - startwtime.tv_sec);

  /* validate result */
  int pass = test(a_p, n);
  printf("TEST %s\n",(pass) ? "PASSed" : "FAILed");
  assert( pass != 0 );
  
    /* print sorted vector */
  /* print(a, n); */
  
    
    //SEQUENTIAL
	
	  /* sort elements in original order */
  gettimeofday (&startwtime, NULL);
  qsort(a_s, n, sizeof(int), cmpfunc);
  gettimeofday (&endwtime, NULL);
  
     /*get time in seconds */
   seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                      + endwtime.tv_sec - startwtime.tv_sec);
					  
	/* validate result */
  int pass2 = test(a_s, n);
  printf("TEST %s\n",(pass2) ? "PASSed" : "FAILed");
  assert( pass2 != 0 );  
  
  /* print execution time */
  printf("Sequential wall clock time: %f sec\n", seq_time);
  printf("Parallel wall clock time: %f sec\n", par_time);
  time_ratio= seq_time/par_time;
  printf("Parallel algorithm was  %f times faster\n", time_ratio);
  
	fprintf(file_pointer,"%d %d %f %f %f\n",p,q,seq_time,par_time,time_ratio);
	}
	
  }
  fclose(file_pointer); 
  /* exit */
  return 0;
  
}

/** -------------- SUB-PROCEDURES  ----------------- **/ 

/** procedure test() : verify sort results **/
int test(int *a, int n) {

  int pass = 1; 

  for (int i=0; i<n; i++){

    if (a[i-1] > a[i]){
      pass = 0;
    }

  }

  return pass;
  
  
}

/** procedure init() : initialize array "a" with data **/
void init(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    a[i] = rand() % n; // (N - i);
  }
}

/** procedure  print() : print array elements **/
void print(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}
