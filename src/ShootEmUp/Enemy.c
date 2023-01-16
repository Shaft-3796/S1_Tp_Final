#include "Enemy.h"
#include "Common.h"
#include "Scene.h"

Enemy *Enemy_New(Scene *scene, int type, Vec2 position)
{
    Enemy *self = (Enemy *)calloc(1, sizeof(Enemy));
    AssertNew(self);

    self->scene = scene;
    self->position = position;
    self->type = type;
    self->state = ENEMY_FIRING;

    Assets *assets = Scene_GetAssets(self->scene);
    switch (type)
    {
    case ENEMY_FIGHTER:
        self->worldW = 64 * PIX_TO_WORLD;
        self->worldH = 64 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter;
        break;

    default:
        assert(false);
        break;
    }

    return self;
}

void Enemy_Delete(Enemy *self)
{
    if (!self) return;
    free(self);
}

void Enemy_Update(Enemy *self)
{
    
}

void Enemy_Render(Enemy *self)
{

}

void Enemy_Damage(Enemy *self, int damage)
{

}
