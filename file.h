#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <assert.h>


/* file.h */

/* IMPLANTATION */

#include <stdbool.h>

struct maillon
{
    int nombre;
    struct maillon *suivant;
};

struct file
{
    int vide;
    struct maillon *premier;
};

extern void init_file (struct file*);
extern void clear_file (struct file*);
extern void enfiler (struct file*, int);
extern void defiler (struct file*);
extern int file_vide (struct file);




#endif // FILE_H_INCLUDED
