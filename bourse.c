#include <stdio.h>
#include <stdlib.h>


typedef struct Ordre Ordre;
struct Ordre
{
    int quantite;
    Ordre *suivant;
};

typedef struct File File;
struct File
{
    Ordre *premier;
};

typedef struct action action;
struct action {
   File achat;
   File vente;
   int prix;
};


void enfiler(File *file, int quantite)
{
    Ordre *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->quantite = quantite;
    nouveau->suivant = NULL;

    if (file->premier != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Ordre *elementActuel = file->premier;
        while (elementActuel->suivant != NULL)
        {
            elementActuel = elementActuel->suivant;
        }
        elementActuel->suivant = nouveau;
    }
    else /* La file est vide, notre élément est le premier */
    {
        file->premier = nouveau;
    }
}


int main()
{
	
	printf("hello world!\n");
	return 0;
}












