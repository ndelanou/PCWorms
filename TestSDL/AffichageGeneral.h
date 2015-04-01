

#ifndef DISPLAY_H
#define DISPLAY_H

#include "worms.h"
#include "HUD.h"
#include "carte.h"
#include "armes.h"
#include "partie.h"

#define FRAME_RATE (1000 / 80)



int mainFenetre(Jeu * jeu);
int sandboxRenderer();


//Fonctions d'initialisation
int initSWR(SDL_Window** p_pWindow, SDL_Renderer **p_pRenderer);	//Initialise la SDL, la SDL_Image, le pWindow et le pRenderer
void initCameras(SDL_Renderer * pRenderer, Terrain * pMapTerrain, SDL_Rect * pCamera, Worms  * pWorms);	//Initialise la position de la cam�ra

//Fonctions diverses
void afficherPoint(SDL_Renderer * r);	//affiche un point 
void afficherLigne(SDL_Renderer * r, Point * p1, Point * p2);	//affiche une ligne
void deplacementRectangle(SDL_Rect * rect, int x2, int y2, int dir);	//d�place un rectangle en fonction de la souris
int reajustRect(SDL_Rect* pRect, SDL_Surface* pSurfaceMap);	//r�ajuste un rectangle pour pas d�passer de la map
void frameRate(unsigned int fM);	//g�re le framerate
int wormsOverlay(Worms** wormsTab);
int updateWormsOverlay(Worms** wormsTab, SDL_Texture* pTextureDisplay, SDL_Surface* pSurfaceMap, int indexWorms1, int indexWorms2);

//gestion de l'affichage
void updateScreen(SDL_Renderer * pRenderer, int nb, ...);	//actualise l'affichage
void moveCam(SDL_Texture* pTexture, SDL_Rect * camera, Input * pInput);	//d�place la cam�ra dans l'espace
void zoomIn(SDL_Renderer * pRenderer, SDL_Texture* pTexture, SDL_Rect * camera, Input * pInput);	//Zoom In, grossis
void zoomOut(SDL_Renderer * pRenderer, SDL_Texture* pTexture, SDL_Rect * camera);	//Zoom out, r�tr�cis
int updateGlobaleTexture(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceModif, SDL_Texture* pTextureDisplay, SDL_Rect* pRectSurfaceModif);	//Met � jour la texture globale

//Fonctions de nettoyage

void cleanUp(SDL_Window** p_pWindow, SDL_Renderer** p_pRenderer, Input** p_pInput, SDL_Texture** p_pTextureDisplay);	//nettoie et quit la SDL
void clearRenderer(SDL_Renderer * pRenderer);	//Clear de l'�cran

int updateGlobaleTexture2(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceModif, SDL_Texture* pTextureDisplay, SDL_Rect* pRectSurfaceModif);


#endif
