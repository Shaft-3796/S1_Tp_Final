#include "Enemy_debug.h"
#include "Scene.h"
#include "Enemy.h"
#include "Bullet.h"

// Protos
void EnemyDebug_Delete(Enemy *self);
void EnemyDebug_Update(Enemy *self);
void EnemyDebug_Render(Enemy *self);
void EnemyDebug_Damage(Enemy *self, int damage);

/// @brief Créer un nouvek enemi de type Debug
Enemy* EnemyDebug_New(Scene *scene, Vec2 position, int life)
{
    /* --- Base Ini --- */
    Enemy *self = (Enemy*)calloc(1, sizeof(Enemy));
    self->type = ENEMY_DEBUG;
    self->texture = scene->assets->fighter;
    self->state = ENEMY_FIRING;
    self->worldH = 48;
    self->worldW = 48;
    self->radius = 0.5;
    /* --- --- --- --- */

    /* --- Custom Ini --- */
    self->scene = scene;
    self->position = position;
    self->life = life;

    /* --- Functions bindings --- */
    self->Delete = &EnemyDebug_Delete;
    self->Update = &EnemyDebug_Update;
    self->Render = &EnemyDebug_Render;
    self->Damage = &EnemyDebug_Damage;
    /* --- --- --- --- --- --- --- */

    return self;
}

void EnemyDebug_Delete(Enemy *self)
{
    if (!self) return;
    free(self);
}

void EnemyDebug_Update(Enemy *self)
{
    
}

void EnemyDebug_Render(Enemy *self)
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

void EnemyDebug_Damage(Enemy *self, int damage)
{
    self->life -= damage;
    if (self->life <= 0)
    {
        self->state = ENEMY_DEAD;
    }
}
