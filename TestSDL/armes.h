#ifndef ARMES_H
#define ARMES_H
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
	float radius;		/* Diam�tre d'action de l'arme */
	float portee;		/* Port�e de l'arme � rentrer dans l'�quation de parabole (cf Gravit�e) */
	int nbmuni;			/* Nombre de munitions */
	Munition muni;		/* Munition en cours d'utilisation */
	float angle;		/* Angle de l'arme (sa position est celle du worms) */
	//image?
	//son?
} Arme;

#endif