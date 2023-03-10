#include "Bullet_Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "Assets.h"
#include "Bullet_Sin_Enemy.h"

// Protos
void BulletSinEnemy_Delete(Bullet *self);
void BulletSinEnemy_Update(Bullet *self);
void BulletSinEnemy_Render(Bullet *self);

/// @brief Creates a new Bullet_Player.
Bullet* BulletSinEnemy_New(Scene *scene, Vec2 position, Vec2 velocity, float angle){
    /* --- Base Ini --- */
    Bullet *self = (Bullet *)calloc(1, sizeof(Bullet));
    self->texture = scene->assets->sin_enemy_rocket;
    self->worldW = 8 * PIX_TO_WORLD;
    self->worldH = 16 * PIX_TO_WORLD;
    self->radius = 0.05f;
    self->fromPlayer = false;
    self->type = BULLET_SIN_ENEMY;
    self->damage = BULLET_DAMAGE_3;

    /* --- Arguments --- */
    self->scene = scene;
    self->position = position;
    self->velocity = velocity;
    self->angle = angle;

    /* --- Custom --- */ 
    self->oscillation_acumulator = 0;

    /* --- Functions bindings --- */
    self->Delete = &BulletSinEnemy_Delete;
    self->Update = &BulletSinEnemy_Update;
    self->Render = &BulletSinEnemy_Render;

    return self;
}

void BulletSinEnemy_Delete(Bullet *self)
{
    if (!self) return;
    free(self);
}

void BulletSinEnemy_Update(Bullet *self)
{
    if(self->oscillation_acumulator >= 0.75){
        self->velocity.y *= -1;
        self->oscillation_acumulator = 0;
        self->angle = self->angle == -45.0f ? -135.0f : -45.0f;
    }
    //printf("Vitesse: %f, %f\n", self->velocity.x, self->velocity.y);
    self->oscillation_acumulator += Timer_GetDelta(g_time);
    self->position = Vec2_Add(self->position, Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));
}

void BulletSinEnemy_Render(Bullet *self)
{
    // On récupère des infos essentielles (communes à tout objet)
Scene *scene = self->scene;
SDL_Renderer *renderer = Scene_GetRenderer(scene);
Camera *camera = Scene_GetCamera(scene);
// On calcule la position en pixels en fonction de la position
// en tuiles, la taille de la fenêtre et la taille des textures.
float scale = Camera_GetWorldToViewScale(camera);
SDL_FRect dst = { 0 };

// On calcule la destination en fonction de la position de l'objet
dst.h = (BULLET_SIZE_MULTIPLIER * PIX_TO_WORLD * scale)/2;
dst.w = (BULLET_SIZE_MULTIPLIER * PIX_TO_WORLD * scale)/2;

Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
// Le point de référence est le centre de l'objet
dst.x -= 0.50f * dst.w + 0.25f * dst.w;
dst.y -= 0.50f * dst.h;

// On affiche en position dst (unités en pixels)
SDL_RenderCopyExF(
renderer, self->texture, NULL, &dst, self->angle, NULL, 0);
}
