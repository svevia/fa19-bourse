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
   double prix;
   char* nom;
};


 void listAction(Action** table);

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

 Action* createAction(double prix,int quantite, char* nom){
	 
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
 
  int countVente(Action *action){
	 int result = 0;
	 Ordre* elementActuel = action->vente->premier;
	 if(elementActuel == NULL){
		 return 0;
	 }
	 while (elementActuel->suivant != NULL)
        {
			result += elementActuel->quantite;
            elementActuel = elementActuel->suivant;
        }
		result += elementActuel->quantite;
		return result;

 }
 
 void acheterAction(Action *action,int quantite){
	 if(action->vente->premier != NULL){
		 int ordreVente = action->vente->premier->quantite;
		 if(ordreVente > quantite){
			 action->vente->premier->quantite = ordreVente-quantite;//Si la valeur d'achat est < à la vente, in reduit l'offre de vente
		 }
		 else if(ordreVente == quantite){
			 defiler(action->vente);
			 return;
		 }
		 else{
			 defiler(action->vente);
			 acheterAction(action,quantite-ordreVente);
		 }
	 }
 }
 
 
 void printAction(Action **action, int i){
	 printf("%s        %.3f€\n",action[i]->nom,action[i]->prix);
	 printf("--------------------------------------------------\n");
	 printf("achat                     | vente                      \n");
	 printf("--------------------------|-----------------------\n");
	 Ordre* achatActuel = action[i]->achat->premier;
	 Ordre* venteActuel = action[i]->vente->premier;
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
 


 
 
 void checkForMove(Action *action){// Si le marché est ouvert, vend les actions tant que c'est possible
	 if(open == 1){
		 while(action->achat->premier != NULL && action -> vente->premier != NULL){
			 printf("tour");
			 if(countVente(action)< action->achat->premier->quantite){
				 action->achat->premier->quantite = action->achat->premier->quantite - countVente(action);
				 acheterAction(action,countVente(action));
			 }
			 
			 else{
				acheterAction(action,defiler(action->achat));
			 }
		 }
	 }
 }


 
  void printMenu(Action **action, int i){
	 
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
	 printf("4.Afficher recapitulatif de l'action\n");
	 printf("5.Lister actions\n\n");
	 
	 
	 int choix;
	scanf("%d", &choix);
	
	int quantite;
	double prix;
	switch(choix){
		case 1:
		open = 1-open;
		checkForMove(action[i]);
		printMenu(action,i);

		break;
		
		case 2:
		printf("Quantité : \n");

		scanf("%d", &quantite);
		
		prix = quantite * action[i]->prix;
		printf("prix : %f\n",prix);
		enfiler(action[i]->achat,quantite);
		checkForMove(action[i]);
		printMenu(action,i);
		break;
		
		case 3:
		printf("Quantité : \n");
		scanf("%d", &quantite);

		prix = quantite * action[i]->prix;
		printf("prix : %f\n",prix);
		
		enfiler(action[i]->vente,quantite);
		checkForMove(action[i]);
		printMenu(action,i);
		break;
		
		case 4:
		printAction(action,i);
		printMenu(action,i);
		break;
		
		case 5:
		listAction(action);
		break;
	}
 }
 
 void listAction(Action** table){
	 int i =0;
	 while(table[i]!=NULL){
		 printf("%d. %s - %.3f€\n",i,table[i]->nom,table[i]->prix);
		 i++;
	 }
	 
	  int choix;
	scanf("%d", &choix);
	
	if(choix < 1000 && table[choix] != NULL){
		printAction(table,choix);
		printMenu(table,choix);
	}	 
	 
	 
 }
 
 
int main()
{
	Action* table[1000];
	
	table[0] = createAction(10,2000,"action 1");
	listAction(table);
	
	return 0;
}












