#include<stdio.h>
#include <time.h>
#define MLD 1000000000.0 

void quicksort(int tab[2500], int pierwszy, int nastepny){
    int pivot, j, temp, i;

     if(pierwszy<nastepny){
         pivot=pierwszy;
         i=pierwszy;
         j=nastepny;

         while(i<j){
             while(tab[i]<=tab[pivot]&&i<nastepny) i++;
             while(tab[j]>tab[pivot]) j--;
             if(i<j){
                 temp=tab[i];
                  tab[i]=tab[j];
                  tab[j]=temp;
             }
         }
         temp=tab[pivot];
         tab[pivot]=tab[j];
         tab[j]=temp;
         quicksort(tab,pierwszy,j-1);
         quicksort(tab,j+1,nastepny);
    }
}

int main() {
  int tab[2500],i,k;
  int n[] = {100, 500, 1000, 2500};
  struct timespec tp0, tp1;
  double Tn;

  printf("-----------------------------------------------------------------------\n");
  printf("Rozmiar tablicy \t| Dane losowe (t) \t| Dane niekorzystne (t)\n");
  printf("-----------------------------------------------------------------------\n");
 
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

  for(k=0; k<4; k++) {
    printf("%d\t\t\t", n[k]);

    //LICZBY LOSOWE

    for(i=1; i<=n[k]; i++) tab[i]=rand()%100; 
    quicksort(tab, 0, n[k]);
    //for(i=1; i<=n[k]; i++) printf("%d ", tab[i]); ---> wypisywanie liczb
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    printf("| %3.7lf\t\t",Tn);

    //LICZBY NIEKORZYSTNE

    for(i=n[k]; i>=1; i--) tab[i]=i;
    quicksort(tab, 0, n[k]);
    //for(i=1; i<=n[k]; i++) printf("%d ", tab[i]);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    printf("| %3.7lf\t\t", Tn);
    printf("\n");
  }
  printf("-----------------------------------------------------------------------\n");
 /* 
    int Rozmiar;

    printf("Podaj rozmiar tablicy: ");
    scanf("%d", &rozmiar);

    printf("Podaj %d elementow: ", rozmiar);
    for(i=0; i<rozmiar; i++)
    scanf("%d",&tab[i]);

    quicksort(tab, 0, rozmiar-1);

    printf("Posortowane elementy: ");
    for(i=0; i<rozmiar; i++)
    printf("%d ", tab[i]);
*/

  return 0;
}
