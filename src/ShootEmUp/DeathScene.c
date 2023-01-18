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

    self->angle = 0.0f;
    self->angle_accumulator = 0.0f;

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

bool DeathScene_Update(DeathScene *self)
{
self->angle_accumulator += Timer_GetDelta(g_time);
    if(self->angle_accumulator >= 0.05f)
    {
        self->angle_accumulator = 0.0f;
        self->angle += 0.5f;
        if (self->angle >= 360.0f)
        {
            self->angle = 0.0f;
        }
    }

    if(self->input->quitPressed)
    {
        return true;
    }
    else
    {
        MenuInput_Update(self->input);
        return self->input->spacePressed;
    }
}

void DeathScene_Render(DeathScene *self)
{
    SDL_SetRenderDrawColor(self->renderer, 0, 0, 0, 255);
    // Sprites
    //Bck
    SDL_RenderCopy(self->renderer, self->assets->layers[3], NULL, NULL);
    // Hole
    SDL_RenderCopyExF(self->renderer, self->assets->black_hole, NULL, NULL, self->angle, NULL, SDL_FLIP_NONE);
    // Text
    SDL_RenderCopy(self->renderer, self->assets->death, NULL, NULL);



    // SDL_RenderCopy(renderer, assets->layers[0], &selection_l2, NULL);
}