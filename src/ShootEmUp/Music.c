#include "Music.h"
#include "Settings.h"
#include "Assets.h"
#include "Common.h"

void playMusic(){
    Mix_Music *music = Mix_LoadMUS("../Assets/Audio/Space.wav");
    Mix_PlayMusic(music, -1);
}

void playSound(char SoundEffect_Title[]){
    char SoundEffectPath[50] = "";
    if(strcmp(SoundEffect_Title, "Player_Hit") == 0){
        Mix_Chunk* sound = Mix_LoadWAV("../Assets/Audio/Player_Hit.wav");
        Mix_PlayChannel(-1, sound, 0);
    }
    if (strcmp(SoundEffect_Title, "Laser_Gun") == 0) {
        Mix_Chunk* sound = Mix_LoadWAV("../Assets/Audio/LaserGun.wav");
        Mix_PlayChannel(-1, sound, 0);
    }
    if (strcmp(SoundEffect_Title, "Bonus") == 0) {
        Mix_Chunk* sound = Mix_LoadWAV("../Assets/Audio/Bonus.wav");
        Mix_PlayChannel(-1, sound, 0);
    }
    if (strcmp(SoundEffect_Title, "Explosion") == 0) {
        Mix_Chunk* sound = Mix_LoadWAV("../Assets/Audio/Explosion.wav");
        Mix_PlayChannel(-1, sound, 0);
    }
    if (strcmp(SoundEffect_Title, "Death_Player") == 0) {
        Mix_Chunk* sound = Mix_LoadWAV("../Assets/Audio/DeathPlayer.wav");
        Mix_PlayChannel(-1, sound, 0);
    }
    if (strcmp(SoundEffect_Title, "Death_Enemy") == 0) {
        Mix_Chunk* sound = Mix_LoadWAV("../Assets/Audio/DeathEnemy.wav");
        Mix_PlayChannel(-1, sound, 0);
    }
}