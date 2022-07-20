#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int m = 10;

typedef struct{
	int ilosc;
	char nazwisko[20];
} nazwiska;

int h(char* k) { //konwersja napisu na liczbe
	int i, sum = 0;
   
	for(i = 0; i < strlen(k); i++) sum = (int)k[i] + sum * 111;
	if(sum < 0) sum = sum * (-1);

	return sum % m;
}

int H(char* k, int i){	//adresowanie otwarte dwukrotne
	//H(k,i) = (h(k) + i * h'(k)) mod m	<-	h'(k) = 1 + k%(m-2)
	return ( h(k) + i*( strlen(k)%(m-2)+1 ) ) % m;	//co to k? strlen(k) czy k[i] ??
}

//funkcja wstaw
void wstaw(nazwiska* tab, nazwiska* hash, int* T){
	int i = 0, j = 0;

	for(j = 0; j < (m * 8)/10; j++){
		i = 0;
		while(strcmp(hash[H(tab[j].nazwisko, i)].nazwisko, " ") != 0){
			if(i > m){
				printf("Metoda zawiodla.\n");
				exit(1);
			} else {
				T[j]++;
				i++;
			}
		} hash[H(tab[j].nazwisko, i)] = tab[j];
	}
}

double srednia(int T[]){

	int i = 0, n = 0;
	double a = 0;

	for(i = 0; i < m; i++){
		a = a + T[i];
		n = n + 1;
	}
         
	a = a / n;

	return a;
}

int main(){

	FILE* input = fopen("nazwiskaASCII.txt", "r");
	int i = 0;
	char c = 'a';
         
	//liczenie liczb/wierszy
	while(fscanf(input, "%c", &c) != EOF){
		if(c == '\n') i++;
	}
        
	fclose(input);
        
	m = i;
	int T[m];

	for(i = 0; i < m; i++) T[i] = 0;
         
	nazwiska tab[m], hash[m];

	input = fopen("nazwiskaASCII.txt", "r");

	for(i = 0; i < m ; i++){
		fscanf(input, "%i", &tab[i].ilosc);
		//tab[i].nazwisko = (char*)malloc(sizeof(char) * 20);
		fscanf(input, "%s", tab[i].nazwisko);
	}

	fclose(input);

	for(i = 0; i < m; i++){
		hash[i].ilosc = 0;
		strcpy(hash[i].nazwisko, " ");
	}
        
	wstaw(tab, hash, T);
	printf("\nSrednia ilosc prob: %lf\n\n", srednia(T));
         
	return 0;
}
