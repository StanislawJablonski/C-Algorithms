#include <stdio.h>
#include <stdlib.h>

struct rekord{
	int x;
	int y;
	int liczba;

	struct rekord *next, *prev;
};

struct rekord *first;
struct rekord *last;


int wstawRekord(){

	struct rekord *nowy;
	nowy = (struct rekord *)(malloc(sizeof(struct rekord)));

	printf("\tpodaj x: ");
	scanf("%i", &nowy->x);

	printf("\tpodaj y: ");
	scanf("%i", &nowy->y);

	if(first != null) {
		first->prev = nowy;
		nowy->next = first;
	} first = nowy;
}


void wyswietlListe() {
	struct rekord *temp = first;
	printf("\tLista: ");
	while(temp != null){
		printf(" (%i, %i) ", temp->x, temp->y);
		temp=temp->next;
	}
	printf("\n");
}


struct rekord * znajdzPoprzedni;

struct rekord * znajdzRekord(int x, int y) {
	struct rekord *curr = first;
	while (curr != null) {
		if ((curr->x == x) && (curr->y == y)) {
			printf("\tZnaleziono punkt (%i, %i)\n", curr->x, curr->y);
			return curr;
		}
	znajdzPoprzedni=curr;
	curr = curr->next;
	if (curr == null) printf("\tNie znaleziono punktu (%i, %i)\n", x, y);
	} return 0;
}

void usunRekord(int x, int y){
	struct rekord *toDel = null;
	toDel = znajdzRekord(x, y);

	if (toDel != null) {
		printf("\tUsunięto punkt (%i, %i)\n", x, y);

		if (toDel == first) first = toDel ->next;
		else znajdzPoprzedni->next = toDel->next;

	free(toDel);
	} else printf("\tNie usunieto punktu.\n");
}

void kasujListe() {
	struct rekord *end = last;

	while (first != null) {
		struct rekord *toDel = first;
		first=toDel->next;
		free(toDel);
		if (first == null) printf("\tLista zostala skasowana\n");
	}
}


void scalListe() {
	struct rekord *temp = first;
	struct rekord *curr = first;

	printf("\tLista X: ");
	while(temp != null){
		printf("%i ", temp->x);
		temp=temp->next;
	}temp=first;

	printf("\n\tLista Y: ");
	while(temp != null){
		printf("%i ", temp->y);
		temp=temp->next;
	}

}

int main() {

	int menu;

	while (1) {
		int a = 0;
		int b = 0;
		printf("\n 1 - WSTAW\n 2 - SZUKAJ\n 3 - USUN\n 4 - KASUJ\n 5 - WYSWIETL LISTE\n 6 - SCAL LISTE\n 0 - ZAKONCZ\n Twoj wybor: ");
		scanf("%i", &menu);
		if (menu == 0) break;

		switch(menu) {
			case 1:
	  		wstawRekord(); break;

			case 2:
	  		printf("\tRekord do znalezienia (x, y): ");
	 		scanf("%i %i", &a, &b);
	  		znajdzRekord(a, b);
			break;

			case 3:
			printf("\tRekord do usuniecia (x, y): ");
	 		scanf("%i %i", &a, &b);
			usunRekord(a, b);
			break;

			case 4:
			kasujListe();
			break;

			case 5:
			wyswietlListe();
			break;

			case 6:
			scalListe();
			break;
		}
	}

	printf("\n");
	return 0;

}
