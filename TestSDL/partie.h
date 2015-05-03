#ifndef GAME_H
#define GAME_H

#include "worms.h"
#include "carte.h"

#define DEFAULTPATH "../assets/logAndResult/ResultGame.txt"

/* Structures et constantes relatives � la gestion d'une partie */

typedef struct Equipe{			//Structure �quipe
	struct Worms** worms;				//Tableau de Worms
	int nbWormsStart;			//Nombre de Worms au d�but de la partie
	int vie;					//Somme des points de vie de l'�quipe
	char nom[50];				//Nom d'�quipe
	SDL_Color color;			//Couleur d'�quipe
	//logo?
} Equipe;

typedef struct {				//Structure d'une partie
	Equipe** equipes;			//Tableau d'�quipes
	int nbEquipe;				//Nombre d'�quipe
	Terrain* pMapTerrain;		//Carte en cours
	int temps;					//Dur�e
	char nomMap[100];
} Jeu;


Jeu * nouveauJeu(char * map);
void destroyJeu(Jeu ** game);
Equipe * nouvelleEquipe(char * nomE, SDL_Color couleur, int nbWorms, int indexTeam);
void destroyEquipe(Equipe** team, int nbE);
int getLifeTeam(Equipe* team);
void updateTeamLife(Equipe** equipeTab);
int mainInit();					// Initialise les polices et les variables globales
void destroyPolice();
int saveGame(Jeu* jeu);
int isGameEnd(Equipe** equipeTab);

#endif