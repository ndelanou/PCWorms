#include <stdio.h>
#include <stdlib.h>
#define TAILLEINV 5

int test(int argc, char** argv)
{
	typedef struct {			//D�claration de la structure de chaque Worms
		int vie;				//Point de vie
		char* nom;				//Nom du joueur
		char* arme;				//Arme en cours d'utilisation
		char* invent[TAILLEINV];//Inventaire des armes et objets disponibles
		int posx;				//Position en X
		int posy;				//Position en Y
		int dir;				//Direction : gauche ou droite
		//image ?
	} Worms;

	typedef struct {		//D�claration de la structure de chaque Worms
		char* nom;			//Nom de l'arme
		float degats;		//D�gats de l'arme
		float radius;		//Diam�tre d'action de l'arme
		float portee;		//Port�e de l'arme � rentrer dans l'�quation de parabole (cf Gravit�e)
		int nbmuni;			//Nombre de munitions
		char* munition;		//Munition en cours d'utilisation
		float angle;		//Angle de l'arme (sa position est celle du worms)
		//image?
	} Arme;

	typedef struct{
		char* nom;			//Nom de la munition
		int posx;			//Position en X
		int posy;			//Position en Y
		float angle;		//Angle de la munition
		//image?
	} Munition;
}