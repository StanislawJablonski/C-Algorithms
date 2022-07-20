#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MDN 254 // maks. dlugosc napisu
#define RANGE 128

void sortPozycyjne(char **A, char **B, int amount);
void sortPrzezZliczanie(char **A, char **B, int ilosc, int pozycja);
void quicksort(char** a, int p, int r);
void zapisz (char **A, int amount) ;

int main(int argc, char *argv[]) {
	int n = 1000;
	char ** A = (char**) malloc(n*sizeof(char*));
	char ** B = (char**) malloc(n*sizeof(char*));
	char ** C = (char**) malloc(n*sizeof(char*));

	czytaj(A,n);
	czytaj(C,n);
	

	printf("Sortowanie %i nazwisk", n);
	
	
	struct timeval time1, time2, timeresult;
	
	gettimeofday(&time1, NULL);
	
		sortPozycyjne(A, B, n);
	
	gettimeofday(&time2, NULL);

	printf("\n\nSortowanie pozycyjne: %ld.%06ld", (time2.tv_sec - time1.tv_sec), (time2.tv_usec - time1.tv_usec));
	
	gettimeofday(&time1, NULL);
	
		quicksort(C, 0, n);
	
	gettimeofday(&time2, NULL);

	printf("\n\nSortowanie Quicksort: %ld.%06ld\n", (time2.tv_sec - time1.tv_sec), (time2.tv_usec - time1.tv_usec));

	zapisz(A, n);
	
}


int longestWord(char **a, int amount) { 
    int i, max = 0;
    
    for (i = 0; i < amount; i++)
            if (strlen(a[i]) > max) max = strlen(a[i]);
            
    return max;
}

void makeSameLength(char **a, int amount, int longest){
                 // to uzupelnia brakujace miejsca nullam
    int i, j;
    
    for (i = 0; i < amount; i++) 
        for (j = 1; j < longest; j++)
			
            if (!((int)a[i][j] > 96 && (int)a[i][j] < 123)) 
				a[i][j] = 0;
					
}

void sortPozycyjne(char **A, char **B, int amount) {
    int i;
    char** pom;
    
    int longest = longestWord(A, amount);	
	makeSameLength(A, amount, longest);
    
    for (i = longest; i >= 0; i--)
	{
        sortPrzezZliczanie(A, B, amount, i);
        pom = A;
	A = B;
	B = pom;
    }
}

void sortPrzezZliczanie(char **A, char **B, int ilosc, int pozycja){
		
	int i, j, C[RANGE]; 
        
        for (i = 0; i < RANGE; i++) 
		C[i] = 0;
		
        for (j = 0; j < ilosc; j++) {
            C[A[j][pozycja]]++;
        }
           
        for (i = 1; i < RANGE; i++)
            C[i] += C[i-1];
        
        
        for (i = ilosc - 1; i >= 0; i--) {
        	B[C[A[i][pozycja]] - 1] = A[i];
        	C[A[i][pozycja]]--;
	}

}

// quicksort

int partition (char** a, int p, int r) {

	char* x = (char*) malloc(sizeof(char)*MDN); 
	int i = p - 1, j;

	strcpy(x, a[r-1]);

	for (j = p; j < r; j++) {
			
		if (strcmp(a[j], x) <= 0) {	
			i++;
			char* temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	
		
	if (i < r) return i;
	else return i-1;
}
	
void quicksort(char** a, int p, int r) {
	if (p < r) {
	int q = partition(a, p, r);
	quicksort(a, p, q);
	//quicksort(a, q+1, r);
	}		
}	

void zapisz (char **A, int amount) {
	FILE *fp1;
	
	fp1 = fopen("./sorted.txt", "w");
     
    int i;
     
    for(i = 0; i < amount; i++) fprintf (fp1, "%s\n", A[i]);
	
	fclose (fp1);
}

int czytaj(char ** A, int amount) {
	char* slowo = malloc(sizeof(char)*MDN);
	int i, s;
    FILE *plik; 
	 
	if((plik=fopen("nazwiska.txt", "r"))==NULL) 
		printf("Nie moge otworzyc pliku!\n");
    else {
        for (i = 0; !feof(plik) && i < amount; i++) 
	{
			fscanf(plik, "%d %s",&s ,slowo);
	    	//printf("%s\n", slowo);
	    	A[i] = (char*) malloc(sizeof(char)*MDN);
	    	strcpy(A[i],slowo);
	}
		    
   		fclose(plik);
   	}
     
}
