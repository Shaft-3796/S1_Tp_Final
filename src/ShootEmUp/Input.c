#include "Input.h"
#include "Common.h"

Input *Input_New()
{
    Input *self = (Input *)calloc(1, sizeof(Input));
    AssertNew(self);

    return self;
}

void Input_Delete(Input *self)
{
    if (!self) return;
    free(self);
}

void Input_Update(Input *self)
{
    self->quitPressed = false;

    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        switch (evt.type)
        {
        case SDL_QUIT:
            self->quitPressed = true;
            break;

        case SDL_KEYDOWN:
            if (evt.key.repeat)
                break;

            switch (evt.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                self->quitPressed = true;
                break;

            case SDL_SCANCODE_RIGHT:
                // Deplacement à droite
                self->hAxis = 1.f;
                break;

            case SDL_SCANCODE_LEFT:
                // Deplacement à gauche
                self->hAxis = -1.f;
                break;

            case SDL_SCANCODE_UP:
                // Deplacement en haut
                self->vAxis = 1.f;
                break;

            case SDL_SCANCODE_DOWN:
                // Deplacement en bas
                self->vAxis = -1.f;
                break;

            default:
                break;
            }
            break;

        case SDL_KEYUP:
            if (evt.key.repeat)
                break;

            switch (evt.key.keysym.scancode)
            {
            case SDL_SCANCODE_RIGHT:
                // Deplacement à droite
                if (self->hAxis > 0.f)
                    self->hAxis = 0.f;
                break;

            case SDL_SCANCODE_LEFT:
                // Deplacement à gauche
                if (self->hAxis < 0.f)
                    self->hAxis = 0.f;
                break;

            case SDL_SCANCODE_UP:
                // Deplacement en haut
                if (self->vAxis > 0.f)
                    self->vAxis = 0.f;
                break;

            case SDL_SCANCODE_DOWN:
                // Deplacement en bas
                if (self->vAxis < 0.f)
                    self->vAxis = 0.f;
                break;

            default:
                break;
            }
            break;
        }
    }
}
