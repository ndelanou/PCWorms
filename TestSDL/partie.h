#ifndef GAME_H
#define GAME_H

#include "worms.h"
#include "carte.h"


/* Structures et constantes relatives � la gestion d'une partie */

typedef struct {			//Structure �quipe
	Worms** worms;				//Tableau de Worms
	int nbWormsStart;			//Nombre de Worms au d�but de la partie
	int vie;					//Somme des points de vie de l'�quipe
	char* nom;					//Nom d'�quipe
	SDL_Color color;			//Couleur d'�quipe
	//logo?
} Equipe;

typedef struct {				//Structure d'une partie
	Equipe** equipes;			//Tableau d'�quipes
	int nbEquipe;				//Nombre d'�quipe
	Terrain map;				//Carte en cours
	int temps;					//Dur�e
	char nomMap[100];
} Jeu;


Jeu * nouveauJeu(int nbE, int nbW, char * map);
void destroyGame(Jeu ** game);
Equipe * nouvelleEquipe(char * nomE, SDL_Color couleur, int nbWorms);
void destroyEquipe(Equipe ** team, int nbE);
int vieEquipe(Equipe * team);

#endif