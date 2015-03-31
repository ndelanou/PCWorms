#ifndef CARTE_H
#define CARTE_H

#include "worms.h"
/* D�claration des structures et constantes relatives � la carte jou�e */

typedef struct {	/* Structure terrain */
	SDL_Texture* imageBackground; /* background */
	SDL_Surface* imageMapSurface;
} Terrain;

typedef struct{
	char* nom;			/* Nom de la caisse */
	int posx;			/* Position en X */
	int posy;			/* Position en Y */
	//image?
} Caisse;

/*Fonction de gestion du terrain*/
int initialisionTerrain(Terrain** p_pMapTerrain, SDL_Renderer * pRenderer, const char * nomImageFond, const char * nomImageMap);
void destroyMap(Terrain** p_pMapTerrain);	//d�truit un terrain


/*Fonctions diverses*/
int limitMap(int mapHight, int mapWidth, SDL_Surface* pSurfaceMotion, enum DIRECTION* pDirecion); //D�termine si un objet est hors map et le replace si il faut


/*Manipulation des pixels*/
Uint32 ReadPixel(SDL_Surface* pSurface, int x, int y);
void DrawPixel(SDL_Surface* pSurface, int x, int y, Uint32 pixelToWrite);

/*D�tection et gestion des collisions*/
int detectionCollisionRect(SDL_Renderer* pRenderer, SDL_Surface* pSurfaceMap, int* xE, int* yE, SDL_Rect* pRect);
int detectionCollisionSurface(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceMotion);
int detectionCollisionSurfaceV2(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceMotion, enum DIRECTION* pDirection, int checkMode);
enum DIRECTION calculDirectionCollision(enum DIRECTION direction, int zone, int checkMode);
void calculXYBalayage(SDL_Surface* pSurfaceMotion, int* xStart, int* xEnd, int* yStart, int* yEnd, int zone);
int gestionCollision(int vitesse, SDL_Surface* surfaceMap, SDL_Surface* surfaceMotion, enum DIRECTION* pDirection);
void calculOrdreBalayage(enum DIRECTION direction, int ordre[4]);

#endif