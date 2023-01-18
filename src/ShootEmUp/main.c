
#include "Settings.h"
#include "Common.h"
#include "Timer.h"
#include "Scene.h"
#include "MenuScene.h"
#include "DeathScene.h"

int main(int argc, char *argv[])
{
    //--------------------------------------------------------------------------
    // Initialisation

    // Initialise la SDL
    Game_Init(SDL_INIT_VIDEO, IMG_INIT_PNG);

    // Cr�e la fen�tre
    int sdlFlags = 0;
#ifdef FULLSCREEN
    sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif
    SDL_Window *window = SDL_CreateWindow(
        u8"Shoot'Em Up", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, sdlFlags
    );

    if (!window)
    {
        printf("ERROR - Create window %s\n", SDL_GetError());
        assert(false); abort();
    }

    // Cr�e le moteur de rendu
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if (!renderer)
    {
        printf("ERROR - Create renderer %s\n", SDL_GetError());
        assert(false); abort();
    }

    // Cr�e le temps global du jeu
    g_time = Timer_New();
    AssertNew(g_time);

    //--------------------------------------------------------------------------
    // Boucle de rendu du menu

    MenuScene *menu_scene = MenuScene_New(renderer);

    while (true)
    {
        // Met � jour le temps
        Timer_Update(g_time);

        // Met � jour la sc�ne
        bool quitLoop = MenuScene_Update(menu_scene);
        if (quitLoop)
            break;

        // Efface le rendu pr�c�dent
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessine la sc�ne
        MenuScene_Render(menu_scene);

        // Affiche le nouveau rendu
        SDL_RenderPresent(renderer);
    }

    //--------------------------------------------------------------------------
    // Boucle de rendu

    Scene *scene = Scene_New(renderer);

    while (true)
    {
        // Met � jour le temps
        Timer_Update(g_time);

        // Met � jour la sc�ne
        bool quitLoop = Scene_Update(scene);
        if (quitLoop)
            break;

        // Efface le rendu pr�c�dent
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessine la sc�ne
        Scene_Render(scene);

        // Affiche le nouveau rendu
        SDL_RenderPresent(renderer);
    }

    //--------------------------------------------------------------------------
    // Boucle de rendu du Death screen

    DeathScene *death_scene = DeathScene_New(renderer);

    while (true)
    {
        // Met � jour le temps
        Timer_Update(g_time);

        // Met � jour la sc�ne
        bool quitLoop = DeathScene_Update(death_scene);
        if (quitLoop)
            break;

        // Efface le rendu pr�c�dent
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessine la sc�ne
        DeathScene_Render(death_scene);

        // Affiche le nouveau rendu
        SDL_RenderPresent(renderer);
    }

    //--------------------------------------------------------------------------
    // Lib�ration de la m�moire

    Scene_Delete(scene);
    scene = NULL;

    Timer_Delete(g_time);
    g_time = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    Game_Quit();

    return EXIT_SUCCESS;
}