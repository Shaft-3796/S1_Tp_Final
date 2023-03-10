#include "Bullet_Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "Assets.h"

// Protos
void BulletPlayer_Delete(Bullet *self);
void BulletPlayer_Update(Bullet *self);
void BulletPlayer_Render(Bullet *self);

/// @brief Creates a new Bullet_Player.
Bullet* BulletPlayer_New(Scene *scene, Vec2 position, Vec2 velocity, float angle){
    /* --- Base Ini --- */
    Bullet *self = (Bullet *)calloc(1, sizeof(Bullet));
    self->texture = scene->assets->base_player_bullets;
    self->worldW = 8 * PIX_TO_WORLD;
    self->worldH = 16 * PIX_TO_WORLD;
    self->radius = 0.05f;
    self->fromPlayer = true;
    self->type = BULLET_PLAYER;

    /* --- Arguments --- */
    self->scene = scene;
    self->position = position;
    self->velocity = velocity;
    self->angle = angle;
    self->fromPlayer = true;

    /* --- Functions bindings --- */
    self->Delete = &BulletPlayer_Delete;
    self->Update = &BulletPlayer_Update;
    self->Render = &BulletPlayer_Render;

    return self;
}

void BulletPlayer_Delete(Bullet *self)
{
    if (!self) return;
    free(self);
}

void BulletPlayer_Update(Bullet *self)
{
    // New pos = old pos + speed * time
    self->position = Vec2_Add(self->position,Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));
}

void BulletPlayer_Render(Bullet *self)
{
    // On récupère des infos essentielles (communes à tout objet)
Scene *scene = self->scene;
SDL_Renderer *renderer = Scene_GetRenderer(scene);
Assets *assets = Scene_GetAssets(scene);
Camera *camera = Scene_GetCamera(scene);
// On calcule la position en pixels en fonction de la position
// en tuiles, la taille de la fenêtre et la taille des textures.
float scale = Camera_GetWorldToViewScale(camera);
SDL_FRect dst = { 0 };

// On calcule la destination en fonction de la position de l'objet
float multiplier = 1.f;
if(self->scene->input->easter_egg){
    multiplier = 0.25f;
    self->texture = assets->bodin;
} else {
    self->texture = assets->base_player_bullets;
}
dst.h = PLAYER_SIZE_MULTIPLIER * PIX_TO_WORLD * scale * multiplier;
dst.w = PLAYER_SIZE_MULTIPLIER * PIX_TO_WORLD * scale * multiplier;

Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
// Le point de référence est le centre de l'objet
dst.x -= 0.50f * dst.w;
dst.y -= 0.50f * dst.h;

// On affiche en position dst (unités en pixels)
SDL_RenderCopyExF(
renderer, self->texture, NULL, &dst, self->angle, NULL, 0);
}
