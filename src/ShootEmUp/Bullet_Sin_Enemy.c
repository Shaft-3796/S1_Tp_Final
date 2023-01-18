#include "Bullet_Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "Assets.h"

// Protos
void BulletSinEnemy_Delete(Bullet *self);
void BulletSinEnemy_Update(Bullet *self);
void BulletSinEnemy_Render(Bullet *self);

/// @brief Creates a new Bullet_Player.
Bullet* BulletSinEnemy_New(Scene *scene, Vec2 position, Vec2 velocity, float angle, float oscillation_period){
    /* --- Base Ini --- */
    Bullet *self = (Bullet *)calloc(1, sizeof(Bullet));
    self->texture = scene->assets->base_enemy_bullet;
    self->worldW = 8 * PIX_TO_WORLD;
    self->worldH = 16 * PIX_TO_WORLD;
    self->radius = 0.05f;
    self->fromPlayer = false;
    self->type = BULLET_SIN_ENEMY;

    /* --- Arguments --- */
    self->scene = scene;
    self->position = position;
    self->velocity = velocity;
    self->angle = angle;
    self->fromPlayer = true;

    /* --- Custom --- */
    self->oscillation_period = oscillation_period;
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
    // On update l'accumulateur d'oscillation
    self->oscillation_acumulator += Timer_GetDelta(g_time);
    // Si l'oscillation est finie
    if (self->oscillation_acumulator >= self->oscillation_period){
        // On reset l'accumulateur
        self->oscillation_acumulator = 0;
        // On change l'ordonnée de la vitesse
        self->velocity.y *= -1;
    }

    // New pos = old pos + speed * time
    self->position = Vec2_Add(self->position,Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));
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
float multiplier = 1.f;
if(self->scene->input->resize_bullets){multiplier = 0.25f; }
dst.h = BULLET_SIZE_MULTIPLIER * PIX_TO_WORLD * scale * multiplier;
dst.w = BULLET_SIZE_MULTIPLIER * PIX_TO_WORLD * scale * multiplier;

Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
// Le point de référence est le centre de l'objet
dst.x -= 0.50f * dst.w + 0.25f * dst.w;
dst.y -= 0.50f * dst.h;

// On affiche en position dst (unités en pixels)
SDL_RenderCopyExF(
renderer, self->texture, NULL, &dst, self->angle, NULL, 0);
}
