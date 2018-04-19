#include <assert.h>
#include "file.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void init_file (struct file* F)
{
    F->premier = NULL;
    F->vide = 1;
    
}

void clear_file (struct file* F)
{
}

void enfiler(struct file *file, int nvNombre)
{
    struct maillon *nouveau;
    nouveau = (struct maillon*)malloc(sizeof(struct maillon*));
    nouveau->nombre = nvNombre;
    nouveau->suivant= NULL;
    
    if (file->premier != NULL) /* La file n'est pas vide */
    {
        /* On se positionne � la fin de la file */
        struct maillon *elementActuel = file->premier;
        while (elementActuel->suivant != NULL)
        {
            elementActuel = elementActuel->suivant;
        }
        elementActuel->suivant = nouveau;
    }
    else /* La file est vide, notre �l�ment est le premier */
    {
        file->premier = nouveau;
    }
    file->vide = 0;
}

void defiler(struct file *file)
{
    if (file == NULL)
    {
        printf("error");
    }

    /* On v�rifie s'il y a quelque chose � d�filer */
    struct maillon *elementDefile;
    if (file->premier != NULL)
    {
        elementDefile = file->premier;
        file->premier = elementDefile->suivant;
        free(elementDefile);
    }
}

int file_vide (struct file file)
{
    return file.vide;
}

