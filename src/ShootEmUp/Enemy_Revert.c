#include "Enemy_Revert.h"
#include "Scene.h"
#include "Enemy.h"
#include "Timer.h"
#include "Math.h"
#include "Bullet.h"

// Protos
void EnemyRevert_Delete(Enemy *self);
void EnemyRevert_Update(Enemy *self);
void EnemyRevert_Render(Enemy *self);
void EnemyRevert_Damage(Enemy *self, int damage);
void EnemyRevert_Revert(Enemy *self, Bullet* bullet);

Enemy *EnemyRevert_New(Scene *scene, Vec2 position, int life)
{
    /* --- Base Ini --- */
    Enemy *self = (Enemy*)calloc(1, sizeof(Enemy));
    self->type = ENEMY_REVERT;
    Assets *assets = Scene_GetAssets(scene);
    self->texture = assets->revert_enemy;
    self->state = ENEMY_FIRING;
    self->moveSens = VERTICAL;
    self->direction = 1;
    self->worldH = 48;
    self->worldW = 48;
    self->radius = 0.25;
    /* --- --- --- --- */

    /* --- Arguments ini --- */
    self->scene = scene;
    self->position = position;
    self->life = life;

    /* --- Functions bindings --- */
    self->Delete = &EnemyRevert_Delete;
    self->Update = &EnemyRevert_Update;
    self->Render = &EnemyRevert_Render;
    self->Damage = &EnemyRevert_Damage;
    /* --- --- --- --- --- --- --- */
    self->Revert = &EnemyRevert_Revert;
    return self;
}

void EnemyRevert_Delete(Enemy *self)
{
    if (!self) return;
    free(self);
}

void EnemyRevert_Update(Enemy *self)
{

}

void EnemyRevert_Render(Enemy *self)
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
    dst.h = ENEMY_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
    dst.w = ENEMY_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
    // Le point de référence est le centre de l'objet
    dst.x -= 0.5f * dst.w;
    dst.y -= 0.50f * dst.h;
    // On affiche en position dst (unités en pixels)
    SDL_RenderCopyExF(renderer, self->texture, NULL, &dst, 270.f, NULL, 0);
}

void EnemyRevert_Damage(Enemy *self, int damage)
{
    self->life -= damage;
    if (self->life <= 0)
    {
        self->state = ENEMY_DEAD;
    }
}

void EnemyRevert_Revert(Enemy *self, Bullet *bullet)
{
    bullet->fromPlayer = false;
    bullet->velocity.x = -bullet->velocity.x;
    bullet->velocity.y = -bullet->velocity.y;
    bullet->texture = self->scene->assets->base_player_bullets_corrupted;
}
