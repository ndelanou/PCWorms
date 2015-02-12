#include <SDL/SDL.h>
#include <stdio.h>
#include "AffichageGeneral.h"

int main(int argc, char** argv)
{
	int quit = 0, fullscreen = 0;
	SDL_Event event;
	SDL_Window* pWindow = NULL;

	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stdout, "�chec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return -1;
	}
	{
		/* Cr�ation de la fen�tre */
		pWindow = SDL_CreateWindow("Ma premiere application SDL2", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1080,
			600,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		if (pWindow == NULL)
		{
			fprintf(stderr, "Erreur de cr�ation de la fen�tre: %s\n", SDL_GetError());
		}
		else{

			afficheImage(pWindow);

			while (quit != 1){ /* continue tant qu'on ne clique pas sur la croix !! */
				SDL_UpdateWindowSurface(pWindow);
				while (SDL_PollEvent(&event)) /* R�cup�ration des actions de l'utilisateur */
				{
					switch (event.type)
					{
					case SDL_QUIT: /* Clic sur la croix */
						quit = 1;
						break;
					case SDL_KEYUP: /* Rel�chement d'une touche */
						if (event.key.keysym.sym == SDLK_ESCAPE){
							quit = 1;
							break;
						}
						if (event.key.keysym.sym == SDLK_KP_ENTER) /* Touche enter pour passer en plein �cran ! */
						{
							/* Alterne du mode plein �cran au mode fen�tr� */
							if (fullscreen == 0)
							{
								fullscreen = 1;
								SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);
							}
							else if (fullscreen == 1)
							{
								fullscreen = 0;
								SDL_SetWindowFullscreen(pWindow, 0);
							}
						}
						break;
					}
				}
			}
			SDL_DestroyWindow(pWindow);
		}
	}

	SDL_Quit();

	return 0;
}