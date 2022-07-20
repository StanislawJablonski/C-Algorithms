#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct wsk{
	char znak;
	int liczba;
	char kod[8];
	struct wsk* next;
	struct wsk* prev;
	struct wsk* left;
	struct wsk* right;       
} *wezel;

#define SZER_EKR 80  // szerokosc ekranu
#define IL_POZ 8   // ilosc poziomow drzewa, ktore beda wydrukowane


/*
	kod z drzew czerwono-czarnych
	wszystko to samo, ale bez wartownika

	znajduje srodek i tam drukuje kolejna liczbe
*/


//funkcje drukowania
char wydruk[IL_POZ+1][SZER_EKR];

void drukujost(wezel w, int lewy, int prawy, int poziom){
	int srodek = (lewy+prawy)/2;
	if (w==NULL) return; 
	wydruk[poziom][srodek]='*';
}

void drukujwew(wezel w, int lewy, int prawy, int poziom){
	int srodek = (lewy+prawy)/2;
	int i, dlugosc;
	char s[19];

	if (w==NULL) return;

	dlugosc=sprintf(s,"%i",w->liczba);

	for (i=0;i<dlugosc;i++)
		wydruk[poziom][srodek-dlugosc/2+i]=s[i];

	if (++poziom<IL_POZ) {
		drukujwew(w->left, lewy, srodek, poziom) ;
		drukujwew(w->right, srodek+1, prawy, poziom) ;
	} else {
		drukujost(w->left, lewy, srodek, poziom) ;
		drukujost(w->right, srodek+1, prawy, poziom) ;
	}

}

//funkcja drukujaca
void drukuj(wezel w){
	int j,i;

	for (i=0;i<=IL_POZ;i++)
		for (j=0;j<SZER_EKR;j++)
			wydruk[i][j] = ' ';

	drukujwew(w, 0, SZER_EKR, 0);

	for (i=0;i<=IL_POZ;i++) {
		for (j=0;j<SZER_EKR;j++)
			putchar(wydruk[i][j]);

		printf("\n");
	}
}

//koniec z drzew cz-cz

void insert(wezel* Q, wezel z){

	z -> next = NULL;
	z -> prev = NULL;

	if((*Q) == NULL) *Q = z; //jezeli pod najmniejszym mamy null
	else {
		wezel pom = *Q;

		while(pom != NULL){
			if(pom -> next == NULL) {
				pom -> next = z;
				z -> prev = pom;
				pom = pom -> next;
			}
			pom = pom -> next;
		}
	}
}

wezel ExtractMin(wezel* Q){

	wezel pom = *Q;
	wezel min = NULL;

	//dwie pierwsze liczby jako najmniejsze
	if(pom != NULL) {
		min = pom;
		pom = pom -> next;
	}

	//sprawdzamy, ew. szukamy dwoch najmniejszych
	while(pom != NULL) {
		if(min -> liczba >= pom -> liczba) min = pom;
		pom = pom -> next;
	}

	//warunki
	if(min -> prev == NULL && min -> next == NULL) {
		*Q = NULL;
		return min;
	} else if(min -> prev == NULL) {
		*Q = min -> next;
		(*Q) -> prev = NULL;
	} else if(min -> next == NULL && min -> prev != NULL) {
		min -> prev -> next = NULL;
		min -> prev = NULL;
	} else {
		pom = min -> prev;
		pom -> next = min -> next;
		pom -> next -> prev = pom;
	}
	return min;
}

void drukuj_kody(wezel drzewo){

	if(drzewo != NULL){
		drukuj_kody(drzewo->left);
		drukuj_kody(drzewo->right);

	if(drzewo->left == NULL && drzewo->right == NULL)
		printf("%c: %s\n", drzewo->znak, drzewo->kod);

	} else	return;

}

void wstaw_kody(wezel* korzen, char* kod){ //w lewo = 0, w prawo = 1
	if((*korzen) != NULL) {
		char s0[10];
		strcpy(s0, kod); //Funkcja kopiuje tekst z kod do s0
		strcat(s0, "0");
		wstaw_kody(&((*korzen) -> left), s0);

		char s1[10];
		strcpy(s1, kod);
		strcat(s1, "1");
		wstaw_kody(&((*korzen) -> right), s1);

		
		if((*korzen)->left == NULL && (*korzen)->right == NULL)
			strcpy((*korzen) -> kod, kod);

        } else return;
}

void caly_kod(wezel korzen, int* bity){

	if(korzen != NULL){
		caly_kod(korzen->left, bity);
		caly_kod(korzen->right, bity);

		if(korzen->left == NULL && korzen->right == NULL)
			(*bity) = (*bity) + strlen(korzen->kod)* (korzen -> liczba);

	} else return;
}

wezel HUFFMAN(char* C){

	int i = 0, ilosc_czestosci = 0;
	int liczba_znakow[127] = {};
	wezel Q = NULL;

	//liczy czestosc wystapien kazego elementu
	for (i = 0; i < strlen(C); i++)
		liczba_znakow[(int)(C[i])]++; 

	printf("\nDodane znaki:\n");

	//jezeli ascii odpowiada znakowi wypisuje gestosc
	for (i = 32; i < 127; i++){ 
		if(liczba_znakow[i] != 0){
			wezel z = (wezel)malloc(sizeof(struct wsk));

			z -> znak = (char)i;	//znak
			z -> liczba = liczba_znakow[i];	//liczba
			z -> left = NULL;
			z -> right = NULL;

			printf("%c: %i  ", z -> znak, z -> liczba);

			insert(&Q, z); //de facto tam: *Q = z (nic więcej)
			ilosc_czestosci++;
		}
	}

	printf("\n\nW tablicy znajduje sie %i roznych znakow.\n", ilosc_czestosci);

	for(i = 2; i <= ilosc_czestosci; i++) { //zaczynamy od 2 elementu

		wezel x = ExtractMin(&Q); //pierwszy najmniejszy element
		wezel y = ExtractMin(&Q); //drugi -||-
		wezel z = (wezel)malloc(sizeof(struct wsk));     

		z -> left = x;
		z -> right = y;

		z -> liczba = x -> liczba + y -> liczba; //nowy wezel (suma)

		insert(&Q, z);
	}
	return ExtractMin(&Q);
}

void znajdz_kod(wezel korzen, char znak, char* kod){

	if(korzen != NULL) {
		znajdz_kod(korzen->left, znak, kod);
		znajdz_kod(korzen->right, znak, kod);

		if(znak == korzen -> znak) strcpy(kod, korzen -> kod);
        } else return;
}

void decode (wezel korzen, char* D, int lenth) {	
	int i, d;
	printf("Odczytany tekst: ");
	for (i = 0; i < lenth; i++) printf("%c", D[i]);

	printf("\nOdkodowany tekst: ");

	wezel pom = korzen;

	for (i = 0; i < lenth; i++) {
		if (D[i] == '0') korzen = korzen -> left;
		else korzen = korzen -> right;

		if (korzen->left == NULL && korzen -> right == NULL) {
			printf("%c", korzen -> znak);
			korzen = pom;
		}
	}
	printf("\n");
}

int main(){

	FILE* plik_In = fopen("napisyhuffmana.txt", "r");

	int i, max, suma;
	char C[200]; //na tekst
	char D[200]; //na odkodowanie

	//odczytywanie pliku
	for(i = 0; fscanf(plik_In, "%c", &C[i]) != EOF; i++);

	C[i]='\0';
	fclose(plik_In);

	int bit_1 = i*3; //wczytane bity

	wezel drzewo = HUFFMAN(C);

	printf("\nDrzewo:\n\n");
	drukuj(drzewo); //drukujemy drzewo

	wstaw_kody(&drzewo, "");

	printf("Kody znakow:\n\n");
	drukuj_kody(drzewo);

	int bit_2 = 0; //bity skompresowanego tekstu
	caly_kod(drzewo, &bit_2);

	printf("\nWczytany tekst ma dlugosc %i bitow.\n", bit_1);
	printf("Skompresowany tekst ma dlugosc %i bitow.\n\n", bit_2);

	FILE* plik_Out = fopen("huffmanoutput.txt", "w");

	for(i = 0; i < (int)strlen(C); i++){
		char kod[8];
		znajdz_kod(drzewo, C[i-1], kod);
		fprintf(plik_Out, "%s", kod);
	}

	fclose(plik_Out);
	
	for (i=0; i<200; i++) D[i]='0';


	FILE* plik_Out2 = fopen("huffmanoutput.txt", "r");
	for(i = 0; fscanf(plik_Out2, "%c", &D[i]) != EOF; i++); 
	

/*	
	max=i;
	//decode(drzewo, D, max);

	//printf("%i\n", max);

	suma=max/8;
	suma=suma*8;
	if (suma<max) suma=suma+8;
	

	//printf("%i\n", suma);
	for (i=0; i<suma; i++) printf("%c", D[i]);
	printf("\n");

	//for (i=0; i<suma; i=i+8)
*/

	decode(drzewo, D, i);

	fclose(plik_Out2);

	return 0;
}
