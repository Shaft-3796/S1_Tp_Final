#include "Enemy_debug.h"
#include "Scene.h"
#include "Enemy.h"

EnemyDebug *EnemyDebug_New(Enemy enemy, Scene *scene, int type, Vec2 position, int hp)
{
    EnemyDebug *self = (EnemyDebug *)calloc(1, sizeof(EnemyDebug));
    AssertNew(self);

    self->scene = scene;
    self->position = position;
    self->type = type;
    self->state = ENEMY_FIRING;
    self->hp = hp;

    Assets *assets = Scene_GetAssets(self->scene);
    self->texture = assets->fighter;

    /* DO NOT REMOVE */
    enemy.enemy = self;

    return self;
}

void EnemyDebug_Delete(EnemyDebug *self)
{
    if (!self) return;
    free(self);
}

void EnemyDebug_Update(EnemyDebug *self)
{
    
}

void EnemyDebug_Render(EnemyDebug *self)
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
dst.h = 48 * PIX_TO_WORLD * scale;
dst.w = 48 * PIX_TO_WORLD * scale;
Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
// Le point de référence est le centre de l'objet
dst.x -= 0.50f * dst.w;
dst.y -= 0.50f * dst.h;
// On affiche en position dst (unités en pixels)
SDL_RenderCopyExF(
renderer, self->texture, NULL, &dst, 270.f, NULL, 0);
}

void EnemyDebug_Damage(EnemyDebug *self, int damage)
{
    self->hp -= damage;
    if (self->hp <= 0)
    {
        self->state = ENEMY_DEAD;
    }
}
