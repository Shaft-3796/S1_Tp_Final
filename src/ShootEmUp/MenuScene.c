#include "MenuScene.h"
#include "MenuInput.h"

MenuScene *MenuScene_New(SDL_Renderer *renderer)
{
    MenuScene *self = (MenuScene *)calloc(1, sizeof(MenuScene));
    AssertNew(self);

    self->renderer = renderer;

    self->assets = Assets_New(renderer);
    self->camera = Camera_New(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    self->input = MenuInput_New();

    // Background
    SDL_Rect layer1Pos = { 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT};
    self->layer1Pos = layer1Pos;
    SDL_Rect layer0Pos = { 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT};
    self->layer0Pos = layer0Pos;

    return self;
}

void MenuScene_Delete(MenuScene *self)
{
    if (!self) return;

    Assets_Delete(self->assets);
    Camera_Delete(self->camera);
    MenuInput_Delete(self->input);

    free(self);
}

void MenuScene_UpdateLevel(MenuScene *self)
{
}

bool MenuScene_Update(MenuScene *self)
{
    // Met � jour les entr�es utilisateur
    Input_Update(self->input);

    // Met � jour la positions et les dimensions des calques du background
    int offset = Timer_GetDelta(g_time)*(float)BACKGROUND_1_SPEED_MULTIPLIER;
    self->layer1Pos.x += offset;
    if(self->layer1Pos.x+self->layer1Pos.w >= BACKGROUND_WIDTH)
    {
        self->layer1Pos.x -= BACKGROUND_PERIOD*2;
    }
    offset = Timer_GetDelta(g_time)*(float)BACKGROUND_0_SPEED_MULTIPLIER;
    self->layer0Pos.x += offset;
    if(self->layer0Pos.x+self->layer0Pos.w >= BACKGROUND_WIDTH)
    {
        self->layer0Pos.x -= BACKGROUND_PERIOD*2;
    }

    return self->input->quitPressed || self->input->spacePressed;
}

void MenuScene_Render(MenuScene *self)
{
    // Affichage du fond
    SDL_Renderer *renderer = MenuScene_GetRenderer(self);
    Assets *assets = MenuScene_GetAssets(self);
    SDL_RenderCopy(renderer, assets->layers[0], &(self->layer0Pos), NULL);
    SDL_RenderCopy(renderer, assets->layers[1], &(self->layer1Pos), NULL);
    SDL_RenderCopy(renderer, assets->layers[2], &(self->layer1Pos), NULL);

    // Sprites
    SDL_RenderCopy(renderer, assets->menu, NULL, NULL);

    // SDL_RenderCopy(renderer, assets->layers[0], &selection_l2, NULL);
}