#ifndef WEAPONS_H
#define WEAPONS_H

#include "Libraries.h" //Inclus toutes les librairies

#define BombFactor 0.5
#define MAXDAMAGE 20
/* D�claration des structures concernant les armes */

typedef struct{		/* Structure munition */
	char* nom;			/* Nom de la munition */
	int posx;			/* Position en X */
	int posy;			/* Position en Y */
	float angle;		/* Angle de la munition */
	//image?
} Munition;

typedef struct {	/* Structure arme */
	char* nom;			/* Nom de l'arme */
	float degats;		/* D�gats de l'arme */
	int radius;		/* Diam�tre d'action de l'arme */
	int range;	    /*Ce param�tre ne s'applique que pour les armes non lanc�es (mitrailleuse, ce genre de truc)*/
	int nbmuni;			/* Nombre de munitions */
	Munition muni;		/* Munition en cours d'utilisation */
	float angle;		/* Angle de l'arme (sa position est celle du worms) */
	KaamObject* weaponObject;	/*Pour une grenade : A initialiser avec la vitesse horizontale et la vitesse verticale correspondant au tir*/ 
								/*D�pendent de la puissance et l'inclinaison du tir, les vitesses sont exprim�es en A.cos(angle) pour X et B.sin(angle) pour Y*/
	//image?
	//son?
} Arme;


void explosion(int x, int y, int rayon, SDL_Surface * pSurfaceMap, SDL_Texture * pTextureDisplay);

#endif