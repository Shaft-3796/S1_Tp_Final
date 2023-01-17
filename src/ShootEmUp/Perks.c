#include "Perks.h"
#include "Scene.h"
#include "Common.h"
#include "Settings.h"
#include "Player.h"

Perk *Perk_New(Scene *scene, int type, Vec2 position)
{
    Perk *self = (Perk *)calloc(1, sizeof(Perk));
    AssertNew(self);

    Assets *assets = Scene_GetAssets(scene);

    self->scene = scene;
    self->position = position;
    self->radius = 0.25f;
    self->type = type;
    self->angle = 0;
    self->rotate_timer = 0;
    if (type == 1)
    {
        self->texture = assets->astro;
    }
    /*
    else if (type == 2)
    {
        self->texture = assets->shield;
    }
    else if (type == 3)
    {
        self->texture = assets->life;
    }
    else if (type == 4)
    {
        self->texture = assets->ammo;
    }
    */

    return self;
}

void Perk_Delete(Perk *self)
{
    if (!self) return;
    free(self);
}

void Perk_Update(Perk *self)
{
    // Pas d'update pour le moment puisque les Perk sont statiques
}


void Perk_Render(Perk *self)
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
// Changez 48 par une autre valeur pour grossir ou réduire l'objet
dst.h = PERKS_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
dst.w = PERKS_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
// Le point de référence est le centre de l'objet
dst.x -= 0.50f * dst.w;
dst.y -= 0.50f * dst.h;
// On change l'angle de rotation
self->rotate_timer += Timer_GetDelta(g_time);
if (self->rotate_timer > PERKS_ROTATION_SPEED)
{
    self->rotate_timer = 0;
    self->angle += 1;
}
// On affiche en position dst (unités en pixels)
SDL_RenderCopyExF(
renderer, self->texture, NULL, &dst, self->angle, NULL, 0);
}

void Perk_Apply_Effect(Perk *self, Player *player)
{
    if (self->type == 1)
    {
        player->speed = player->speed * ASTRO_SPEED_MULTIPLIER;
        player->scene->backgroundSpeedMultiplier = ASTRO_SPEED_MULTIPLIER;
        player->perk_astro = true;
        player->perk_astro_timer = 0;
    }
    /*
    else if (self->type == 2)
    {
        player->shield = 1;
    }
    else if (self->type == 3)
    {
        player->life = player->life + 1;
    }
    else if (self->type == 4)
    {
        player->ammo = player->ammo + 10;
    }
    */
}