#include<stdio.h>

/*
	Adj(u) 		to zbiór wierzchołków, do których jest krawędź z wierzchołka u
	u.kolor 	to kolor wierzchołka: BIAŁY lub SZARY
	u.pi 		to taki wierzchołek v, że dotarliśmy do u krawędzią(v,u). 
		Takie krawędzie tworzą drzewo (lub las drzew) spinające przeszukiwany graf. 
		Korzeń (korzenie) tego drzewa (lasu) to te wierzchołki u dla których u.pi == NIL
*/ 

int n;

struct wsk{
        char kolor;
        int pi;
}* wezel;

void DFS2(int i, struct wsk u[], int matrix[][n]){	//matrix - graf	
	// przeszukujemy graf w głąb rozpoczynając od wierzchołka startowego u
	// wierzchołki już odwiedzone mają kolor SZARY

        u[i].kolor = 's'; //szary
        int j = 0;
        for(j = 0; j < n; j++){				//dla każdego v należącego do Adj(u)
                if(matrix[i][j] == 1){
                        if(u[j].kolor == 'b'){		//if v.kolor==BIAŁY
                                u[j].pi = i;		//v.pi=u
                        }
                }
        }
}

void DFS1(struct wsk u[], int matrix[][n]){ //matrix - graf

        int i = 0;   
   
        for(i = 0; i < n; i++){			//dla każdego wierzchołka u
                u[i].kolor = 'b';			//u.kolor=BIAŁY
                u[i].pi = -1;			//u.pi=NIL
        }

        for(i = 0; i < n; i++){			//dla każdego wierzchołka u
                if(u[i].kolor == 'b'){		//if u.kolor==BIAŁY
                        DFS2(i, u, matrix);
                }
        }
}

int main(){

        FILE* plik = fopen("graf.txt", "r");
        n = 0;
        fscanf(plik, "%i", &n);
        printf("\nIlosc wezlow: %i\n", n);

        int matrix[n][n];
        int i = 0, j = 0;

        printf("\nMacierz sasiedztwa:\n");

        for(i = 0; i < n; i++){
                for(j = 0; j < n; j++){
                        fscanf(plik, "%i", &matrix[i][j]);
                        printf("%i ", matrix[i][j]);
                } printf("\n");
        }
         
        fclose(plik);
        printf("\n");

        struct wsk tab[n];

        DFS1(tab, matrix);

        printf("Output:\n");
        for(i = 0; i < n; i++){
                printf("%i", i+1);
                printf(" %i\n", tab[i].pi+1);
        }
         
        return 0;
}

