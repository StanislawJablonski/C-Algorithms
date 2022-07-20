#include<stdio.h>
#include<stdlib.h>

//struktura drzewa z przelacznikiem
typedef struct drz{
        int liczba;
        char przel;
        struct drz* p;
        struct drz* right;
        struct drz* left;
} *drzewo;


//funkcja wstawiajaca nowy element do drzewa
void wstaw(drzewo* T, drzewo z){

        z -> left =  NULL;
        z -> right =  NULL;
        z -> przel = 'l';

        drzewo x = *T;

        drzewo y = NULL;
        
        printf("Wejscie do petli\n");
        while(x != NULL) {
                y = x;
                if(z -> liczba < x -> liczba){
                        printf("Przejscie w lewo\n");
                        x = x -> left; 
                } else if (z -> liczba > x -> liczba) {
			printf ("Przejscie w prawo\n");
			x = x -> right;
                } else {
                        if(x -> przel == 'l') {
                                printf("To samo i przejscie w lewo\n");
                                x -> przel = 'r';
                                x = x -> left;
                        } else {
                                printf("To samo i przejscie w prawo\n");
                                x -> przel = 'l';
                                x = x -> right;
                        }
               }
        }
         
        z -> p = y;

        printf("Dodanie wartosci\n\n");
        if(y == NULL) *T = z;         
	else if(z -> liczba < y -> liczba) y -> left = z;
	else if(z -> liczba > y -> liczba) y -> right = z;
	else if(z -> liczba == y -> liczba){
                if(y -> przel == 'r') y -> left = z;
                else y -> right = z;
       }
}

//funkcja odnajduje najmniejszy wezel
drzewo min(drzewo x){
        while(x -> left != NULL){
                x = x -> left;
        } return x;
}

//funkcja usuwa dany wezel z drzewa
void usun(drzewo* T, drzewo z){
        drzewo y, x;
        if(z -> left == NULL || z -> right == NULL) y = z;
        else y = min(z -> right);
         
        if(y -> left != NULL) x = y -> left;
        else x = y -> right;
         
        if(x != NULL) x -> p = y -> p;
         
        if(y -> p == NULL) *T = x;
        else {
                if(y == y -> p -> left) y -> p -> left = x;
                else y -> p -> right = x;
        }
         
        if(y != z) z -> liczba = y -> liczba;
}

//funkcja przeszukuje drzewo binarne
int szukaj(drzewo x, int k){
        while(x != NULL && k != x -> liczba){
               if(k < x -> liczba) x = x -> left;
               else x = x -> right;
        }
        if(x != NULL) return 1;
        else return 0;
}

void drukuj(drzewo x){
        if(x != NULL){
                drukuj(x -> left);
                printf("%i\n", x -> liczba);
                drukuj(x -> right);
        }
}

int main(){

        //deklaracje wezlow z elementami
	drzewo a = (drzewo)malloc(sizeof(struct drz));
	a -> liczba = 1;
	drzewo b = (drzewo)malloc(sizeof(struct drz));
	b -> liczba = 3;
	drzewo c = (drzewo)malloc(sizeof(struct drz));
	c -> liczba = 4;
	drzewo d = (drzewo)malloc(sizeof(struct drz));
	d -> liczba = 12;
	drzewo e = (drzewo)malloc(sizeof(struct drz));
	e -> liczba = 6;

	drzewo T = NULL;

	//wstawianie elementow
	wstaw(&T, a);
	wstaw(&T, b);
	wstaw(&T, c);
	wstaw(&T, d);
	wstaw(&T, e);

	//wypisanie elementow
	printf("\nElementy drzewa:\n");
	drukuj(T);

	//usuniecie jednego wezla
	printf("\nUsuwanie pierwszej wartosci");
	usun(&T, a);

	//wypisanie elementow z usunietym wezlem
	printf("\nElementy drzewa 2:\n");
	drukuj(T);

	//przeszukiwanie drzewa
	if(szukaj(T, 6)) printf("\nZnaleziono liczbe.\n");
	else printf("\nNie znaleziono liczby.\n");
         
	return 0;
}
