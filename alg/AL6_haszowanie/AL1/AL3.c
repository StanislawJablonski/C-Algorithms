// kompilowac z opcjami -lrt -lm: gcc L1.c -lrt -lm
#include <time.h>
#include <stdio.h>
#include <math.h>
#define MAX 60000l
#define MLD 1000000000.0 //10**9

double procedura3(int n) {
int i, j;
 	for (i=1; i<sqrt(n); i++) {
		j=i;
		while (j<sqrt(n)) {
			j++;
		}
	}
}

main(){
  struct timespec tp0, tp1;
  double Tn,Fn,x;
  int n;
for(n=2;n<2300;n=2*n){

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

// przykladowe obliczenia
    x=procedura3(n);

// zgadywana funkcja
    // Fn=5*n ; // np. funkcja liniowa
    //	     Fn=n*n*n ; 
          Fn=n*log(n); 
    //	       Fn=n*n*sqrt(n);
    //     Fn=n*n; 
    //	    Fn=n*n/1000 ; 
    
clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

  Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("n: %5d \tczas: %3.5lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
}
}
