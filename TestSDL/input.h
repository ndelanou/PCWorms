#ifndef INPUT_H
#define INPUT_H

#include "Libraries.h"

/*Acquisition des Inputs*/
void getInput();	//R�cup�re les inputs
void INPUT_keydownInputs(SDL_Event event);
void INPUT_keyupInputs(SDL_Event event);
void mouseButtonDown(SDL_Event event);
void mouseButtonUp(SDL_Event event);
void mouseWheel(SDL_Event event);

/*Gestion des Inputs*/
int gestInput(Jeu* jeu, SDL_Texture* pTextureDisplay, SDL_Rect* pCamera, Worms** wormsTab);	//Gestion globale des Inputs
void inputsCamera(SDL_Texture* pTextureDisplay, SDL_Rect* pCamera, Worms * pWorms);	//Gestion des Inputs de la camera
void inputsJumpWorms(Worms* pWorms, SDL_Surface* pSurfaceMap);	//Gestion des Inputs pour un saut de worms
void inputsWeapons(SDL_Texture* pTextureDisplay, SDL_Rect* pCamera, Terrain* pMapTerrain, Worms** wormsTab);	//Gestion des Inputs des armes
void callNextWorms(Worms** wormsTab);
int calculIndex();

/*Initialisations*/
Input* initInput();		//Initialise les Input
void resetStructInput();
Cursor initCursor(void);	//initialise la structure  cursor
void secuTextInput();


#endif