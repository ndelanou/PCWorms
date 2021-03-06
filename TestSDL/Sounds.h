#ifndef SOUND_H
#define SOUND_H

#include "Libraries.h"

/*Chemins vers les sons des bombes*/

#define MusiqueMenu "../assets/sounds/music/CuteIntro.wav"
#define MusiqueVictoire "../assets/sounds/music/ffvii.wav"
#define MusiqueInGame "../assets/sounds/music/musicInGame.wav"
#define OpenMenu "../assets/sounds/music/MenuArmes.wav"
#define SoundOver "../assets/sounds/music/MenuOver.wav"
#define MusiqueScore "../assets/sounds/music/EndMusic.wav"

//Declaration des sons armes
#define ExploMed "../assets/sounds/weapon/Explosion_medium.wav"
#define BipExplo "../assets/sounds/weapon/Bip_explosion.wav"
#define ExploSourde "../assets/sounds/weapon/Explosion_sourde.wav"
#define LancerGrenade "../assets/sounds/weapon/LancerGrenade.wav"
#define FireBullet "../assets/sounds/weapon/FireBullet.wav"

#define NBCHUNK 20
#define NBMUSIC 5

typedef struct // structure pour les chunk
{
	char *adresse;
	Mix_Chunk * ptrChunk;
}Chunk;

typedef struct // structure pour les chunk
{
	char *adresse;
	Mix_Music * ptrMusic;
}Music;

int indexTabChunk; // index de la dernière case non vide du tableau des chunks
int indexTabMusic; // index de la dernière case non vide du tableau des music
Mix_Chunk * sndFx;
Chunk chunkTab[NBCHUNK];
Music musicTab[NBMUSIC];
Mix_Music * ptrMusicMenu;


int initSDLMixer();
int loadSounds(char* file, int type);// 0 si un chunk 1 une musique
int playMusique(int validation, char * file);
int findChunkInTab(char * file);
int findMusicInTab(char * file);
int playChunk(int validation, char * file);
void cleanSounds();
#endif // !SOUND_H