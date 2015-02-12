#include "armes.h"
#include "carte.h"
#define TAILLEINV 5
#define TAILLETEAM 5
#define NBTEAM 5

/* Structures et constantes relatives � la gestion d'une partie */

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



typedef struct {			//Structure d'une partie
	Equipe equipes[NBTEAM];		//Nombre d'�quipe
	Terrain map;				//Carte en cours
	int temps;					//Dur�e

} Jeu;