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
    case BULLET_SIN_ENEMY:
        self->ordInit = 0;
        self->texture = assets->base_enemy_bullet;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = false;
        break;
    default:
    case ASTEROID:
        self->texture = assets->asteroid;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = false;
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
    switch (self->type) {
        case BULLET_SIN_ENEMY:
            if(self->position.y >= self->ordInit+1){
                self->velocity.y * -1;
            }
            if(self->position.y <= self->ordInit-1){
                self->velocity.y * -1;
            }
            else{
                self->position = Vec2_Add(self->position,Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));
            }
            break;
        default:
            // On récupère des infos essentielles (communes à tout objet)
            Scene *scene = self->scene;
            Input *input = Scene_GetInput(scene);
            // New pos = old pos + speed * time
            self->position = Vec2_Add(self->position,Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));
            break;
    }
}

void Bullet_Render(Bullet *self)
{
switch (self->type) {
    case ASTEROID:
        dst.h = ASTEROID_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
        dst.w = ASTEROID_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
        break;
    default:
        dst.h = BULLET_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
        dst.w = BULLET_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
        break;

}

Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
// Le point de référence est le centre de l'objet
dst.x -= 0.50f * dst.w;
dst.y -= 0.50f * dst.h;
    switch (self->type) {
        case BULLET_BASE_ENEMY:
            dst.x -= 0.25f * dst.w;
            break;
        default:
            break;
    }
// On affiche en position dst (unités en pixels)
SDL_RenderCopyExF(
renderer, self->texture, NULL, &dst, self->angle, NULL, 0);
}

/* --- Gameplay --- */

// Shortcut function to create an asteroid
Bullet* Asteroid_New(Scene *scene, int y_pos, float angle){
    Vec2 position = {18, y_pos};
    Vec2 velocity = {-1*ASTEROID_SPEED_MULTIPLIER, 0};
    return Bullet_New(scene, position, velocity, ASTEROID, angle);
}