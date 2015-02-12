#include <stdio.h>
#include <stdlib.h>
#define TAILLEINV 5
#define TAILLETEAM 5
#define NBTEAM 5

void Structure()
{
	//Structures d�j� d�clar�es dans l'ordre : muni, arme, worms, equipe, terrain, jeu, caisse

	typedef struct{		//Structure munition
		char* nom;			//Nom de la munition
		int posx;			//Position en X
		int posy;			//Position en Y
		float angle;		//Angle de la munition
		//image?
	} Munition;

	typedef struct {	//Structure arme
		char* nom;			//Nom de l'arme
		float degats;		//D�gats de l'arme
		float radius;		//Diam�tre d'action de l'arme
		float portee;		//Port�e de l'arme � rentrer dans l'�quation de parabole (cf Gravit�e)
		int nbmuni;			//Nombre de munitions
		Munition muni;		//Munition en cours d'utilisation
		float angle;		//Angle de l'arme (sa position est celle du worms)
		//image?
		//son?
	} Arme;

	typedef struct {		//Structure worms
		int vie;				//Point de vie
		char* nom;				//Nom du joueur
		char* arme;				//Arme en cours d'utilisation
		Arme* invent[TAILLEINV];//Inventaire des armes et objets disponibles
		int posx;				//Position en X
		int posy;				//Position en Y
		int dir;				//Direction : gauche ou droite
		//image?
		//son?
	} Worms;

	typedef struct {			//Structure �quipe
		int vie;					//Somme des points de vie de l'�quipe
		char* nom;					//Nom d'�quipe
		char* color;				//Couleur d'�quipe
		Worms* equipe[TAILLETEAM];	//Tableau de Worms
		//logo?
	} Equipe;

	typedef struct {			//Structure terrain
		//mapcollision?				
		//background?
		//mapdestruction?
	} Terrain;

	typedef struct {			//Structure d'une partie
		Equipe equipes[NBTEAM];		//Nombre d'�quipe
		Terrain map;				//Carte en cours
		int temps;					//Dur�e

	} Jeu;

	typedef struct{
		char* nom;			//Nom de la caisse
		int posx;			//Position en X
		int posy;			//Position en Y
		//image?
	} Caisse;
}

