#include <SDL/SDL.h>

int afficheImage(SDL_Window *pWindow, SDL_Surface * image); /*TODO: r�ecrire les protos*/
void mainFenetre();
SDL_Surface * loadImage(const char * file);
SDL_Window * creerFenetre(const int x, const int y, const char * nom);