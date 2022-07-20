#include<stdio.h>
#include<stdlib.h>

#define SZER_EKR 80  /* szerokosc ekranu */
#define IL_POZ 8   /* ilosc poziomow drzewa, ktore beda wydrukowane   */

//struktura drzewa binarnego
typedef struct wsk{
	int liczba;
	char kolor;
	struct wsk* parent;
	struct wsk* left;
	struct wsk* right;
} *wezel;

//funkcje drukowania
char wydruk[IL_POZ+1][SZER_EKR];

void drukujost(wezel w, int lewy, int prawy, int poziom, wezel war){
	int srodek = (lewy+prawy)/2;
	if (w==war) return; 

	wydruk[poziom][srodek]='*';
}

void drukujwew(wezel w, int lewy, int prawy, int poziom, wezel war){
	int srodek = (lewy+prawy)/2;
	int i, dl;
	char s[19];
	if (w==war) return;
	if (w->kolor=='b') dl=sprintf(s,"%i", w->liczba);
	else dl=sprintf(s,"%+i", w->liczba);

	for (i=0;i<dl;i++) wydruk[poziom][srodek-dl/2+i]=s[i];
	if (++poziom<IL_POZ){
		drukujwew(w->left, lewy, srodek, poziom, war) ;
		drukujwew(w->right, srodek+1, prawy, poziom, war) ;
	} else {
		drukujost(w->left, lewy, srodek, poziom, war) ;
		drukujost(w->right, srodek+1, prawy,poziom, war) ;
	}
}

//funkcja drukujaca
void drukuj(wezel w, wezel war){
	int j,i;
	for (i=0;i<=IL_POZ;i++)
		for (j=0;j<SZER_EKR;j++) wydruk[i][j] = ' ';
	drukujwew(w,0,SZER_EKR,0, war);

	for (i=0;i<=IL_POZ;i++){
		for (j=0;j<SZER_EKR;j++) putchar(wydruk[i][j]);
	printf("\n");
  }
}

//obrot w lewo
void left_rotate(wezel *korzen, wezel x, wezel war){

	wezel y = x -> right;
	x -> right = y -> left;

	if(y -> left != war) y -> left -> parent = x;
         
	y -> parent = x -> parent;
         
	if(x -> parent == war) *korzen = y;
	else if(x == x -> parent -> left) x -> parent -> left = y;
	else x -> parent -> right = y;
         
	y -> left = x; 
	x -> parent = y;
}


//obrot w prawo
void right_rotate(wezel *korzen, wezel x, wezel war){
         
	wezel y = x -> left;
	x -> left = y -> right;

	if(y -> right != war) y -> right -> parent = x;  
         
	y -> parent = x -> parent;

	if(x -> parent == war) *korzen = y;
	else if(x == x -> parent -> right) x -> parent -> right = y;
	else x -> parent -> left = y;

	y -> right = x; 
	x -> parent = y;
}
 
//wstawianie binarne
void wstaw_binarne(wezel* korzen, wezel z, wezel war){
         
        wezel x = (*korzen);
        wezel y = war;
        
        //przechodzenie
        while(x != war){
		y = x;
		if(z -> liczba < x -> liczba) x = x -> left;
		else x = x -> right;
        }
         
        z -> parent = y;

        //dodanie wartosci
        if(y == war) *korzen = z;
        else if(z -> liczba < y -> liczba) y -> left = z;
        else y -> right = z;
}

//wstawianie do drzewa czerwono czarnego
void wstawRB(wezel* korzen, int k, wezel war){

	wezel z = (wezel)malloc(sizeof(struct wsk));
	z -> liczba = k; //wstawiana wartosc
	z -> left = war;
	z -> right = war;
	z -> kolor = 'r';

	printf("Dodawanie liczby: %i\n", z -> liczba);
	wstaw_binarne(korzen, z, war);

	while(z -> parent -> kolor == 'r' && z != *korzen) {
		if(z -> parent == z -> parent -> parent -> left){
			wezel y = z -> parent -> parent -> right;

			if(y -> kolor == 'r'){
				z -> parent -> kolor = 'b';
				y -> kolor = 'b';
				z -> parent -> parent -> kolor = 'r';
				z = z -> parent -> parent;
			} else {
				if(z == z -> parent -> right){
					z = z -> parent;
					left_rotate(korzen, z, war);
				}                                 
				z -> parent -> kolor = 'b';
				z -> parent -> parent -> kolor = 'r';
				right_rotate(korzen, z -> parent -> parent, war);
			}
		} else {

			wezel y = z -> parent -> parent -> left;

			if(y -> kolor == 'r'){
				z -> parent -> kolor = 'b';
				y -> kolor = 'b';
				z -> parent -> parent -> kolor = 'r';
				z = z -> parent -> parent;
			} else {
				if(z == z -> parent -> left){
					z = z -> parent;
					right_rotate(korzen, z, war);                      
				}
				z -> parent -> kolor = 'b';
				z -> parent -> parent -> kolor = 'r';
				left_rotate(korzen, z -> parent -> parent, war);
			}
		}
	}
	(*korzen) -> kolor = 'b';
	drukuj(*korzen, war);
}

//maksymalna glebokosc drzewa
int max_glebokosc(wezel T, wezel war){
	if (T == war) return 0;
	else {
		int lgleb = max_glebokosc(T -> left, war);
		int rgleb = max_glebokosc(T -> right, war);
 
		if (lgleb > rgleb) return lgleb+1;
		else return rgleb+1;

	}
}

 
//minimalna glebokosc drzewa
int min_glebokosc(wezel T, wezel war){
	if (T == war) return 0;
	else {
		int lgleb = min_glebokosc(T -> left, war);
		int rgleb = min_glebokosc(T -> right, war);
 
		if (lgleb < rgleb) return lgleb + 1;
		else return rgleb + 1;
  	}
} 

//funkcja szukajaca czerwonych elementow
int szukaj_czerw(wezel T, wezel war){
        int a = 0;
        if(T != war){
                a = a + szukaj_czerw(T -> left, war);
                if(T -> kolor == 'r') a = a + 1;
                a = a + szukaj_czerw(T -> right, war);
        }
        return a;
}

int max(int a, int b){
	if(a > b) return a; else return b;
}

//funkcja zliczajaca czerwone elementy na sciezce
int il_czerw(wezel T, wezel war, int *liczba){

	//zmienne pomocnicze
	int left_num = 0, right_num = 0;
	int left_il = 0, right_il = 0;

	//jesli doszlismy do konca to zwraca 0
	if (T == war) return 0;
         
	//rekursja dla lewej i prawej galezi
	left_il = il_czerw(T -> left, war, &left_num);
	right_il = il_czerw(T -> right, war, &right_num);

	//czy element jest czerwony
	int a = 0;
	if(T -> kolor == 'r') a = 1;
         
	//zapamietuje liczbe czerwonych elementow na sciezce
	(*liczba) = max(left_num, right_num) + a;

	//na ktorej galezi jest wiecej czerwonych elementow
	int temp = max(left_il, right_il);

	//zwracam ilosc czerwonych elementow
	return max(temp, left_num + right_num);
}

int main(){

	//deklaracja wartownika
	wezel war = (wezel)malloc(sizeof(struct wsk));
	war -> kolor = 'b';
	war -> left = war;
	war -> right = war;

	//deklaracja korzenia
	wezel korzen = (wezel)malloc(sizeof(struct wsk));
	korzen = war;
	korzen -> parent = war;

	//wstawianie elementow
	wstawRB(&korzen, 12, war);
	wstawRB(&korzen, 10, war);
	wstawRB(&korzen, 8, war);
	wstawRB(&korzen, 15, war);
	wstawRB(&korzen, 17, war);
	wstawRB(&korzen, 32, war);
	wstawRB(&korzen, 34, war);
	wstawRB(&korzen, 4, war);
	wstawRB(&korzen, 5, war);
	wstawRB(&korzen, 22, war);
	wstawRB(&korzen, 13, war);
	wstawRB(&korzen, 3, war);
	wstawRB(&korzen, 7, war);
	wstawRB(&korzen, 34, war);
	wstawRB(&korzen, 23, war);
	int a = 0;
	printf("Maksymalna glebokosc drzewa: %i.\n", max_glebokosc(korzen, war));
	printf("Minimalna glebokosc drzewa: %i.\n", min_glebokosc(korzen, war));
	printf("Liczba czerwonych wezlow z drzewie %i.\n", szukaj_czerw(korzen, war));
	printf("Liczba czerwonych wezlow w sciezce: %i.\n", il_czerw(korzen, war, &a));
        
	return 0;
}
