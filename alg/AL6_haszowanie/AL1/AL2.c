// kompilowac z opcjami -lrt -lm: gcc L1.c -lrt -lm
#include <time.h>
#include <stdio.h>
#include <math.h>
#define MAX 60000l
#define MLD 1000000000.0 //10**9

int max(int x,int suma)
{
   int c = 0;

   c = (x > suma) ? x : suma;
   return c;
}

double procedura2(int n) {
  int A[n];
  int d, g, i;
  float x=0.0;
 for (d=1; d<n; d++) for (g=d; g<n; g++)
			{
			  float suma=0.0;
			  for (i=d; i<g; i++) suma=suma+A[i];
			  x=max(x,suma);
			}
      return x;
}

//double procedura1(int n){
// float x=0;
// int i,j,k;

// for(i=n-1;i>1;i--) {
//  if((i % 2) == 1) {
//    for(j=1;j<i+1;j++) ; 
//    for(k=i+1;k<n+1;k++) x=x+1;
//    }
// } 
// return x;
//}

main(){
  struct timespec tp0, tp1;
  double Tn,Fn,x;
  int n;
for(n=2;n<2300;n=2*n){

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

// przykladowe obliczenia
    x=procedura2(n);

// zgadywana funkcja
    //     Fn=5*n ; // np. funkcja liniowa
        Fn=n*n*n ; 
    //        Fn=n*log(n); 
	 //      Fn=n*n*sqrt(n);
    //      Fn=n*n; 
	//    Fn=n*n/1000 ; 
    
clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

  Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("n: %5d \tczas: %3.5lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
}
}
