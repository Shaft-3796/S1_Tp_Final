#include "DeathScene.h"
#include "MenuInput.h"

DeathScene *DeathScene_New(SDL_Renderer *renderer)
{
    DeathScene *self = (DeathScene *)calloc(1, sizeof(DeathScene));
    AssertNew(self);

    self->renderer = renderer;

    self->assets = Assets_New(renderer);
    self->camera = Camera_New(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    self->input = MenuInput_New();

    self->multiplicator = 1.f;
    self->multiplicator_accumulator = 0.0f;

    SDL_Rect layer0Pos = { 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT};
    self->layer0Pos = layer0Pos;

    return self;
}

void DeathScene_Delete(DeathScene *self)
{
    if (!self) return;

    Assets_Delete(self->assets);
    Camera_Delete(self->camera);
    MenuInput_Delete(self->input);

    free(self);
}

void DeathScene_UpdateLevel(DeathScene *self)
{

}

int DeathScene_Update(DeathScene *self)
{
    MenuInput_Update(self->input);

    int offset = Timer_GetDelta(g_time)*(float)BACKGROUND_0_SPEED_MULTIPLIER;
    self->layer0Pos.x += offset;
    if(self->layer0Pos.x+self->layer0Pos.w >= BACKGROUND_WIDTH)
    {
        self->layer0Pos.x -= BACKGROUND_PERIOD*2;
    }

    self->multiplicator_accumulator += Timer_GetDelta(g_time);
    if(self->multiplicator_accumulator >= 0.05f && self->multiplicator <= 5.f)
    {
        self->multiplicator_accumulator = 0.0f;
        self->multiplicator += 0.1f;
    }

    /* --- Return --- */
    if(self->input->quitPressed){
        return 1;
    }
    else if(self->input->spacePressed){
        return 2;
    }
    else{
        return 0;
    }
}

void DeathScene_Render(DeathScene *self)
{
    // Background
    SDL_RenderCopy(self->renderer, self->assets->layers[1], &(self->layer0Pos), NULL);

    SDL_SetRenderDrawColor(self->renderer, 0, 0, 0, 255);
    // Sprites
    //Bck
    // SDL_RenderCopy(self->renderer, self->assets->layers[3], NULL, NULL);
    // Hole
    //SDL_RenderCopyExF(self->renderer, self->assets->black_hole, NULL, NULL, self->angle, NULL, SDL_FLIP_NONE);

    // Text
    SDL_RenderCopy(self->renderer, self->assets->death, NULL, NULL);
    SDL_Rect src = {(1920-(1920/self->multiplicator))/2, (1080-(1080/self->multiplicator))/2, 1920/self->multiplicator, 1080/self->multiplicator};
    SDL_RenderCopyF(self->renderer, self->assets->game_over_layer, &src, NULL);



    // SDL_RenderCopy(renderer, assets->layers[0], &selection_l2, NULL);
}