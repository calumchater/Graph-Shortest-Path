#include "sousProgGraph.h"
#include <stdbool.h>
#include <stdio.h>
#define MAX 100
#include <stdlib.h>
#define NILSOM (struct liste_sommet*)0
#define NILARC (struct arc*)0
#define NIL (struct maillon_int*)0
#include "file.h"

void init_liste_int (struct liste_int* L)  // Dans cette fonction nous initialisons une liste_int 
{    printf("ici\n");
    L->tete = NIL;
    L->nbelem = 0;
}

/*void ajouter_en_tete_liste_int (struct liste_int *L, int d,struct Graphe G)
{     printf("ici\n");  
    struct maillon_int* nouveau;
    nouveau = (struct maillon_int*)malloc(sizeof(struct maillon_int));
    if(nouveau != (struct maillon_int*)0){

  printf("nIci\n");
    nouveau->value = d;       
    printf("12\n");
    printf("Nv :%d\n", nouveau->value);
    nouveau->next = L->tete;
    printf("11\n");
    L->tete = nouveau;
    L->nbelem += 1;
    }
    else{printf("error");}
}
*/
void ajouter_en_tete_liste_sommet (struct liste_sommet* L, struct arc d)
{   struct arc* nouveau;
    printf("ici \n");
    nouveau = (struct arc*)malloc(sizeof(struct arc));
    if(nouveau != NILARC){
/* appeler ici un eventuel constructeur pour nouveau->value */
    nouveau->flot = d.flot;/* affectation du flot */
    nouveau->cap =d.flot;
    nouveau->numero=d.numero;
    nouveau->next = L->head;
    L->head = nouveau;
    L->nbElements += 1;
    }
    else{
     printf("error");}
}


void buildGraph(char *file, struct Graphe *G){
    char line[MAX];
    FILE *f = fopen(file, "r" );
    if (f != NULL) {
    fgets(line,MAX,f);
    char poubelle;
    char first;
    sscanf(line,"%c",&first);
    while(first != 'a'){
       // Create graph inside of this. Take into account spaces. Test first character
      if(first == 'c'){
	printf("%s",line);
      }
      else if(first == 'p'){
	int som, arc;
	sscanf(line,"%c %d %d",&poubelle, &som, &arc);
	G->nbSommets = som;
	G->nbArcs = arc;
	G->L = (struct liste_sommet*)malloc((G->nbSommets)*sizeof(struct liste_sommet));
	printf("nb som: %d\n", G->nbSommets);
	printf("nb arc %d\n", G->nbArcs);

      }
      else if(first == 'n'){
	int som;
	char id;
	sscanf(line,"%c %d %c", &poubelle, &som, &id);
	if(id == 's'){
		G->source = som;
	}
	else if(id == 't'){
	  G->puits = som;
	  printf("puits: %d\n",G->puits);
	}
      }
         fgets(line,MAX,f);
	 sscanf(line,"%c",&first);
    }
    //  else if(first == 'a'){
	int boucle=1;
	int arr;
	int capacite;
	int dep;
	printf("%d\n", G->nbArcs);
	while(boucle <= G->nbArcs+1 ){
	    struct arc *nouvArc = (struct arc*)malloc(sizeof (struct arc)); // on definit un nouvel arc
	    sscanf(line,"%c %d %d %d",&poubelle, &dep, &arr, &capacite);     // on lit les infos concernant cet arc
	    nouvArc->cap=capacite;   // on cree les valeurs de ce nouvel arc
	    nouvArc->flot=0;
	    nouvArc->next=G->L[dep-1].head;     // le suivant de ce nouvel arc devient la tete de la liste_sommet
	    nouvArc->numero=arr;
	    G->L[dep-1].head=nouvArc;	 // la tete de la liste devient ce nouvel arc
	    G->L[dep-1].nbElements++;
	    fgets(line,MAX,f);
	    sscanf(line,"%c %d %d %d",&poubelle, &dep, &arr, &capacite);
	    boucle++;

	}}
  fclose(f);
  }

void buildRG(struct Graphe G, struct Graphe *H){
  struct arc* nouveau;
  struct arc* courant;
  H->L= (struct liste_sommet*)malloc(sizeof(struct arc*)*2*(G.nbSommets));
  H->nbSommets=G.nbSommets;
  H->source=G.source;
  H->puits=G.puits;
  H->flot=G.flot;
  H->nbArcs=G.nbArcs;
  int i=0;
  for(i=0;i<(H->nbSommets)-1;i++){
    struct arc* courant;
    courant= H->L[i].head;
    while(courant->next != NILARC){
      courant=courant->next;
      nouveau=malloc(sizeof(struct arc));
      nouveau=(H->L[i]).head;
      ajouter_en_tete_liste_sommet(&(H->L[courant->numero]),*nouveau);
    }
  }
}



void shortestPath(struct Graphe G, struct chemin *Ch){
  int *Mark;
  int *Pere;
  Mark=(int*)malloc((G.nbSommets)*sizeof(int));
  Pere=(int*)malloc(sizeof(int)*(G.nbSommets));
  int min;
  struct arc *courant;
  struct file Z;
  struct maillon *premier = (struct maillon*)malloc(sizeof(struct maillon*)*G.nbSommets);
  //initialisation de Mark a Faux//
  int i,s;
  for(i=0;i<G.nbSommets;i++){
    Mark[i]=0;
  }
  //initialisation de Z//
  s=G.source;

  init_file(&Z);

  enfiler(&Z,s);
  printf("ici\n");
  printf("%d \n", Z.premier->nombre);
  printf("G source = %d\n",s);
  courant = G.L[Z.premier->nombre].head;
  printf("%d\n", courant->numero);
  while(Z.vide != 1 && Mark[courant->numero]==0){
    defiler(&Z);   
    printf("%d\n", courant->cap);
    min= courant->cap;
    
    while(courant->next != NILARC){
      if(Mark[(courant->next)->numero]==0 && (courant->next)->cap!=0){
	
	Mark[(courant->next)->numero]=1;
	printf("2\n");
	Pere[(courant->next)->numero]=(courant->next)->numero;
	printf("3\n");
	enfiler(&Z, (courant->next)->numero);
      }
  printf("4\n");
  if(min > courant->next->cap){
        min=courant->cap;
	printf("cap min : %d", min);
      }
      courant=courant->next;
      
    }
  }
    printf("ici\n");
  int t;
  t= G.puits;
  printf("t: %d\n",t);
  printf("7\n");
  while(Pere[t]!=s){
    printf("5\n");
    //ajouter_en_tete_liste_int(Ch->C,t,G);
      printf("ici\n");  
    struct maillon_int* nouveau;
    nouveau = (struct maillon_int*)malloc(sizeof(struct maillon_int));
    printf("nIci\n");
    nouveau->value = t;       
    printf("12\n");
    printf("Nv :%d\n", nouveau->value);
    nouveau->next = Ch->C->tete;
    printf("11\n");
    Ch->C->tete = nouveau;
    printf("6\n");
    t=Pere[t];
    printf("7\n");
    Ch->longueurChemin = Ch->longueurChemin + 1;
  }
  printf("8\n");
  Ch->capMin=min;
}


int minCapa(struct Graphe G,struct chemin Ch){
  shortestPath(G,&Ch);
  return (Ch.capMin);
}



void updateFlowInNet(struct chemin Ch, int k, struct Graphe *G){
    struct maillon_int * courantChemin;
    struct maillon_int * suivantChemin;
    courantChemin = Ch.C->tete;
    suivantChemin = courantChemin->next;
    while (suivantChemin != NIL) { // On parcourt la liste chainee du chemin

    //Arc aller
    struct arc *courant;
    int value;
    int suivValue;
    value = courantChemin->value;
    suivValue =suivantChemin->value;
    courant = G->L[value].head; // On initialise courant avec le sommet i du chemin
    while (courant->numero != suivValue) { // on cherche le successeur
      courant = courant->next;
    }

    //Marquage Indirect
    if (courant->next == NILARC) { // nbTest-1 car la tete n'est pas un successeur
      courant = G->L[suivValue].head; // On va au sommet suivant du chemin
      while (courant->numero != value) {
        courant = courant->next;
      }
      courant->flot = courant->flot - k; // Reduction si MI
    } else {
      courant->flot = courant->flot + k; // Augmentation si MD
    }
    }
}


void updateFlowInRG(struct chemin Ch, int k, struct Graphe * G) {
    struct maillon_int * courantChemin;
    struct maillon_int * suivantChemin;
    int value;
    int suivValue;
    courantChemin = Ch.C->tete;
    suivantChemin = courantChemin->next;
    value = courantChemin->value;
    suivValue =suivantChemin->value;
    while (suivantChemin != NIL) { // On parcourt la liste chainee du chemin

    //Arc aller
    struct arc *courant;

    courant = G->L[value].head; // On initialise courant avec le sommet i du chemin
    while (courant->numero != suivValue) { // on cherche le successeur
      courant = courant->next;
    }

    //Marquage Indirect
    if (courant->next == NILARC) { // nbTest-1 car la tete n'est pas un successeur
      courant = G->L[suivValue].head; // On va au sommet suivant du chemin
      while (courant->numero != value) {
        courant = courant->next;
      }
      courant->flot = courant->flot - k; // Reduction si MI
    } else {
      courant->flot = courant->flot + k; // Augmentation si MD
    }
    //  Arc Retour
    courant = G->L[value].head; // On initialise courant avec le sommet i du chemin
    while (courant->next != NILARC) { // boucle dans reseau?
      courant = courant->next;
    }
    // Marquage Indirect
    if (courant->next == NILARC) { // nbTest-1 car la tete n'est pas un successeur
      courant = G->L[suivValue].head; // On va au sommet suivant du chemin
      while (courant->numero != suivantChemin->value) {
        courant = courant->next;
      }
      courant->flot = courant->cap - k; // Reduction si MD
    } else {
      courant->flot = courant->cap + k; // Augmentation si MI
    }
    courantChemin = courantChemin->next;
    suivantChemin = courantChemin->next;
  }
}


