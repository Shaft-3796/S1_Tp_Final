#include "Bullet_Player.h"
#include "Bullet.h"
#include "Scene.h"
#include "Assets.h"

// Protos
void BulletAuto_Delete(Bullet *self);
void BulletAuto_Update(Bullet *self);
void BulletAuto_Render(Bullet *self);

/// @brief Creates a new Bullet_Player.
Bullet* BulletAuto_New(Scene *scene, Vec2 position, Vec2 velocity, float angle){
    /* --- Base Ini --- */
    Bullet *self = (Bullet *)calloc(1, sizeof(Bullet));
    self->texture = scene->assets->auto_bullet;
    self->worldW = 8 * PIX_TO_WORLD;
    self->worldH = 16 * PIX_TO_WORLD;
    self->radius = 0.3f;
    self->fromPlayer = false;
    self->type = BULLET_AUTO;
    self->damage = BULLET_DAMAGE_2;

    /* --- Arguments --- */
    self->scene = scene;
    self->position = position;
    self->velocity = velocity;
    self->angle = angle;
    self->fromPlayer = false;

    /* --- Custoom --- */
    self->follow_disable = false;

    /* --- Functions bindings --- */
    self->Delete = &BulletAuto_Delete;
    self->Update = &BulletAuto_Update;
    self->Render = &BulletAuto_Render;

    return self;
}

void BulletAuto_Delete(Bullet *self)
{
    if (!self) return;
    free(self);
}

void BulletAuto_Update(Bullet *self)
{
    // Update du vecteur vitesse
    Player* player = self->scene->player;
    Vec2 player_pos = player->position;
    Vec2 bullet_pos = self->position;
    Vec2 diff = Vec2_Sub(player_pos, bullet_pos);
    float dist = Vec2_Length(diff);
    if (dist > 2.f && !self->follow_disable)
    {
        // On se dirige vers le player
        Vec2 dir = Vec2_Normalize(diff);
        self->velocity = Vec2_Scale(dir, 6.f);
        // On update l'angle
        //self->angle = acosf(self->velocity.y/Vec2_Length(self->velocity));
        // Angle to deg
        self->angle = 90 - atan2f(diff.y, diff.x) * 180.f / M_PI;
    }
    else{
        self->follow_disable = true;
    }

    // New pos = old pos + speed * time
    self->position = Vec2_Add(self->position,Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));

}

void BulletAuto_Render(Bullet *self)
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
renderer, self->texture, NULL, &dst, self->angle, NULL, 0);
}
