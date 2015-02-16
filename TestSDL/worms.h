#ifndef WORMS_H
#define WORMS_H

#include <SDL\SDL.h>
#include "armes.h"
#define TAILLEINV 5

typedef struct {		//Structure worms
	int vie;				//Point de vie
	char* nom;				//Nom du joueur
	char* arme;				//Arme en cours d'utilisation
	Arme* invent[TAILLEINV];//Inventaire des armes et objets disponibles
	int posx;				//Position en X
	int posy;				//Position en Y
	int dir;				//Direction : gauche ou droite
	SDL_Rect wormsRect;
	//son?
} Worms;

#endif // !1


