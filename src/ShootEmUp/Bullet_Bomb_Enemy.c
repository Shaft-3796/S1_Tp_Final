#include "Bullet_Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "Assets.h"
#include "Music.h"

// Protos
void BulletBombEnemy_Delete(Bullet *self);
void BulletBombEnemy_Update(Bullet *self);
void BulletBombEnemy_Render(Bullet *self);

/// @brief Creates a new Bullet_Player.
Bullet* BulletBombEnemy_New(Scene *scene, Vec2 position, Vec2 velocity, float angle){
    /* --- Base Ini --- */
    Bullet *self = (Bullet *)calloc(1, sizeof(Bullet));
    self->texture = scene->assets->bomb;
    self->worldW = 8 * PIX_TO_WORLD;
    self->worldH = 16 * PIX_TO_WORLD;
    self->radius = 0.3f;
    self->fromPlayer = 0;
    self->type = BULLET_BOMB_ENEMY;
    self->damage = BULLET_DAMAGE_3;

    /* --- Arguments --- */
    self->scene = scene;
    self->position = position;
    self->velocity = velocity;
    self->angle = angle;
    self->fromPlayer = false;

    /* --- Custom --- */
    self->bomb_explosion_time = 0;
    self->ready_to_delete = false;

    /* --- Functions bindings --- */
    self->Delete = &BulletBombEnemy_Delete;
    self->Update = &BulletBombEnemy_Update;
    self->Render = &BulletBombEnemy_Render;

    return self;
}

void BulletBombEnemy_Delete(Bullet *self)
{
    if (!self) return;
    free(self);
}

void BulletBombEnemy_Update(Bullet *self)
{
    // Source de base
    self->sourceRect = (SDL_Rect){ 0, 0, 64, 64 };
    // New pos = old pos + speed * time
    self->position = Vec2_Add(self->position,Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));
    if(self->bomb_explosion_time >= 6.0f){
        self->velocity.x = 0;
        self->velocity.y = 0;
    }
    if(self->bomb_explosion_time >= 6.25f && self->bomb_explosion_time <= 6.5f){
        self->sourceRect = (SDL_Rect){ 64, 0, 64, 64 };
    }
    if(self->bomb_explosion_time >= 6.5f){
        // On incrémente en fonction du temps et de la vitesse
        int frames = (self->bomb_explosion_time- 6.5f) * 20;
        if(frames >= 14){
            frames = 14;
            self->radius = 2;
            self->ready_to_delete = self->ready_to_delete==2 ? 2 : 1;
        }
        // On récupère la position de la frame
        self->sourceRect = (SDL_Rect){ 64+64*frames, 0, 64, 64 };

        playSound("Explosion");
    }

    self->bomb_explosion_time += Timer_GetDelta(g_time);
}

void BulletBombEnemy_Render(Bullet *self)
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
dst.h = BULLET_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
dst.w = BULLET_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;

Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
// Le point de référence est le centre de l'objet
dst.x -= 0.50f * dst.w + 0.25f * dst.w;
dst.y -= 0.50f * dst.h;

// On affiche en position dst (unités en pixels)
SDL_RenderCopyExF(
renderer, self->texture, &(self->sourceRect), &dst, self->angle, NULL, 0);
}
