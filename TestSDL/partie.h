#ifndef GAME_H
#define GAME_H

#include "worms.h"
#include "carte.h"
#include "Libraries.h" //Inclus toutes les librairies

#define TAILLETEAM 5
#define NBTEAM 5

/* Structures et constantes relatives � la gestion d'une partie */

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

#endif