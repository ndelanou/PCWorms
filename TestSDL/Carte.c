#include "carte.h"
#include "AffichageGeneral.h"
#include "worms.h"
#include "my_stdrFct.h"


//////////////////////////////////////////////////////////////////////////////////////////
/////////////////                                                        /////////////////
/////////////////                  Gestion du terrain                    /////////////////
/////////////////                                                        /////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/**
* \fn int initialisionTerrain(Terrain** p_pMapTerrain, SDL_Renderer * pRenderer, const char * nomImageFond, const char * nomImageMap)
* \brief Initialise un terrain avec son image de fond et l'image de la map.
*
* \param[in] p_pMapTerrain, adresse du pointeur de structure Terrain a initialiser
* \param[in] pRenderer, pointeur du renderer dans lequel le Terrain est a initialiser
* \param[in] nomImageFond, nom du fichier de l'image de fond
* \param[in] nomImageMap, nom du fichier de l'image de la map
* \returns int, Indicateur de reussite de la fonction : 1 = succes, -1 = echec
*/
int initialisionTerrain(Terrain** p_pMapTerrain, SDL_Renderer * pRenderer, const char * nomImageFond, const char * nomImageMap)
{
	Terrain * pMapTerrainTemp = NULL;	//Pointeur du Terrain temporaire

	fprintf(logFile, "initialisationTerrain : START :\n\n");
	//Creation du pointeur de Terrain
	pMapTerrainTemp = (Terrain*)malloc(sizeof(Terrain));	//Allocation m�moire pour le pointeur de Terrain
	if (pMapTerrainTemp == NULL)	//Si l'allocation s'est mal passee
	{
		fprintf(logFile, "initialisationTerrain : FAILURE, allocation memoire de pMapTerrainTemp.\n\n");
		return -1;	//Retour d'erreur
	}
	pMapTerrainTemp->imageBackground = NULL;	//Initialisation � NULL du pointeur de la texture de l'image de fond
	pMapTerrainTemp->collisionMapSurface = NULL;	//Initialisation � NULL du pointeur de la surface de l'image de la map

	//Creation de la texture de l'image de fond
	pMapTerrainTemp->imageBackground = loadTexture(pRenderer, nomImageFond);	//Chargement de l'image de fond dans la texture
	if (pMapTerrainTemp->imageBackground == NULL)	//Si le chargement a �chou�
	{
		fprintf(logFile, "initialisationTerrain : FAILURE, loadTexture : imageBackground.\n\n");
		destroyMap(&pMapTerrainTemp);	//Destruction du Terrain
		return -1;	//Retour d'erreur
	}

	//Creation de la surface de la map qui servira pour la collision
	pMapTerrainTemp->collisionMapSurface = loadImage(nomImageMap);	//Chargement de l'image de la map dans la surface
	if (pMapTerrainTemp->collisionMapSurface == NULL) //Verification qu'il n'y a pas eu d'erreur lors de l'allocation en m�moire
	{
		fprintf(logFile, "initialisationTerrain : FAILURE, loadImage : collisionMapSurface.\n\n");
		destroyMap(&pMapTerrainTemp);	//Destruction du Terrain
		return -1;	//Retour d'erreur
	}
	pMapTerrainTemp->globalMapSurface = SDL_CreateRGBSurface(pMapTerrainTemp->collisionMapSurface->flags,
		pMapTerrainTemp->collisionMapSurface->w, pMapTerrainTemp->collisionMapSurface->h, 32, RMASK, GMASK, BMASK, AMASK);
	if (pMapTerrainTemp->globalMapSurface == NULL) //Verification qu'il n'y a pas eu d'erreur lors de l'allocation en m�moire
	{
		fprintf(logFile, "initialisationTerrain : FAILURE, createRGBsurface : %s.\n\n", SDL_GetError());
		destroyMap(&pMapTerrainTemp);	//Destruction du Terrain
		return -1;	//Retour d'erreur
	}
	memcpy(pMapTerrainTemp->globalMapSurface->pixels, pMapTerrainTemp->collisionMapSurface->pixels, pMapTerrainTemp->collisionMapSurface->h*pMapTerrainTemp->collisionMapSurface->w*sizeof(Uint32));
	(*p_pMapTerrain) = pMapTerrainTemp; //R�cup�ration du pointeur du Terrain
	pMapTerrainTemp = NULL;	//Remise � NULL du pointeur temporaire
	fprintf(logFile, "\ninitialisationTerrain : SUCCESS.\n\n");
	return 1;	//Retour sans erreur
}

/**
* \fn void destroyMap(Terrain** p_pMapTerrain)
* \brief D�truit une structure Terrain et remet son pointeur � NULL.
*
* \param[in] p_pMapTerrain, adresse du pointeur de la structure du Terrain � d�truire.
*/
void destroyMap(Terrain** p_pMapTerrain)
{
	if ((*p_pMapTerrain)->imageBackground != NULL)	//Si le pointeur de la texture de l'image de fond n'est pas NULL
	{
		SDL_DestroyTexture((*p_pMapTerrain)->imageBackground);	//Destruction de la texture de l'image de fond
		(*p_pMapTerrain)->imageBackground = NULL;	//Remise � NULL du pointeur
	}
	if ((*p_pMapTerrain)->collisionMapSurface != NULL)	//Si le pointeur de la surface de l'image de la map n'est pas NULL
	{
		SDL_FreeSurface((*p_pMapTerrain)->collisionMapSurface);	//Destruction de la surface de l'image de la map
		(*p_pMapTerrain)->collisionMapSurface = NULL;	//Remise � NULL du pointeur
	}
	if ((*p_pMapTerrain)->globalMapSurface != NULL)	//Si le pointeur de la surface de l'image de la map n'est pas NULL
	{
		SDL_FreeSurface((*p_pMapTerrain)->globalMapSurface);	//Destruction de la surface de l'image de la map
		(*p_pMapTerrain)->globalMapSurface = NULL;	//Remise � NULL du pointeur
	}
	free(*p_pMapTerrain);	//Liberation de la m�moire du pointeur du Terrain
	*p_pMapTerrain = NULL;	//Remise � NULL du pointeur
	fprintf(logFile, "destroyMap : DONE.\n");
}









//////////////////////////////////////////////////////////////////////////////////////////
/////////////////                                                        /////////////////
/////////////////                  Fonctions diverses                    /////////////////
/////////////////                                                        /////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/**
* \fn int limitMap(unsigned int mapHight, unsigned int mapWidth, SDL_Surface* pSurface, enum DIRECTION* dir)
* \brief Test les limites de la map avec l'objet en mouvement.
*
* \param[in] mapHight, hauteur de la map
* \param[in] mapWidth, largeur de la map
* \param[in] pSurfaceMotion, surface de l'objet en mouvement
* \param[in] pDirecion, pointeur de la direction du deplacement du worms, NULL si non utile
* \return 1 = depassement de la map, 0 = pas de depassement de la map
*/
int limitMap(int mapHight, int mapWidth, SDL_Surface* pSurfaceMotion, enum DIRECTION* pDirecion)
{
	int xSurface = pSurfaceMotion->clip_rect.x;	//stockage de la valeur x de la surface en d�placement pour simplifier la lecture
	int ySurface = pSurfaceMotion->clip_rect.y;	//stockage de la valeur y de la surface en d�placement pour simplifier la lecture
	if (xSurface < 0)	//Si la surface sors de la map par la gauche
	{
		pSurfaceMotion->clip_rect.x = 0;	//Set de la valeur de x � 0 pour coller � la map
		if (pDirecion != NULL)	//Si le pointeur de direction n'est pas NULL
			*pDirecion = LEFT;	//Set de la direction � gauche
		return 1;	//return 1 = d�passement de la map, 0 = pas de d�passement
	}
	else if (xSurface + pSurfaceMotion->w > mapWidth)	//Si la surface sors de la map par la droite
	{
		pSurfaceMotion->clip_rect.x = mapWidth - pSurfaceMotion->clip_rect.w;	//Set de la valeur de x � la largeur de la map - la largeur de l'objet pour coller � la map
		if (pDirecion != NULL)	//Si le pointeur de direction n'est pas NULL
			*pDirecion = RIGHT;	//Set de la direction � droite
		return 1;	//return 1 = d�passement de la map, 0 = pas de d�passement
	}
	if (ySurface < 0)	//Si la surface sors de la map par le dessus
	{
		pSurfaceMotion->clip_rect.y = 0;	//Set de la valeur de y pour coller au haut de la map
		if (pDirecion != NULL)	//Si le pointeur de direction n'est pas NULL
			*pDirecion = UP;	//Set de la direction � haut
		return 1;	//return 1 = d�passement de la map, 0 = pas de d�passement
	}
	else if (ySurface + pSurfaceMotion->h > mapHight)	//Si la surface sors de la map par le dessous
	{
		pSurfaceMotion->clip_rect.y = mapHight - pSurfaceMotion->clip_rect.h + 1;	//Set de la valeur de y � hauteur de la map - hauteur de l'objet pour coller � la map
		if (pDirecion != NULL)	//Si le pointeur de direction n'est pas NULL
			*pDirecion = DOWN;	//Set de la direction � bas
		return 1;	//return 1 = d�passement de la map, 0 = pas de d�passement
	}
	return 0;	//return 1 = d�passement de la map, 0 = pas de d�passement
}


/**
* \fn enum DIRECTION calculDirection(enum DIRECTION direction, int zone, int checkMode)
*
* \brief Determine la direction de la collision.
*
* \param[in] direction, direction du d�placement
* \param[in] zone, zone de la collision
* \param[in] checkMode, mode pour le test de deplacement (0 par defaut)
* \return DIRECTION, direction de la collision
*/

enum DIRECTION calculDirectionCollision(enum DIRECTION direction, int zone, int checkMode)
{
	if (direction == RIGHT || direction == LEFT)
	{
		switch (zone)
		{
		case 7:
			return UP;
		case 8:
			return DOWN;
		default:
			break;
		}
	}
	if (direction == UPRIGHT)
	{
		/*if (zone == 1)
			return UPLEFT;
			else if (zone == 2)
			return UP;*/
	}
	else if (direction == UPLEFT)
	{

	}
	if (zone == 3 && direction == DRIGHT)
		return DOWN;
	else if (zone == 4 && direction == DLEFT)
		return DOWN;
	if (checkMode && direction == UP && zone == 8)
		return DOWN;
	return direction;
}









//////////////////////////////////////////////////////////////////////////////////////////
/////////////////                                                        /////////////////
/////////////////         Fonctions de d�tection de collision            /////////////////
/////////////////                                                        /////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/**
* \fn int detectionCollisionRect(SDL_Renderer* pRenderer, SDL_Surface* pSurfaceMap, int* xE, int* yE, SDL_Rect* pRect)
* \brief Detecte s'il y a collision entre un rectangle et une surface.
*
* \param[in] pRenderer, pointeur vers le renderer de la fenetre
* \param[in] pSurfaceMap, pointeur vers la surface de la surface a tester
* \param[in] xE, pointeur vers la variable contenant l'abscisse de la collision
* \param[in] yE, pointeur vers la variable contenant l'ordonne de la collision
* \param[in] pRect, pointeur vers le rectangle a tester
* \returns int, indicateur de collision : 1 = collision, 0 sinon
*/
int detectionCollisionRect(SDL_Renderer* pRenderer, SDL_Surface* pSurfaceMap, int* xE, int* yE, SDL_Rect* pRect)
{
	SDL_Rect rect = { 0, 0, 0, 0 };
	Uint32 p = ReadPixel(pSurfaceMap, 0, 0);
	Uint8 r = 0, g = 0, b = 0, a = 0;
	int x = 0, y = 0, w = 0, h = 0;
	rect = *pRect;
	int collision = 0;
	SDL_GetRendererOutputSize(pRenderer, &w, &h);
	if ((w - rect.x <= rect.w) || (rect.x <= 0) || (rect.y <= 0) || (h - rect.y) <= rect.h)
	{
		return 1;
	}
	for (y = rect.y; (y <= rect.h + rect.y) && (collision == 0); y++)
	{
		if (y == rect.y || y == (rect.h + rect.y))
		{
			for (x = rect.x; (x <= rect.x + rect.w) && (collision == 0); x++)
			{
				p = ReadPixel(pSurfaceMap, x, y);
				SDL_GetRGBA(p, pSurfaceMap->format, &r, &g, &b, &a);
				if (a < 100) //transparence
				{
					collision = 0;
				}
				else
				{
					*xE = x;
					*yE = y;
					collision = 1;
				}
			}
		}
		else
		{
			p = ReadPixel(pSurfaceMap, rect.x, y);
			SDL_GetRGBA(p, pSurfaceMap->format, &r, &g, &b, &a);
			if (a < 100) //transparence
			{
				collision = 0;
			}
			else
			{
				*xE = rect.x + rect.w;
				*yE = y;
				collision = 1;
			}
			p = ReadPixel(pSurfaceMap, rect.x + rect.w, y);
			SDL_GetRGBA(p, pSurfaceMap->format, &r, &g, &b, &a);
			if (a < 100) //transparence
			{
				collision = 0;
			}
			else
			{
				*xE = rect.x + rect.w;
				*yE = y;
				collision = 1;
			}
		}
	}
	return collision;
}







