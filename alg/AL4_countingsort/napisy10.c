// wskazowka do sortowania pozycyjnego
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MDN 254 // maks. dlugosc napisu
#define MN 10 // maks il napisow

char **A,**B,**T;

void drukuj(char **A,int n){
  // drukuje  drugie litery napisow i napisy  
  int i;
  for (i=0;i<n;i++){
    printf("%c %s",*(A[i]+1),A[i]);  
//czyli   printf("%c %s",*(*(A+i)+1),*(A+i));  
    printf("\n");
  }
}

void czytaj(char **A, int ilosc){
 char slowo[MDN];
 int i=0;
 for (i=0;i<ilosc; i++){
    scanf("%s",slowo);
    A[i] = (char*) malloc(sizeof(char)*MDN);
    strcpy(A[i],slowo);
 }
}

int main(){
  int n=2;
  A=(char**) malloc(n*sizeof(char*));
  B=(char**) malloc(n*sizeof(char*));
  printf("tablica A: \n"); czytaj(A,n); 
  printf("tablica B: \n"); czytaj(B,n); 
  printf("tablica A: \n"); drukuj(A,n);
  printf("tablica B: \n"); drukuj(B,n);
  printf("zamiana \n"); T=A; A=B; B=T; 
  printf("tablica A: \n"); drukuj(A,n);
  printf("tablica B: \n"); drukuj(B,n);
}
