#include "Bullet.h"
#include "Common.h"
#include "Scene.h"

Bullet *Bullet_New(Scene *scene, Vec2 position, Vec2 velocity, int type, float angle)
{
    Bullet *self = (Bullet *)calloc(1, sizeof(Bullet));
    AssertNew(self);

    self->position = position;
    self->velocity = velocity;
    self->type = type;
    self->angle = angle;
    self->scene = scene;
    self->fromPlayer = false;

    Assets *assets = Scene_GetAssets(scene);
    switch (type)
    {
    case BULLET_FIGHTER:
        self->texture = assets->fighterBullet;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = false;
        break;

    default:
    case BULLET_PLAYER:
        self->texture = assets->playerBullet;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = true;
        break;
    }

    return self;
}

void Bullet_Delete(Bullet *self)
{
    if (!self) return;
    free(self);
}

void Bullet_Update(Bullet *self)
{

}

void Bullet_Render(Bullet *self)
{

}