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
int initialisionTerrain(Terrain ** map, SDL_Renderer * pRenderer, const char * file, const char * file2);
void destroyMap(Terrain** map);	//d�truit un terrain


/*Fonctions diverses*/
int limitMap(int mapHight, int mapWidth, SDL_Surface* pSurface, enum DIRECTION* dir); //D�termine si un objet est hors map et le replace si il faut


/*Manipulation des pixels*/
Uint32 ReadPixel(SDL_Surface *surface, int x, int y);
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

/*D�tection et gestion des collisions*/
int detectionCollisionRect(SDL_Renderer* pRenderer, SDL_Surface* pSurfaceMap, int* xE, int* yE, SDL_Rect* pRect);
int detectionCollisionSurface(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceMotion);
int detectionCollisionSurfaceV2(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceMotion, enum DIRECTION* dir, int retournement);
enum DIRECTION calculDirectionCollision(int x, int y, enum DIRECTION impulse, int w, int h, int retournement);
void calculXYBalayage(SDL_Surface* pSurfaceMotion, enum DIRECTION dir, int* xStart, int* xEnd, int* yStart, int* yEnd);
int gestionCollision(int vitesse, SDL_Surface* surfaceMotion, SDL_Surface* surfaceMap, enum DIRECTION *dir, int retournement);

#endif