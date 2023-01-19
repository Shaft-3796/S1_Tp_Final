#include "Music.h"
#include "Settings.h"
#include "Assets.h"
#include "Common.h"

void playMusic(){
    Mix_Music *music = Mix_LoadMUS("../Assets/Audio/Space.wav");
    Mix_PlayMusic(music, -1);
}

void playSound(){
    Mix_Chunk * sound = Mix_LoadWAV("../Assets/Audio/Player_Hit.wav");
    Mix_PlayChannel(-1, sound, 0);
}