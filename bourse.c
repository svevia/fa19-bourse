#include <stdio.h>
#include <stdlib.h>


int open = 0; //0 isi bourse est fermé, 1 si ouvert


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
 

 
 int countVente(Action *action){
	 int result = 0;
	 Ordre* elementActuel = action->vente->premier;
	         while (elementActuel->suivant != NULL)
        {
			result += elementActuel->quantite;
            elementActuel = elementActuel->suivant;
        }
		result += elementActuel->quantite;
		return result;

 }
 
 
 void checkForMove(Action *action){// Si le marché est ouvert, vend les actions tant que c'est possible
	 if(open == 1){
		 while(action->achat->premier != NULL && countVente(action)> action->achat->premier->quantite){
			 acheterAction(action,defiler(action->achat));
		 }
	 }
 }

 
  void printMenu(Action *action){
	 
	 printf("MENU\n");
	 printf("Marché ");
	 if(open == 1){
		 printf("Ouvert \n\n");
	 }
	 else{
		 printf("Fermé \n\n");
	 }
	 
	 printf("1.Ouvrir/Fermé marché\n");
	 printf("2.Placer ordre d'achat\n");
	 printf("3.Placer ordre de vente\n");
	 printf("4.Afficher recapitulatif de l'action\n\n");
	 
	 
	 int choix;
	scanf("%d", &choix);
	
	int quantite;
	switch(choix){
		case 1:
		open = 1-open;
		checkForMove(action);
		printMenu(action);

		break;
		
		case 2:
		printf("Quantité : \n");

		scanf("%d", &quantite);
		enfiler(action->achat,quantite);
		printMenu(action);
		break;
		
		case 3:
		printf("Quantité : \n");
		scanf("%d", &quantite);
		enfiler(action->vente,quantite);
		printMenu(action);
		break;
		
		case 4:
		printAction(action);
		printMenu(action);
		break;
	}
 }
 
 
int main()
{
	Action *action = createAction(10,2000,"action 1");
	printAction(action);
	printMenu(action);
	
	return 0;
}












