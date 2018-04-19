# include "stdio.h"
# include "sousProgGraph.h"
#include "file.h"
#define NIL (struct maillon_int*)0
#define MAX 100
#include <stdlib.h> 
 
int main(){
      
  struct Graphe G;


  
  //printf("et la capacite minimum est =%d\n",Ch.capMin);
  char adresse[MAX];
  
  scanf("%s",adresse);
  buildGraph(adresse,&G);
  int i = 0;
  for(i=0; i<G.nbSommets;i++){
      struct arc * courant = G.L[i].head;
      int j = 0;
      for( j=0;j<G.L[i].nbElements;j++){
      printf("dep: %d // arr: %d\n", i+1, courant->numero);
	courant = courant->next;
    }
  }
      printf("G a %d sommets et %d arcs\n", G.nbSommets, G.nbArcs);
  struct chemin Ch;
  //Ch = malloc(sizeof(struct chemin));
  //= (struct maillon_int*)malloc(sizeof(struct maillon_int*)*(G.nbSommets));
  struct Graphe H;
  shortestPath(G,&Ch);
  struct maillon_int* courant;
  printf("10\n");
  printf("num tete : %d\n", Ch.C->tete->value);
  courant= Ch.C->tete;
printf("9\n");
  //pour afficher le chemin//
  while(courant!=NIL){
    printf("indice chemin: %d\n", courant->value);
    courant = courant->next;
  }
  
  return 0;
}
