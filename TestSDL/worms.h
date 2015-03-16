#ifndef WORMS_H
#define WORMS_H

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
	SDL_Surface* texteSurface;
	//son?
} Worms;


Worms* createWorms(const char* name);	//Cr�� un worms � partir d'une image
void destroyWorms(Worms** worms, int nbWorms);	//d�truit un worms
void deplacementWorms(Input* pInput, Worms* worms, SDL_Surface* surfaceCollision);	//d�place un worms au clavier
char retournementWorms(Input* pInput, Worms* worms);
#endif // !1


