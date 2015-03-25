#include "carte.h"
#include "AffichageGeneral.h"
#include "worms.h"


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

	//Creation du pointeur de Terrain
	pMapTerrainTemp = (Terrain*)malloc(sizeof(Terrain));	//Allocation m�moire pour le pointeur de Terrain
	if (pMapTerrainTemp == NULL)	//Si l'allocation s'est mal passee
	{
		printf("Probleme de lors de l'allocation memoire du terrain");
		return -1;	//Retour d'erreur
	}
	pMapTerrainTemp->imageBackground = NULL;	//Initialisation � NULL du pointeur de la texture de l'image de fond
	pMapTerrainTemp->imageMapSurface = NULL;	//Initialisation � NULL du pointeur de la surface de l'image de la map

	//Creation de la texture de l'image de fond
	pMapTerrainTemp->imageBackground = loadTexture(pRenderer, nomImageFond);	//Chargement de l'image de fond dans la texture
	if (pMapTerrainTemp->imageBackground == NULL)	//Si le chargement a �chou�
	{
		printf("Probleme de lors de la creation de la texture Background");
		destroyMap(&pMapTerrainTemp);	//Destruction du Terrain
		return -1;	//Retour d'erreur
	}

	//Creation de la surface de la map qui servira pour la collision
	pMapTerrainTemp->imageMapSurface = loadImage(nomImageMap);	//Chargement de l'image de la map dans la surface
	if (pMapTerrainTemp->imageMapSurface == NULL) //Verification qu'il n'y a pas eu d'erreur lors de l'allocation en m�moire
	{
		printf("Probleme de lors de la creation de la surface de la map");
		destroyMap(&pMapTerrainTemp);	//Destruction du Terrain
		return -1;	//Retour d'erreur
	}
	(*p_pMapTerrain) = pMapTerrainTemp; //R�cup�ration du pointeur du Terrain
	pMapTerrainTemp = NULL;	//Remise � NULL du pointeur temporaire
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
	if ((*p_pMapTerrain)->imageMapSurface != NULL)	//Si le pointeur de la surface de l'image de la map n'est pas NULL
	{
		SDL_FreeSurface((*p_pMapTerrain)->imageMapSurface);	//Destruction de la surface de l'image de la map
		(*p_pMapTerrain)->imageMapSurface = NULL;	//Remise � NULL du pointeur
	}
	free(*p_pMapTerrain);	//Liberation de la m�moire du pointeur du Terrain
	*p_pMapTerrain = NULL;	//Remise � NULL du pointeur
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
* \param[in] pDirecion, pointeur de la direction du deplacement du worms
* \return 1 = depassement de la map, 0 = pas de depassement de la map
*/
int limitMap(int mapHight, int mapWidth, SDL_Surface* pSurfaceMotion, enum DIRECTION* pDirecion)
{
	int xSurface = pSurfaceMotion->clip_rect.x;
	int ySurface = pSurfaceMotion->clip_rect.y;
	if (xSurface < 0)
	{
		pSurfaceMotion->clip_rect.x = 0;
		if (pDirecion != NULL)
			*pDirecion = LEFT;
		return 1;
	}
	else if (xSurface + pSurfaceMotion->w > mapWidth)
	{
		pSurfaceMotion->clip_rect.x = mapWidth - pSurfaceMotion->clip_rect.w;
		if (pDirecion != NULL)
			*pDirecion = RIGHT;
		return 1;
	}
	if (ySurface < 0)
	{
		pSurfaceMotion->clip_rect.y = 0;
		if (pDirecion != NULL)
			*pDirecion = UP;
		return 1;
	}
	else if (ySurface + pSurfaceMotion->h > mapHight)
	{
		pSurfaceMotion->clip_rect.y = mapHight - pSurfaceMotion->clip_rect.h + 1;
		if (pDirecion != NULL)
			*pDirecion = DOWN;
		return 1;
	}
	return 0;
}


/**
* \fn enum DIRECTION calculDirection(int x, int y, enum DIRECTION direction, int w, int h)
*
* \brief Determine la direction de la collision.
*
* \param[in] y, ordonn�e de la collision
* \param[in] x, abscisse de la collision
* \param[in] direction, direction du d�placement
* \param[in] w, largeur de l'objet
* \param[in] h, hauteur de l'objet
* \param[in] retournement, variable indiquant s'il y a eu retournement du worms
* \return DIRECTION, direction de la collision
*/

enum DIRECTION calculDirectionCollision(int x, int y, enum DIRECTION direction, int w, int h, int retournement)
{
	if ((direction == UPRIGHT || direction == UPLEFT) && !retournement)
	{
		if ((x < 2 * w / 10) || (x >= 8 * w / 10))
			return direction;
		if (y > 2 * h / 3)
			return DOWN;
		else return UP;
	}
	else if (direction == RIGHT || direction == LEFT)
	{
		if (!retournement)
		{
			if (y <= (7 * h / 8))
				return direction;
			else return DOWN;
		}
		else
		{
			if (x > (w / 2))
				return RIGHT;
			else return  LEFT;
		}
	}
	else if ((direction == DRIGHT || direction == DLEFT))
	{
		if (x >= (3 * w / 11) && x <= (8 * w / 11) && (y > h / 2))
			return DOWN;
		else if (x < w / 2)
			return DLEFT;
		else if (x > w / 2)
			return DRIGHT;
		else return direction;
	}
	else if (direction == UP)
	{
		if ((x < w / 2) && (y > 5 * h / 8))
			return DLEFT;
		else return direction;
	}
	else return direction;
}








//////////////////////////////////////////////////////////////////////////////////////////
/////////////////                                                        /////////////////
/////////////////               Manipulation des pixels                  /////////////////
/////////////////                                                        /////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/**
* \fn Uint32 ReadPixel(SDL_Surface* pSurface, int x, int y)
* \brief Lit un pixel aux coordonnees x et y d'une surface.
*
* \param[in] pSurface, surface dans laquelle on lit le pixel
* \param[in] x, abscisse dans la surface
* \param[in] y, ordonne dans la surface
* \returns Uint32, pixel lu aux coordonnees contenant les 4 canaux (RGBA)
* \remarks Faire attention que x et y soient bien compris dans la surface.
*/

Uint32 ReadPixel(SDL_Surface* pSurface, int x, int y)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)pSurface->pixels;
	//Get the requested pixel
	return pixels[(y * pSurface->w) + x];
}


/**
* \fn void DrawPixel(SDL_Surface* pSurface, int x, int y, Uint32 pixelToWrite)
* \brief Ecrit un pixel aux coordonnees x et y d'une surface.
*
* \param[in] pSurface, surface dans laquelle on ecrit le pixel
* \param[in] x, abscisse dans la surface
* \param[in] y, ordonne dans la surface
* \param[in] pixelToWrite, pixel a ecrire
*/
void DrawPixel(SDL_Surface* pSurface, int x, int y, Uint32 pixelToWrite)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)pSurface->pixels;

	//Set the pixel
	if ((x >= pSurface->clip_rect.x) && (x <= (pSurface->clip_rect.x + pSurface->w)) && (y >= pSurface->clip_rect.y) && (y <= (pSurface->clip_rect.y + pSurface->h)))
		pixels[(y * pSurface->w) + x] = pixelToWrite;
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


/**
* \fn int detectionCollisionSurface(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceMotion)
* \brief Detecte s'il y a collision entre deux surfaces.
*
* \param[in] pSurfaceMap, pointeur vers la surface de la map
* \param[in] pSurfaceMotion, pointeur vers la surface en mouvement dans la map
* \returns int, indicateur de collision : 1 = collision, 0 sinon
*/
int detectionCollisionSurface(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceMotion)
{
	//Variables d'acquisitions
	Uint32 pixelS1 = 0;	//Variable stockant le pixel en cours de lecture de la surface de la map
	Uint8 rS1 = 0, gS1 = 0, bS1 = 0, aS1 = 0;	//Variables stockant les informations sur les couleurs du pixel lu de la surface de la map
	Uint32 pixelS2 = 0;	//Variable stockant le pixel en cours de lecture de la surface en mouvement
	Uint8 rS2 = 0, gS2 = 0, bS2 = 0, aS2 = 0;	//Variables stockant les informations sur les couleurs du pixel lu de la surface en mouvement
	int offset_xS2 = pSurfaceMotion->clip_rect.x;	//Offset en x de la surface en mouvement dans la map
	int offset_yS2 = pSurfaceMotion->clip_rect.y;	//Offset en y de la surface en mouvement dans la map
	SDL_PixelFormat* formatS1 = pSurfaceMap->format;	//Pointeur du format de pixels de la surface de la map
	SDL_PixelFormat* formatS2 = pSurfaceMotion->format;	//Pointeur du format de pixels de la surface en mouvement
	//Variables de balayage
	int x = 0, y = 0;
	int xStart = pSurfaceMotion->clip_rect.x, xEnd = pSurfaceMotion->clip_rect.x + pSurfaceMotion->clip_rect.w;	//Variables de d�but, de fin et d'incr�ment du balayage des x
	int yStart = pSurfaceMotion->clip_rect.y, yEnd = pSurfaceMotion->clip_rect.y + pSurfaceMotion->clip_rect.h;	//Variables de d�but, de fin et d'incr�ment du balayage des y
	//Varable de collision
	int collision = 0;	//Booleen de collision, 0 = pas de collision, 1 = collision
	//Test des limites de la map et de la fenetre
	if (limitMap(pSurfaceMap->h, pSurfaceMap->w, pSurfaceMotion, NULL))	//Detection d'un d�passement de la map
		return 1;

	for (y = yStart; (y < yEnd) && (collision == 0); y++)
	{
		for (x = xStart; (x < xEnd) && (collision == 0); x++)
		{
			//Acquisition pixel surface 1
			pixelS1 = ReadPixel(pSurfaceMap, x, y);	//Lecture du pixel de la map
			SDL_GetRGBA(pixelS1, formatS1, &rS1, &gS1, &bS1, &aS1);	//Informations sur les couleurs du pixel de la surface de la map
			//Acquisition pixel surface 2
			pixelS2 = ReadPixel(pSurfaceMotion, x - offset_xS2, y - offset_yS2);	//Lecture du pixel de la surface en mouvement
			SDL_GetRGBA(pixelS2, formatS2, &rS2, &gS2, &bS2, &aS2);	//Informations sur les couleurs du pixel de la surface en mouvement
			//D�termination de la collision
			if (aS1 != 255 || aS2 != 255)	//Si le pixel de la surface de la map ou le pixel de la surface en mouvement est transparent
				collision = 0;	//Collision = 0 -> pas de collision
			else	//Au moins l'un des pixels n'est pas transparent
			{
				collision = 1;	//Collision = 0 -> pas de collision
			}
		}
	}
	formatS1 = NULL;	//Remise � 0 des pointeurs de format
	formatS2 = NULL;	//Remise � 0 des pointeurs de format
	return collision;
}


/**
* \fn int detectionCollisionSurfaceV2(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceMotion, enum DIRECTION* pDirection, int retournement)
* \brief Detecte s'il y a collision entre deux surfaces selon le sens de d�placement du worms.
*
* \param[in] pSurfaceMap, pointeur vers la surface de la map
* \param[in] pSurfaceMotion, pointeur vers la surface en mouvement dans la map
* \param[in] pDirection, pointeur de la direction du deplacement du worms
* \param[in] retournement, variable indiquant s'il y a eu retournement du worms
* \returns int, indicateur de collision : 1 = collision, 0 sinon
*/
int detectionCollisionSurfaceV2(SDL_Surface* pSurfaceMap, SDL_Surface* pSurfaceMotion, enum DIRECTION* pDirection, int retournement)
{
	//Variables d'acquisitions
	Uint32 pixelS1 = 0;	//Variable stockant le pixel en cours de lecture de la surface de la map
	Uint8 rS1 = 0, gS1 = 0, bS1 = 0, aS1 = 0;	//Variables stockant les informations sur les couleurs du pixel lu de la surface de la map
	Uint32 pixelS2 = 0;	//Variable stockant le pixel en cours de lecture de la surface en mouvement
	Uint8 rS2 = 0, gS2 = 0, bS2 = 0, aS2 = 0;	//Variables stockant les informations sur les couleurs du pixel lu de la surface en mouvement
	int offset_xS2 = pSurfaceMotion->clip_rect.x;	//Offset en x de la surface en mouvement dans la map
	int offset_yS2 = pSurfaceMotion->clip_rect.y;	//Offset en y de la surface en mouvement dans la map
	SDL_PixelFormat* formatS1 = pSurfaceMap->format;	//Pointeur du format de pixels de la surface de la map
	SDL_PixelFormat* formatS2 = pSurfaceMotion->format;	//Pointeur du format de pixels de la surface en mouvement
	//Variables de balayage
	int x = 0, y = 0;	//Variables de balayage des x, y
	int xStart = pSurfaceMotion->clip_rect.x, xEnd = pSurfaceMotion->clip_rect.x + pSurfaceMotion->clip_rect.w, xInc = 1;	//Variables de d�but, de fin et d'incr�ment du balayage des x
	int yStart = pSurfaceMotion->clip_rect.y, yEnd = pSurfaceMotion->clip_rect.y + pSurfaceMotion->clip_rect.h, yInc = 1;	//Variables de d�but, de fin et d'incr�ment du balayage des y
	//Variable de collision
	int collision = 0;	//Booleen de collision, 0 = pas de collision, 1 = collision
	//Test des limites de la map et de la fenetre
	if (limitMap(pSurfaceMap->h, pSurfaceMap->w, pSurfaceMotion, pDirection))	//Detection d'un d�passement de la map
		return 1;
	//D�termination de yStart, yEnd, xStart et xEnd
	calculXYBalayage(pSurfaceMotion, *pDirection, &xStart, &xEnd, &yStart, &yEnd);	//Calcul des valeurs de balayage des boucles for pour optimiser la vitesse de traitement
	//Calcul de la collision
	for (y = yStart; (y < yEnd) && (collision == 0); y += yInc)
	{
		for (x = xStart; (x < xEnd) && (collision == 0); x += xInc)
		{
			//Acquisition des pixels des surfaces 1 et 2
			pixelS1 = ReadPixel(pSurfaceMap, MY_ABS(x), MY_ABS(y));	//Lecture du pixel de la map
			pixelS2 = ReadPixel(pSurfaceMotion, MY_ABS(x) - offset_xS2, MY_ABS(y) - offset_yS2);	//Lecture du pixel de la surface en mouvement
			//R�cup�ration des composantes colorim�triques
			SDL_GetRGBA(pixelS1, formatS1, &rS1, &gS1, &bS1, &aS1);	//Informations sur les couleurs du pixel de la surface de la map
			SDL_GetRGBA(pixelS2, formatS2, &rS2, &gS2, &bS2, &aS2);	//Informations sur les couleurs du pixel de la surface en mouvement
			//D�termination de la collision
			if (aS1 != 255 || aS2 != 255)	//Si le pixel de la surface de la map ou le pixel de la surface en mouvement est transparent
				collision = 0;	//Collision = 0 -> pas de collision
			else	//Au moins l'un des pixels n'est pas transparent
			{
				collision = 1;	//Collision = 0 -> pas de collision
				*pDirection = calculDirectionCollision(MY_ABS(x) - offset_xS2, MY_ABS(y) - offset_yS2, *pDirection, pSurfaceMotion->w, pSurfaceMotion->h, retournement);	//Calcul de la direction de la collision pour affiner le traitement
			}
		}
	}
	formatS1 = NULL;	//Remise � 0 des pointeurs de format
	formatS2 = NULL;	//Remise � 0 des pointeurs de format
	return collision;
}

/**
* \fn void calculXYBalayage(SDL_Surface* pSurfaceMotion, enum DIRECTION dir, int* xStart, int* xEnd, int* yStart, int* yEnd)
* \brief Calcul les valeurs de debut et de fin pour X et Y afin d'optimiser la detection de collision.
*
* \param[in] psurfaceMotion, surface en deplacement
* \param[in] direction, direction du deplacement du worms
* \param[in] xStart, pointeur vers la variable xStart, debut du balayage en x
* \param[in] xEnd, pointeur vers la variable xEnd, fin du balayage en x
* \param[in] yStart, pointeur vers la variable yStart, debut du balayage en y
* \param[in] yEnd, pointeur vers la variable yEnd, fin du balayage en y
* \returns void
*/
void calculXYBalayage(SDL_Surface* pSurfaceMotion, enum DIRECTION direction, int* xStart, int* xEnd, int* yStart, int* yEnd)
{
	//D�termination de yStart, yEnd
	if (direction == DOWN)	//Si la surface se dirige vers le bas
	{
		*yStart = -(pSurfaceMotion->clip_rect.y + pSurfaceMotion->clip_rect.h) + 1;	//On balaye en partant du bas, on prends la valeur n�gative pour conserver une incr�mentation positive et une boucle identique
		*yEnd = -(2 * pSurfaceMotion->clip_rect.h / 3 + pSurfaceMotion->clip_rect.y) + 1;	//On arr�te le balayage au tiers haut, pour une detection vers le bas, c'est suffisant
	}
	//D�termination de xStart, xEnd
	else if (direction == UPRIGHT)	//Si la surface se dirige en diagonale haute droite
	{
		*xStart = -(pSurfaceMotion->clip_rect.x + pSurfaceMotion->clip_rect.w) + 1;
		*xEnd = -(pSurfaceMotion->clip_rect.x) + 1;
		*yEnd = pSurfaceMotion->clip_rect.y + pSurfaceMotion->clip_rect.h;
	}
	else if (direction == UPLEFT)	//Si la surface se dirige en diagonale haute gauche
	{
		*yEnd = pSurfaceMotion->clip_rect.y + pSurfaceMotion->clip_rect.h;
	}
	else if (direction == RIGHT)	//Si la surface se dirige vers la droite
	{
		*xStart = -(pSurfaceMotion->clip_rect.x + pSurfaceMotion->clip_rect.w) + 1;	//On d�marre le balayage � droite
		*xEnd = -(pSurfaceMotion->clip_rect.x + pSurfaceMotion->clip_rect.w / 2) + 1;	//On arr�te le balayage � la moiti� de la surface, pour une d�tection de c�t�, c'est suffisant
	}
	else if (direction == LEFT)	//Si la surface se dirige vers la gauche
	{
		*xEnd = (pSurfaceMotion->clip_rect.x + pSurfaceMotion->clip_rect.w / 2);	//On arr�te le balayage � la moiti� de la surface, pour une d�tection de c�t�, c'est suffisant
	}
	else if (direction == DRIGHT)	//Si la surface se dirige en diagonale basse droite
	{
		*yStart = -(pSurfaceMotion->clip_rect.y + pSurfaceMotion->clip_rect.h) + 1;	//On d�marre le balayage en bas
		*yEnd = -(2 * pSurfaceMotion->clip_rect.h / 3 + pSurfaceMotion->clip_rect.y) + 1;	//On s'arr�te au tiers haut
		*xStart = -(pSurfaceMotion->clip_rect.x + pSurfaceMotion->clip_rect.w) + 1;	//On d�marre le balayage � droite
		*xEnd = -(pSurfaceMotion->clip_rect.x) + 1;
	}
	else if (direction == DLEFT)	//Si la surface se dirige en diagonale basse gauche
	{
		*yStart = -(pSurfaceMotion->clip_rect.y + pSurfaceMotion->clip_rect.h) + 1;	//On d�marre le balayage en bas
		*yEnd = -(2 * pSurfaceMotion->clip_rect.h / 3 + pSurfaceMotion->clip_rect.y) + 1;	//On s'arr�te au tiers haut
		*xEnd = (pSurfaceMotion->clip_rect.x + pSurfaceMotion->clip_rect.w);
	}
}


/**
* \fn int gestionCollision(int vitesse, SDL_Surface* surfaceMap, SDL_Surface* surfaceMotion, enum DIRECTION* pDirection, int retournement)
* \brief replace le worms en cas de collision.
*
* \param[in] vitesse, vitesse de deplacement du worms, sert pour le replacement
* \param[in] surfaceMotion, surface en deplacement
* \param[in] surfaceMap, surface de la map
* \param[in] pDirection, direction du deplacement du worms, peut etre modifie par la fonction
* \param[in] retournement, variable indiquant s'il y a eu retournement du worms
* \returns int collision, indique s'il y a eu collision
*/
int gestionCollision(int vitesse, SDL_Surface* surfaceMap, SDL_Surface* surfaceMotion, enum DIRECTION* pDirection, int retournement)
{
	int t = 0;
	int collision = 0;
	while (detectionCollisionSurfaceV2(surfaceMap, surfaceMotion, pDirection, retournement) && t < 60)	//Tant qu'on d�tecte une collision et que la boucle ne s'est pas effectu�e plus de 60 fois (�vite des boucles infinies)
	{
		switch (*pDirection)	//Switch de la valeur de derriere le pointeur pDirection, indiquant le sens de d�tection de la collision
		{
		case RIGHT:	//Cas d'une d�tection � droite
			surfaceMotion->clip_rect.x -= vitesse;
			break;
		case LEFT:	//Cas d'une d�tection � gauche
			surfaceMotion->clip_rect.x += vitesse;
			break;
		case DOWN:	//Cas d'une d�tection en bas
			surfaceMotion->clip_rect.y -= vitesse;
			break;
		case UP:	//Cas d'une d�tection en hauteur
			surfaceMotion->clip_rect.y += vitesse;
			break;
		case UPRIGHT:	//Cas d'une d�tection en diagonale haute droite
			surfaceMotion->clip_rect.x -= vitesse;
			surfaceMotion->clip_rect.y += vitesse;
			break;
		case UPLEFT:	//Cas d'une d�tection en diagonale haute gauche
			surfaceMotion->clip_rect.x += vitesse;
			surfaceMotion->clip_rect.y += vitesse;
			break;
		case DRIGHT:	//Cas d'une d�tection en diagonale basse droite
			surfaceMotion->clip_rect.x -= vitesse;
			surfaceMotion->clip_rect.y -= vitesse;
			break;
		case DLEFT:	//Cas d'une d�tection en diagonale basse gauche
			surfaceMotion->clip_rect.x += vitesse;
			surfaceMotion->clip_rect.y -= vitesse;
			break;
		default:
			break;
		}
		t++;	//Incr�mentation du limiteur de boucle
		collision = 1;	//Mise � 1 de l'indicateur de collision
	}
	return collision;	//Return l'indice de collision, 0 = pas de collision, 1 = collision
}