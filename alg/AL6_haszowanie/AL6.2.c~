#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int m = 1021;

int zerowe(int tab[]){
	int i = 0, a = 0;

	for(i = 0; i < m; i++){
		if(tab[i] == 0) a++;
	}  
	return a;
}

int max(int tab[]){
	int i, a;

	a = tab[0];

        for(i = 1; i < m; i++){
                if(tab[i] > a) a = tab[i];
        }
        return a;
}

double srednia(int tab[]){

        int i = 0,  n = 0;
        double a = 0;

        for(i = 0; i < m; i++){
                if(tab[i] != 0){
                        a = a + tab[i];
                        n = n + 1;
                }       
        }
        a = a / n;
        return a;
}

int h(char* k) { //konwersja napisu na liczbe
        int i;
        unsigned int sum = 0;
   
        for(i = 0; i < strlen(k); i++) sum = (int)k[i] + sum * 111;
        if(sum < 0) sum = sum * (-1);   

        return sum % m;
}

int main(){     

        int T[m], i = 0;
        
        for(i = 0; i < m; i++) T[i] = 0;
         
        char** tab = (char**)malloc(sizeof(char*) * m*2);
        char** hash = (char**)malloc(sizeof(char*) * m*2);

        //deklaracja zmiennych
        FILE* input = fopen("3700.txt", "r");

        if(input == NULL){
                printf("Brak pliku wejsciowego.\n");
                return 0;
       }
         
        for(i = 0; i < 2*m; i++){
                tab[i] = (char*)malloc(sizeof(char) * 20);
                fscanf(input, "%s", tab[i]);
                hash[i] = NULL;
        }
         
        fclose(input);

        for(i = 0; i < 2*m; i++){
                if(hash[h(tab[i])] != NULL) T[h(tab[i])]++; 
                hash[h(tab[i])] = tab[i];
        }
         
        printf("\nIlosc zerowych miejsc w tablicy: %i\n", zerowe(T));
        printf("Wartosc maksymalna w tablicy: %i\n", max(T));
        printf("Srednia wartosc miejsc niezerowych: %lf\n\n", srednia(T));

        return 0;
}
