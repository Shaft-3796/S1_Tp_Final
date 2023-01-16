#include "Common.h"
#include "Assets.h"

Timer *g_time = NULL;

void Game_Init(int sdlFlags, int imgFlags)
{

    // Initialise la SDL2
    if (SDL_Init(sdlFlags) < 0)
    {
        printf("ERROR - SDL_Init %s\n", SDL_GetError());
        assert(false); abort();
    }

    // Initialise la SDL2 image
    if (IMG_Init(imgFlags) != imgFlags)
    {
        printf("ERROR - IMG_Init %s\n", IMG_GetError());
        assert(false); abort();
    }

    // // Initialise la SDL2 TTF
    // if (TTF_Init() == -1)
    // {
    //     printf("ERROR - TTF_Init %s\n", TTF_GetError());
    //     assert(false); abort();
    // }

    // // Initialise la SDL2 Mixer
    // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    // {
    //     printf("ERROR - Mix_OpenAudio %s\n", Mix_GetError());
    //     assert(false); abort();
    // }
    // Mix_AllocateChannels(8);
}

void Game_Quit()
{
    // Mix_Quit();
    // TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
