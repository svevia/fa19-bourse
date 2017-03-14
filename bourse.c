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

typedef struct Action Action;
struct Action {
   File *achat;
   File *vente;
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

int defiler(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int quantite = 0;

    /* On vérifie s'il y a quelque chose à défiler */
    if (file->premier != NULL)
    {
        Ordre *ordre = file->premier;

        quantite = ordre->quantite;
        file->premier = ordre->suivant;
        free(ordre);
    }

    return quantite;
}

 Action* createAction(int prix,int quantite){
	 
	 Action *nouveau = malloc(sizeof(*nouveau));
	 nouveau->achat =  malloc(sizeof(nouveau->achat));
	 nouveau->vente =  malloc(sizeof(nouveau->vente));
	 nouveau->prix = prix;
	 enfiler(nouveau->vente,quantite);
	 return nouveau;
 }
 
 
 void acheterAction(Action *action,int quantite){
	 int ordreVente = action->vente->premier->quantite;
	 if(ordreVente > quantite){
		 action->vente->premier->quantite = ordreVente-quantite;
	 }
	 else{
		 defiler(action->vente);
		 acheterAction(action,quantite-ordreVente);
	 }
 }

int main()
{
	Action *action = createAction(10,2000);
	printf("hello world!\n");
	printf("%d\n",action->prix);
	acheterAction(action,300);
	printf("%d\n",action->vente->premier->quantite);
	return 0;
}












