#include<stdio.h>
#include<stdlib.h>

typedef struct wz{

        int klucz; //klucz zwiazany z elementem x
        int rank; // ranga drzewa czyli oszacowanie wysokosci, okreslone tylko dla korzenia
        struct wz* p; //wskaznik do ojca, korzen wskazuje sam siebie
 
} *wezel;

wezel MakeSet(int k){

	//utworzenie zbioru reprezentujacego jednoelementowy zbior
	//z kluczem k
        wezel x = (wezel)malloc(sizeof(struct wz));
        x->klucz = k;
        x->rank=0;
        x->p = x;

        return x;
}

wezel FindSet(wezel x){
	//zwrca reprezentanta zbioru do ktorego nalezy element x
	//z kompresja

        if(x != x->p){
                x->p = FindSet(x->p);
        }
         
        return x->p;
}

void Union(wezel x, wezel y){
	//zamienia zbiory o reprezentantach x, y, w jeden zbior bedacy ich suma rozlaczna
	//z ranga

        if(x->rank > y->rank){
                y->p = x;
        } else {
                x->p = y;
                if(x->rank == y->rank){
                        y->rank = y->rank+1;
                }
        }
}

int indeks = 1;

void dodaj_wezel(int k, wezel* Z){

        Z[indeks] = MakeSet(k);
        indeks++;

}

void dodaj_krawedz(int A, int B, wezel* Z){
        Union(FindSet(Z[A]), FindSet(Z[B]));
}

int main(){

        int i = 0;
        wezel Z[20];
        Z[0] = MakeSet(0);

        //dodanie wierzcholka
        for(i=1;i<20;i++){
                dodaj_wezel(i, Z);
        }
         
	//na sztywno 0-20
        printf("\nDodane elementy:\n");
        for(i=1;i<=9;i++){
                printf("%i ", Z[i]->klucz);
        }
         
        printf("\n");

        //dodanie krawedzi
        dodaj_krawedz(1, 2, Z);
        dodaj_krawedz(3, 5, Z);
        dodaj_krawedz(2, 4, Z);
        dodaj_krawedz(4, 6, Z);
        dodaj_krawedz(8, 7, Z);
        dodaj_krawedz(7, 4, Z);
        dodaj_krawedz(3, 8, Z);

        printf("\n");

        //sprawdzenie, czy dwa wierzcholki sa w tej samej skladowej spojnosci grafu
        if(FindSet(Z[1]) == FindSet(Z[2])){
                printf("Oba wierzcholki sa w tej samej skladowej spojnosci grafu.\n");
        } else {
                printf("Wierzcholki NIE sa w tej samej skladowej spojnosci grafu.\n");

        }

        printf("\n");

        return 0;
}

 
