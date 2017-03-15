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
   char* nom;
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

 Action* createAction(int prix,int quantite, char* nom){
	 
	 Action *nouveau = malloc(sizeof(*nouveau));
	 nouveau->achat =  malloc(sizeof(nouveau->achat));
	 nouveau->vente =  malloc(sizeof(nouveau->vente));
	 nouveau->achat->premier = NULL;
	 nouveau->vente->premier = NULL;
	 nouveau->prix = prix;
	 nouveau->nom = nom;
	 enfiler(nouveau->vente,quantite);
	 return nouveau;
 }
 
 
 void acheterAction(Action *action,int quantite){
	 int ordreVente = action->vente->premier->quantite;
	 if(ordreVente > quantite){
		 action->vente->premier->quantite = ordreVente-quantite;//Si la valeur d'achat est < à la vente, in reduit l'offre de vente
	 }
	 else{
		 defiler(action->vente);
		 acheterAction(action,quantite-ordreVente);
	 }
 }
 
 
 void printAction(Action *action){
	 printf("%s\n",action->nom);
	 printf("--------------------------------------------------\n");
	 printf("achat                     | vente                      \n");
	 printf("--------------------------|-----------------------\n");
	 Ordre* achatActuel = action->achat->premier;
	 Ordre* venteActuel = action->vente->premier;
	 while(achatActuel != NULL || venteActuel != NULL){
		 if(achatActuel != NULL){
			 printf("%5d                     |",achatActuel->quantite);
		 }
		 else{
			 printf("                          |");
		 }
		 if(venteActuel != NULL){
			 printf("%5d                 \n",venteActuel->quantite);
		 }
		 else{
			 printf("                      \n");
		 }
		 
		 if(achatActuel!= NULL){
			achatActuel = achatActuel->suivant;
		 }
		 if(venteActuel != NULL){
			venteActuel = venteActuel->suivant;
		 }
	 }
 }
 

int main()
{
	Action *action = createAction(10,2000,"action 1");
	enfiler(action->vente,1000);
	enfiler(action->achat,500);
	enfiler(action->achat,2500);
	enfiler(action->vente,300);
	printAction(action);
	acheterAction(action,2500);

	return 0;
}












