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
    self->life_bar_accumulator = -1;
    self->max_life = life;
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

    // Rendu de la barre de vie
    // Frame
    SDL_FRect dst_frame = {0};
    dst_frame.h = ENEMY_LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
    dst_frame.w = ENEMY_LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
    Vec2 pos_frame = self->position;
    pos_frame.x += REVERT_ENEMY_LIFE_BAR_OFFSET_X;
    pos_frame.y += REVERT_ENEMY_LIFE_BAR_OFFSET_Y;
    Camera_WorldToView(camera, pos_frame, &dst_frame.x, &dst_frame.y);
    SDL_RenderCopyF(
    renderer, assets->enemy_life_bar_frame, NULL, &dst_frame);
    // Content
    SDL_Rect src_content = {0};
    src_content.h = 64;
    src_content.w = 10 + (float)54/((float)self->max_life/self->life);
    src_content.x = 0;
    src_content.y = 0;
    SDL_FRect dst_content = {0};
    dst_content.h = ENEMY_LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
    dst_content.w = (ENEMY_LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale) * ((float)src_content.w/64);
    Vec2 pos_content = self->position;
    pos_content.x += REVERT_ENEMY_LIFE_BAR_OFFSET_X;
    pos_content.y += REVERT_ENEMY_LIFE_BAR_OFFSET_Y;
    Camera_WorldToView(camera, pos_content, &dst_content.x, &dst_content.y);
    SDL_RenderCopyF(
    renderer, assets->enemy_life_bar_content, &src_content, &dst_content);
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
