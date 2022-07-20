#include<stdio.h>

void wyznacz_lcs(int X[], int Y[], int warX, int warY, int tab[][warY+1], char trasa[][warY+1]){

	int i, j;

	for(i = 0; i <= warX; i++) tab[i][0] = 0; //uzupelaniamy zerami
	for(j = 0; j <= warY; j++) tab[0][j] = 0; 

	for(j = 1; j <= warY; j++){
		for(i = 1; i <= warX; i++){
			if (X[i - 1] == Y[j - 1]) {
				//dla tych samych wartosci +1 i oznaczenie "\"
				tab[i][j] = tab[i-1][j-1]+1;
				trasa[i][j] = '\\';
			} else if(tab[i-1][j] >= tab[i][j-1]) { 
				//bierzemy wartosc z boku
				tab[i][j] = tab[i-1][j]; 
				trasa[i][j] = '|';
			} else {
				//bierzemy wartosc z gory
				tab[i][j] = tab[i][j-1]; 
				trasa[i][j] = '-';
			}
		} 
	}
  
	//tabela
	printf("\n");
	for(i = 0; i <= warX; i++){
		//i - szer, uzupelniamy liczbami
		if(i == 0) printf("    ");
		else printf("%i ", X[i - 1]);        
	}
	printf("\n");

	for(j = 0; j <= warY; j++){
		//j - wys, uzupelniamy liczbami
		if(j == 0) printf("  ");
		else printf("%i ", Y[j - 1]);

		//drukowanie uzupelnionej tablicy
		for(i = 0; i <= warX; i++) printf("%i ", tab[i][j]); 
		printf("\n");

        }


}

void print_lcs(int X[], int Y[], int i, int j, char trasa[][6]){

	if(i == 0 || j == 0) return; 	//koniec taki

	//gdzie idziemy i znow funkcja
	if(trasa[i][j] == '\\'){	
		print_lcs(X, Y, i-1, j-1, trasa);
		printf("%i ", X[i-1]); //drukujemy sobie liczbe
	} else if (trasa[i][j] == '|') print_lcs(X, Y, i - 1, j, trasa);
	else print_lcs(X, Y, i, j - 1, trasa);
}

int main(){
        
	int X[] = {1,0,1,1,0};
	int Y[] = {0,0,1,0,1};

	int warX = 5;
	int warY = 5;

	int tab[warX+1][warY+1];
	char trasa[warX+1][warY+1];

	wyznacz_lcs(X, Y, warX, warY, tab, trasa);
	printf("\nNajdluzszy wspolny podciag: ");
	print_lcs(X, Y, warX, warY, trasa);

	printf("\n\n");

	return 0;
}
