

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
int initSWR(SDL_Window** pWindow, SDL_Renderer **pRenderer);	//Initialise la SDL, la SDL_Image, le pWindow et le pRenderer
SDL_Surface * loadImage(const char * file);	//Charge une image dans une surface
SDL_Texture * loadTexture(SDL_Renderer * pRenderer, const char * file);	//Charge une image dans une texture
SDL_Window * creerFenetre(const int w, const int h, const char * nom);	//Cr�� une fen�tre de largeur w, hauteur h et de nom nom
void initCameras(SDL_Renderer * pRenderer, Terrain * map, SDL_Rect * camera, Worms  * worms);	//Initialise la position de la cam�ra
int createGlobalTexture(SDL_Surface* pSurfaceMap, SDL_Texture** pTexture, SDL_Renderer* pRenderer, SDL_Rect* camera);

//Fonctions diverses
void afficherPoint(SDL_Renderer * r);	//affiche un point 
void afficherLigne(SDL_Renderer * r, Point * p1, Point * p2);	//affiche une ligne
void deplacementRectangle(SDL_Rect * rect, int x2, int y2, int dir);	//d�place un rectangle en fonction de la souris
int secureRect(SDL_Rect* pRect, SDL_Surface* pSurface);	//r�ajuste un rectangle pour pas d�passer de la map
void frameRate(unsigned int fM);	//g�re le framerate
SDL_Rect initRect(int x, int y, int w, int h);

//gestion des inputs
void updateScreen(SDL_Renderer * pRenderer, int nb, ...);	//actualise l'affichage
void moveCam(SDL_Texture* pTexture, SDL_Rect * camera, Input * pInput);	//d�place la cam�ra dans l'espace
void zoomIn(SDL_Renderer * pRenderer, SDL_Texture* pTexture, SDL_Rect * camera, Input * pInput);	//Zoom In, grossis
void zoomOut(SDL_Renderer * pRenderer, SDL_Texture* pTexture, SDL_Rect * camera);	//Zoom out, r�tr�cis
int updateGlobaleTexture(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceModif, SDL_Texture* pTexture, SDL_Rect* pRectSurfaceModif);	//Met � jour la texture globale
SDL_Surface* crop_surface(SDL_Surface* sprite_sheet, int x, int y, int width, int height);	//Met � l'�chelle la surface de collision

//Fonctions de nettoyage

void cleanUp(SDL_Window** pWindow, SDL_Renderer** pRenderer, Input** pInput);	//nettoie et quit la SDL
void clearRenderer(SDL_Renderer * pRenderer);	//Clear de l'�cran

void animationWorms(SDL_Surface * display);

#endif
