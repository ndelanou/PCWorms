#ifndef LIBRARIES_H
#define LIBRARIES_H

/*Biblioth�ques de base*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

/*Biblioth�ques suppl�mentaires*/
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <math.h>


//structures globales
#define MY_ABS(a) ((a) < 0 ? (-a) : (a))
#define pi 3.1415
typedef struct{		//structure Point
	int x;
	int y;
}Point;

typedef struct{ //structure Curseur
	Point before;
	Point now;
}Cursor;

enum DIRECTION {RIGHT = 0, LEFT = 1, DOWN = 2, UP = 3, NONE = 5 };

typedef struct{		//structure g�rant les diff�rents inputs
	char jump;	//touche de saut
	char jumpOnGoing;	//indique qu'un saut est en cours et d�sactive les touches de direction
	char bend;	//touche pour s'accroupir
	char menu;	//touche de menu principal
	char rclick;		//click droite de la souris
	enum DIRECTION direction;	//stocke la direction du d�placement du worms
	char lclick;	//click gauche de la souris
	char quit;	//quitte le programme
	char weaponTab;
	char wheelUp; //zoomIn
	char wheelDown; //zoomOut
	char raffraichissement;
	char windowResized;
	char acceleration;
	char bombe;
	Cursor cursor; //cursor avec position actuelle et pr�c�dente
}Input;


#endif