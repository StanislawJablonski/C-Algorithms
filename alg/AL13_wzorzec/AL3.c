#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MLD 1000000000.0 

	// P - wzorzec, tablica [1..m],
	// T - tekst, tablica [1..n],

void naiwny(char* P, char* T) { 

        int i = 0, j = 0, n = strlen(T), m = strlen(P);

        for(i = 0; i <= n - m; i++){ //  tu porównujemy m znaków (w pętli)
                for(j = 0; j < m; j++){
                        if(P[j] != T[i+j]) j = m; //jesli znajdzie takie same podciagi idzie do if-a
                }
                 
                if(j == strlen(P)){
                        printf("Wystapienie na pozycji: %i.\n", i);
                }
        }
}

void rabinkarp(char* P, char* T){ //wykorzystuje funkcje haszujaca

	// d - rozmiar alfabetu (np. 128)
	// q - liczba pierwsza (np. 27077)

        int n = strlen(T), m = strlen(P);
        int p = 0, t = 0, i = 0, j = 0, q = 27077, h = 1, d = 128;

        for (i = 0; i < m-1; i++){
                h = (h*d)%q;	// wyliczy h = (d do potęgi m-1) modulo q
        }

        for (i = 0; i < m; i++){
	//wartość p "kodująca" P[1..m]
	//wartość t "kodująca" T[s+1..s+m] dla s==0
	//kodowanie niejednoznaczne - haszowanie	
                p = (d*p + P[i])%q;
                t = (d*t + T[i])%q;
        }

        for (i = 0; i <= n - m; i++){
                if(p == t){		//tu porównujemy m znaków (w petli)
                        for (j = 0; j < m; j++){
                                if (T[i+j] != P[j]) j=m;
                        }

                        if(j == m) printf("Wystapienie na pozycji (Rabin-Karp): %i\n", i);    
                }

                //czy tekst sie nie skonczyl?
                if (i < n-m){
                        t = (d*(t - T[i]*h) + T[i+m])%q;
				// czyli t = (d*(t-T[s+1]*h)+T[s+1+m])%q, gdzie arytmetyka jest
				// modulo q (mnozenie i odejmowanie)
				// to wylicza wartość t "kodująca" T[s+2, ... , s+m,s+1+m]
				// na podstawie wartosci t "kodujacej" T[s+1,s+2, ... , s+m
                        if(t < 0) t = (t + q);                  
                }
        }
}

void prefix(char *P, int* pi) {
   
	pi[0] = 0;
	int t = 0, i = 0;;
	int m = strlen(P);
   
	for(i = 1; i < m; i++) {
		while(t > 0 && P[t + 1] != P[i]){
			t = pi[t];
		}

		if(P[t + 1] == P[i]) {
			t++;
			pi[i] = t;
		}
	} 
}


void kmp(char *P, char *T) { //
	// P - wzorzec, tablica [1..m],
	// T- tekst, tablica [1..n],

        int tab[strlen(P)];
        prefix(P, tab); //(wzorzec, strlen(wzorzec)
        int i = 0, j = 0;

        int m = strlen(T);
        int n = strlen(P);

        while(i < m - n + 1){
                j = 0;
                while(P[j] == T[i + j] && P[j] != '\0'){
                        j++;
                } 

                if(j == n) printf("Wystapienie na pozycji (KMP): %i \n", i);

                if((j - tab[j]) > 1) i = i + j-tab[j];
                else i++;
        }
}

int main () {

//        char* napis = "sgfdsgdfgdsghdfsgdsgdfshahahagfdfhogfhkogfhkofghkhahahagpdfgdgfohhahahafgggg";
//        char* wzorzec = "hahaha";
/*	naiwny(wzorzec, napis);
        printf("\n");
	rabinkarp(wzorzec, napis);
	printf("\n");
	kmp(wzorzec, napis);
	printf("\n");
*/
	int n = 0, i = 0, m = 0;
	char c;

//-------------------------------------------------------
	FILE* napis = fopen("tekst.txt", "r");
	while(fscanf(napis, "%c", &c) != EOF) n++;	//n -> dlugosc tekst.txt
        fclose(napis);

	char* napis2 = (char *)malloc(sizeof(char)* n);
	napis = fopen("tekst.txt", "r");
        for(i = 0; i < n; i++){
                fscanf(napis, "%c", &napis2[i]);
        }
//-------------------------------------------------------
	FILE* wzorzec = fopen("wzorzec.txt", "r");;
	while(fscanf(wzorzec, "%c", &c) != EOF) m++;	//m -> dlugosc wzorzec.txt
        fclose(wzorzec);

        char* wzorzec2 = (char*)malloc(sizeof(char)* m);
        wzorzec = fopen("wzorzec.txt", "r");
        for(i = 0; i < m; i++){
                fscanf(wzorzec, "%c", &wzorzec2[i]);
        }
//-------------------------------------------------------
        struct timespec tp0, tp1;
        double Tn;

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
        naiwny(wzorzec2, napis2);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
        Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
        printf("\nNaiwny: %3.5lf sekund.\n\n", Tn);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
        rabinkarp(wzorzec2, napis2);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
        Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
        printf("\nRabin-Karp: %3.5lf sekund.\n\n", Tn);
 
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
        kmp(wzorzec2, napis2);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
        Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
        printf("\nKMP: %3.5lf sekund.\n\n", Tn);

        return 0;
}
