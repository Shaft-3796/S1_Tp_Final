#include "MenuInput.h"
#include "Common.h"

MenuInput* MenuInput_New()
{
    MenuInput *self = (MenuInput *)calloc(1, sizeof(MenuInput));
    AssertNew(self);
    self->spacePressed = false;
    return self;
}

void MenuInput_Delete(MenuInput *self)
{
    if (!self) return;
    free(self);
}

void MenuInput_Update(MenuInput *self) {
    self->quitPressed = false;

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
                    case SDL_SCANCODE_SPACE:
                        // shoot
                        self->spacePressed = true;
                        break;

                    default:
                        break;
                }
                break;

        }
    }
}
