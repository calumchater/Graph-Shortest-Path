#include <stdio.h>
#define MAXLENGTH 100000

struct Graphe{
	int nbSommets;
	int source; // indice de la source dans L[]
	int puits; // indice du puits dans L[]
	int flot;
	int nbArcs;
	struct liste_sommet *L;
};

struct liste_sommet{  // Definir un NIL pour liste arc
	struct arc *head;
	int nbElements;
};

struct arc{
	struct arc *next;
	int flot;
	int cap;
	int numero;
};

struct chemin{
	int capMin;
	int longueurChemin;
	struct liste_int *C;
};

struct maillon_int
{   int value;
    struct maillon_int* next;
};

struct liste_int
{   struct maillon_int* tete;
    int nbelem;
};

extern void init_liste_int (struct liste_int*);


extern void ajouter_en_tete_liste_int (struct liste_int*, int, struct Graphe);


extern void buildGraph(char *, struct Graphe *);  // Fichier dimacs


extern void buildRG (struct Graphe, struct Graphe *);  // On part du reseau et on construit un graphe d'ecart


extern void shortestPath(struct Graphe,struct chemin *);   // Ici on utilise le graphe d'ecart


extern int minCapa(struct Graphe,struct chemin);


extern void updateFlowInNet(struct chemin, int, struct Graphe *);  // Le graphe ici est le reseau


extern void updateFlowInRG(struct chemin, int, struct Graphe *);  // Le graphe utilise ici est le graphe d'ecart


extern void ajouter_en_tete_liste_sommet(struct liste_sommet*,struct arc);

