#include "Timer.h"

Timer* Timer_New()
{
    Timer *self = (Timer*)calloc(1, sizeof(Timer));
    AssertNew(self);

    self->currentTime = 0.0f;
    self->previousTime = 0.0f;

    self->delta = 0.0f;
    self->unscaledDelta = 0.0f;
    self->elapsed = 0.0f;
    self->unscaledElapsed = 0.0f;

    self->maxDelta = 0.2f;
    self->scale = 1.0f;

    return self;
}

void Timer_Delete(Timer* self)
{
    if (!self) return;

    memset(self, 0, sizeof(Timer));
    free(self);
}

void Timer_Start(Timer* self)
{
    assert(self);
    self->currentTime = SDL_GetTicks() / 1000.f;
    self->previousTime = SDL_GetTicks() / 1000.f;
    self->delta = 0.0f;
}

void Timer_Update(Timer* self)
{
    assert(self);
    self->previousTime = self->currentTime;
    self->currentTime = SDL_GetTicks() / 1000.f;

    float unscaledDelta = self->currentTime - self->previousTime;
    if (unscaledDelta > self->maxDelta)
        unscaledDelta = self->maxDelta;

    self->unscaledDelta = unscaledDelta;
    self->delta = self->scale * self->unscaledDelta;

    self->unscaledElapsed += self->unscaledDelta;
    self->elapsed += self->delta;
}