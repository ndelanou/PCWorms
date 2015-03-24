#ifndef WORMS_H
#define WORMS_H

#include "Libraries.h"
#include "armes.h"

#define TAILLEINV 5

typedef struct {		//Structure worms
	int vie;				//Point de vie
	char* nom;				//Nom du joueur
	char* arme;				//Arme en cours d'utilisation
	Arme* invent[TAILLEINV];//Inventaire des armes et objets disponibles
	int xAbs;				//position "absolu" en X
	int yAbs;				//position "absolu" en Y
	float vitx;
	float vity;
	enum DIRECTION dirSurface;
	enum DIRECTION dir;				//Direction : gauche ou droite
	SDL_Rect wormsRect;
	SDL_Surface* wormsSurface;
	SDL_Surface* wormsSurfaceLeft;
	SDL_Surface* wormsSurfaceRight;
	SDL_Surface* wormsSurfaceTomb;
	SDL_Surface* texteSurface;
	//son?
} Worms;

/*Creation et destruction d'un worms*/
Worms* createWorms(char* name);	//Cr�� un worms � partir d'une image
void destroyWorms(Worms** worms, int nbWorms);	//d�truit un worms

/*Deplacement d'un worms*/
void deplacementWorms(Input* pInput, Worms* worms, SDL_Surface* surfaceCollision);	//d�place un worms au clavier

/*Fonctions diverses*/
char retournementWorms(Input* pInput, Worms* worms);
void swapSurface(Worms* worms);
int deathByLimitMap(Worms* worms, SDL_Surface* map);
#endif // !1


