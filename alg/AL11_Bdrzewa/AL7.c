#include <stdio.h>
#include <stdlib.h>
#define t 3 //stopien

typedef struct wz{
	char lisc;
	int n; //ilosc kluczy (-1 oznacza wezel usuniety)
	int c[2*t]; // wskazniki do synow (pozycje w pliku: 0,1,2 ...)
	int klucz[2*t-1]; // klucze
	int nr_w_pliku;
} wezel;

typedef struct{
	wezel *root;
} Tree;

int rozmiarw = sizeof(wezel); // rozmiar wezla w bajtach
FILE *plik; // plik drzewa (zawierajacy wezly)
int pozycja = 0;


// z pmp

void zapisz(int i, wezel *w){
	// zapisuje *w jako i-ty zapis w pliku drzewa
	fseek(plik,(long)i*rozmiarw,SEEK_SET);
	fwrite(w,rozmiarw,1,plik);
	//  printf("z%d ",i);
}

void odczytaj(int i, wezel *w){
	// odczytuje i-ty zapis w pliku drzewa i wpisuje do *w
	fseek(plik,(long)i*rozmiarw,SEEK_SET);
	fread(w,rozmiarw,1,plik);
	//  printf("o%d ",i);
}

//koniec


void split(wezel* x, int i, wezel* y){ //nowy korzen, 0, drzewo

	wezel z;
	z.lisc = y->lisc;
	z.n = t - 1; //ilosc kluczy
	int j = 0;

	//printf("Wchodze do splita dla i = %i\n", i);
	for(j = 0; j < t - 1; j++){
		printf("Wchodze do pierwszej petli.\n");
		z.klucz[j] = y->klucz[j + t];
	}

	if(y->lisc == 'f'){
		printf("Wezel nie jest lisciem w splicie.\n");

		for(j=0;j < t;j++){
			//printf("Wchodze do petli gdy wezel nie jest lisciem.\n");
			z.c[j] = y->c[j + t];
		}

	}

	y->n = t-1;

	for(j=x->n; j>=i+1; j--){
		printf("Wchodze do drugiej petli.\n");
		x->c[j+1] = x->c[j];
	}

	z.nr_w_pliku = ++pozycja;
	x->c[i+1] = z.nr_w_pliku;

	for(j=x->n - 1; j>=i; j--){
		printf("Wchodze do trzeciej petli.\n");
		x->klucz[j+1] = x->klucz[j];
	}

	x->klucz[i] = y->klucz[t - 1];
	x->n++;

	printf("Zapisuje trzy elementy.\n"); //l m r
	zapisz(y->nr_w_pliku, y);
	zapisz(z.nr_w_pliku, &z);
	zapisz(x->nr_w_pliku, x);
}

void insert_nonfull(wezel *x, int k){ //korzen, wartosc do dodania
	printf("Wchodze do nonfulla by dodac %i\n", k);
	int i = x -> n-1;

	if(x->lisc == 't'){
		printf("Wezel jest lisciem.\n");

		while(i>=0 && k < x->klucz[i]){
			x->klucz[i+1] = x->klucz[i];
			i--;
		}

		printf("Dodanie wartosci do wezla.\n");
		x->klucz[i+1] = k;
		printf("Nowy klucz to %i\n", x->klucz[i+1]);
		x->n++;
		zapisz(x->nr_w_pliku, x);

	} else {

		printf("Wezel nie jest lisciem w nonfullu.\n");
		while(i >= 0 && k < x->klucz[i]){
			i--;
		}
		i++;

		wezel a;
		odczytaj(x->c[i], &a);

		if(a.n == 2*t-1){
			printf("Liczba elementow w x->c[i] wynosi %i.\n", a.n);
			split(x, i, &a);

                        if(k > x->klucz[i]){
                                //printf("Wstawiane %i jest wieksze od %i.\n", k, x->klucz[i]);
                                i++;
                                odczytaj(x->c[i], &a);
                        }
		}

		//printf("Rekursja\n");
		insert_nonfull(&a, k);
	}
}

//wstaw -> k
void insert(Tree *drzewo, int k){

	printf("\nWchodze do inserta by dodac %i\n", k);
	wezel *T = drzewo->root;

	if(T->n == 2*t-1){

		printf("Wezel jest przepelniony.\n");

		wezel *s = (wezel*)malloc(sizeof(wezel)); //nowy wezel

		s->n = 0; //ilosc kluczy
		s->lisc = 'f';
		s->c[0] = T->nr_w_pliku;
		pozycja++;
		s->nr_w_pliku = pozycja;

		drzewo->root = s; //nowy korzen
		split(s, 0, T);
		insert_nonfull(s, k);
		//free(T);
        } else {
		printf("W wezle jest miejsce.\n");
		insert_nonfull(T, k);
	}
}

int search(wezel* x, int k){
	int i = 0;

	while(i < x->n && k > x->klucz[i]){
		i++;
		printf("%d\n",i);
	}
	if(i < x->n && k==x->klucz[i]) return 1;

	if(x->lisc =='t') return 0;
	else{
		wezel a;
		odczytaj(x->c[i], &a);
		return search(&a, k);
	}
}

int rekDrukujBDot(int r, int z, FILE *plikwy){
	// pomocnicza funkcja dla drukujBDot()
	// drukuje B-drzewo o korzeniu r (pozycja w pliku)
	// z  - numer wezla
	// zwraca najwiekszy numer wezla w poddrzewie, ktorego jest korzeniem
	//d [shape=box, width=5.0,length=3, height=0.3]

	wezel w;
	int i = 0;
	odczytaj(r, &w);
	fprintf(plikwy,"%i [shape=box, label=\"",z);
	for (i = 0; i < w.n; i++){
		fprintf(plikwy,"%i ",w.klucz[i]);
		printf("Wpisuje %i\n", w.klucz[i]);
	}

	fprintf(plikwy,"\"]\n");
	int nz=z;

	if (w.lisc == 'f'){
		printf("Nie jest lisciem.\n");

		for(i = 0;i <= w.n;i++){
			fprintf(plikwy,"%i -- %i ;\n",z,nz+1);
			nz=rekDrukujBDot(w.c[i],nz+1,plikwy);
		}
	}

	return nz;
}

void drukujBDot(int root){
	// przygotowuje wydruk graficzny B-drzewa o korzeniu r (pozycja w pliku)
	// tworzy plik bdrzewo.gv z danymi dla programu dot
	// instrukcja    dot -Tpdf -o bdrzewo.pdf bdrzewo.gv
	// utworzy plik bdrzewo.pdf z graficzna reprezentacja drzewa

	FILE *plikwy;
	printf("\nDrukowanie do pliku.\n");
	plikwy=fopen("bdrzewo.gv","w");
	fprintf(plikwy, "graph bdrzewo{\n");
	fprintf(plikwy, "size = \"10,20\"");
	rekDrukujBDot(root,0,plikwy);
	fprintf(plikwy, "}\n");
	fclose(plikwy);
	printf("\nUtworzony plik bdrzewo.gv\n\n");
}

int main(){

	plik = fopen("binarne","w+");

	//wstawianie na sztywno
	Tree drzewo;

	wezel T;
	T.n = 0; //ilosc kluczy = 0
	T.lisc='t'; //tak - lisc
	T.nr_w_pliku = 0;
	drzewo.root = &T;

	int i = 0;

	//wstawiamy liczby 9-0
	//int Proba[10]={1,6,3,2,6,3,2,5,7,99};
	for(i = 18; i >= 1; i--)
		insert(&drzewo, i);

       //do pliku .gv
	drukujBDot(drzewo.root->nr_w_pliku);

	//szukanie
	int szukana=7;
	if(search(drzewo.root, szukana)){
		printf("Znaleziono %d.\n",szukana);
	} else {
		printf("Nie znaleziono %d.\n",szukana);
	}

	fclose(plik);
	return 0;
}
