#include "AffichageGeneral.h" /* Inclus la SDL.h */

int mainFenetre2()
{
	int quit = 0, fullscreen = 0, i = 0, x1 = 0, y1 = 0, w1, h1;
	SDL_Event event;
	SDL_Renderer* renderer = NULL; //d�claration du renderer
	SDL_Window* pWindow = NULL;
	SDL_Rect rectangle;

	/* Initialisation simple */
	if (SDL_VideoInit(NULL) < 0)
	{
		printf("�chec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return -1;
	}
	else {
		/* Cr�ation de la fen�tre */
		pWindow = creerFenetre(1080, 600, "KaamWorms");
		if (pWindow == NULL)
		{
			SDL_Quit();
			return -1;
		}
		renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL)//gestion des erreurs
		{
			printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
			return -1;
		}
		SDL_SetRenderDrawColor(renderer, 255, 40, 50, 200); //r�glage des couleurs de dessin
		SDL_GetWindowPosition(pWindow, &x1, &y1);
		SDL_GetWindowSize(pWindow, &w1, &h1);
		rectangle.h = 300;
		rectangle.w = 200;
		rectangle.x = 0;
		rectangle.y = 0;
		for (i = 0; i <= (w1-rectangle.w)/10; i++)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0,0, 255); //r�glage des couleurs de dessin
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 255, 40, 50, 255); //r�glage des couleurs de dessin
			if (SDL_RenderDrawRect(renderer, &rectangle) < 0) //dessin d'une ligne
			{
				printf("Erreur lors de la creation de la ligne : %s", SDL_GetError());
				return -1;
			}
			rectangle.x = 10 * i;
			SDL_RenderPresent(renderer); //actualisation du renderer
			SDL_Delay(100);
		}
		SDL_Delay(3000);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(pWindow);
		SDL_Quit();
	}
}

int mainFenetre(){

	int quit = 0, fullscreen = 0;
	SDL_Event event;
	SDL_Window* pWindow = NULL;

	/* Initialisation simple */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("�chec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return -1;
	}
	{
		/* Cr�ation de la fen�tre */
		pWindow = creerFenetre(1080, 600, "KaamWorms");
		/*Chargement image*/
		SDL_Surface * wormsLeft = loadImage("../assets/pictures/worms_left.png");
		SDL_Surface * wormsRight = loadImage("../assets/pictures/worms_right.png");
		SDL_SetWindowIcon(pWindow, wormsRight);

		if (pWindow != NULL){
			while (quit != 1)
			{
				SDL_PumpEvents(); // On demande � la SDL de mettre � jour les �tats sur les p�riph�riques

				// Clavier
				{
					Uint8 * pKeyStates = SDL_GetKeyboardState(NULL);
					if (pKeyStates[SDL_SCANCODE_ESCAPE])
					{
						quit = 1;
					}
					SDL_Keymod mod = SDL_GetModState();
					if (mod != KMOD_NONE)
					{
						printf("Vous avez appuy� sur une touche sp�ciale : %d\n", mod);
					}
					if (pKeyStates[SDL_SCANCODE_LEFT]){
						afficheImage(pWindow, wormsLeft);//affichage du worms si arrow left
					}
					if (pKeyStates[SDL_SCANCODE_RIGHT]){
						afficheImage(pWindow, wormsRight);// affichage du worms si arrow right
					}
				}
				printf("\n");
				// Souris
				{
					int x = 0;
					int y = 0;
					Uint32 boutons = SDL_GetMouseState(&x, &y);

					printf("Position de la souris : %d;%d\n", x, y);
					printf("Bouton de la souris : %d\n", boutons);

					SDL_GetRelativeMouseState(&x, &y);
					printf("D�placement de la souris : %d;%d\n", x, y);
				}
				printf("\n");

				while (SDL_PollEvent(&event)) /* R�cup�ration des actions de l'utilisateur */
				{
					switch (event.type)
					{
					case SDL_QUIT: /* Clic sur la croix */
						quit = 1;
						break;
					case SDL_KEYUP: /* Rel�chement d'une touche */
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
					}

					SDL_UpdateWindowSurface(pWindow);
				}
			}
			SDL_DestroyWindow(pWindow);
		}
		SDL_FreeSurface(wormsLeft);
		SDL_FreeSurface(wormsRight);
		SDL_Quit();
	}
}


//Fonction de cr�ation de fen�tre
SDL_Window * creerFenetre(const int w, const int h, const char * nom){
	SDL_Window * pWindow = NULL;
	pWindow = SDL_CreateWindow(nom,	//nom de la fen�tre
		SDL_WINDOWPOS_CENTERED, //position en x de la fen�tre
		SDL_WINDOWPOS_CENTERED,	//position en y de la fen�tre
		w,	//largeur de la fen�tre
		h,	//hauteur de la fen�tre
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);	//propri�t�s suppl�mentaires de la fen�tre
	if (pWindow == NULL)
	{
		fprintf(stderr, "Erreur de cr�ation de la fen�tre: %s\n", SDL_GetError());
		return NULL;
	}
	else return pWindow;
}

int afficheImage(SDL_Window *pWindow, SDL_Surface * image)
{
	SDL_Rect dest = { 1080 / 2 - image->w / 2, 600 / 2 - image->h / 2, 50, 50 };
	SDL_BlitSurface(image, NULL, SDL_GetWindowSurface(pWindow), &dest);
}


//Fonction de cr�ation de surface
SDL_Surface * loadImage(const char * file){
	SDL_Surface* image = IMG_Load(file);
	if (image == NULL)
	{
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		return NULL;
	};
	return image;
}