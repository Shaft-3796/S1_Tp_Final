#include "Input.h"
#include "Common.h"

Input *Input_New()
{
    Input *self = (Input *)calloc(1, sizeof(Input));
    AssertNew(self);

    // Eg
    for(int i = 0; i < 5; i++)
    {
        self->letters[i] = 0;
    }
    self->resize_bullets = 0;
    self->waitForMouseUp = 0;

    return self;
}

void Input_Delete(Input *self)
{
    if (!self) return;
    free(self);
}

void Input_Update(Input *self) {
    self->shootPressed = false;
    SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
        switch (evt.type) {
            case SDL_QUIT:
                self->quitPressed = true;
                break;

            case SDL_KEYDOWN:
                if (evt.key.repeat)
                    break;

                switch (evt.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        self->quitPressed = true;
                        break;

                    case SDL_SCANCODE_RIGHT:
                        // Deplacement � droite
                        self->hAxis = 1.f;
                        break;

                    case SDL_SCANCODE_LEFT:
                        // Deplacement � gauche
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

                    case SDL_SCANCODE_SPACE:
                        // shoot
                        self->shootPressed = true;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                if (evt.key.repeat)
                    break;

                switch (evt.key.keysym.scancode) {
                    case SDL_SCANCODE_RIGHT:
                        // Deplacement � droite
                        if (self->hAxis > 0.f)
                            self->hAxis = 0.f;
                        break;

                    case SDL_SCANCODE_LEFT:
                        // Deplacement � gauche
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

                        /* --- Easter Egg --- */
                    case SDL_SCANCODE_B:
                        self->letters[0] = 1;
                        break;

                    case SDL_SCANCODE_O:
                        self->letters[1] = 1;
                        break;

                    case SDL_SCANCODE_D:
                        self->letters[2] = 1;
                        break;

                    case SDL_SCANCODE_I:
                        self->letters[3] = 1;
                        break;

                    case SDL_SCANCODE_N:
                        self->letters[4] = 1;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (evt.button.button == SDL_BUTTON_LEFT) {
                    fflush(stdout);
                    if (!self->waitForMouseUp) {
                        self->shootPressed = true;
                        self->waitForMouseUp = true;
                    }
                    else{
                        self->shootPressed = false;
                        self->waitForMouseUp = true;
                    }

                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (evt.button.button == SDL_BUTTON_LEFT) {
                    fflush(stdout);
                    self->shootPressed = false;
                    self->waitForMouseUp = false;
                }
                break;
        }

        for (int i = 0; i < 5; i++) {
            if (self->letters[i] == 0) {
                break;
            }
            if (i == 4) {
                self->easter_egg = true;
            }
        }
    }
}