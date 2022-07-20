#include<stdio.h>
#define PLIK "liczby.txt"
#define PLIKK "wyjscie.txt"

void Heapify(int A[], int i) {
	int l, r, n, largest;
 
	for(l=1; l<i; l++) {
		largest = A[l];
		r = l;
		n = (r-1)/2;
 	
		while((r>0) && (largest>A[n])) {
			A[r] = A[n];
			r = n;
			n = (r-1)/2;
		}
	A[r] = largest;
	}
}
 
void BuildHeap (int A[], int i) {
	int r, l, largest;
 
	l = 0;
	largest = A[l];
	r = 2*l+1;
 
	while(r <= i-1) {
		if(r+1 <= i-1)
			if(A[r] < A[r+1]) r++;
		if(largest < A[r]) {
			A[l] = A[r];
			l = r;
			r = 2*l+1;
		} else
			break;
	}
	A[l] = largest;
}

void Heapsort(int A[], int i) {
	int n,t;
 
	Heapify(A,i);
 
	for(n=i-1; n>0; n--) {
		t = A[0];
		A[0] = A[n];
		A[n] = t;
		BuildHeap(A,n);
	}
}
 
int main() {
	int i, n, k, A[50];
 
	FILE *plik;
	FILE *wyjscie;

	plik = fopen(PLIK, "r");

	for (k=0; k<=10; k++) {
		fscanf(plik, "%d", &i);
		A[k]=i;
		if (A[k] == A[k-1]) break;
		printf("%d ", A[k]);
	}
	fclose(plik);
	i=k;
 
	Heapsort(A,i);
	wyjscie = fopen(PLIKK, "w");

	printf("\nPosortowane elementy: \n");

	for(n=0; n<i; n++) {
		printf("\t%d", A[n]);
		fprintf(wyjscie, "%d\n", A[n]);
	}

	fclose(wyjscie);
	printf("\n"); 
}

