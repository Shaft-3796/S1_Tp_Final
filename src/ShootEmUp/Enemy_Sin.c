#include "Enemy_Sin.h"
#include "Scene.h"
#include "Enemy.h"
#include "Timer.h"
#include "Math.h"
#include "Bullet.h"
#include "Bullet_Sin_Enemy.h"

// Protos
void EnemySin_Delete(Enemy *self);
void EnemySin_Update(Enemy *self);
void EnemySin_Render(Enemy *self);
void EnemySin_Damage(Enemy *self, int damage);

Enemy *EnemySin_New(Scene *scene, Vec2 position, int life, float shoot_period)
{
    /* --- Base Ini --- */
    Enemy *self = (Enemy*)calloc(1, sizeof(Enemy));
    self->type = ENEMY_SIN;
    Assets *assets = Scene_GetAssets(scene);
    self->texture = assets->sin_enemy;
    self->state = ENEMY_FIRING;
    self->worldH = 48;
    self->worldW = 48;
    self->radius = 0.5;
    self->life_bar_accumulator = -1;
    self->max_life = life;
    /* --- --- --- --- */

    /* --- Custom Ini --- */
    self->scene = scene;
    self->position = position;
    self->life = life;
    self->moveSens = VERTICAL;
    self->direction = 1;
    self->accumulator_bullet_shot = 0;
    self->shoot_period = shoot_period;
    self->accumulator_Teleport = 0;
    self->rafal_period = 0;

    /* --- Functions bindings --- */
    self->Delete = &EnemySin_Delete;
    self->Update = &EnemySin_Update;
    self->Render = &EnemySin_Render;
    self->Damage = &EnemySin_Damage;
    /* --- --- --- --- --- --- --- */
    return self;
}

void EnemySin_Delete(Enemy *self)
{
    if (!self) return;
    free(self);
}

void EnemySin_Update(Enemy *self)
{
    if (self->accumulator_bullet_shot >= self->shoot_period){
        Vec2 velocity = Vec2_Set(-4.0f, 1.5f);
        Bullet *bullet = BulletSinEnemy_New(self->scene, self->position, velocity, -45.0f);
        Scene_AppendBullet(self->scene, bullet);
        self->accumulator_bullet_shot = 0;
    }
    self->accumulator_bullet_shot += Timer_GetDelta(g_time);

    // Mise à jour de la vitesse en fonction de l'état des touches
    Vec2 velocity = Vec2_Set(0, self->direction);
    if(self->moveSens == VERTICAL){
        // Mise à jour de la position
        self->position = Vec2_Add(self->position, Vec2_Scale(velocity, Timer_GetDelta(g_time)));
        Vec2 new_position = Vec2_Add(self->position,Vec2_Scale(velocity, Timer_GetDelta(g_time)));
        if(new_position.y < 0.5 || new_position.y > 8.5){
            switch (self->direction) {
                case 1:
                    self->direction = -1;
                    break;
                default:
                    self->direction = 1;
                    break;
            }
        }
    }
}

void EnemySin_Render(Enemy *self)
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
    dst.h = 88 * PIX_TO_WORLD * scale;
    dst.w = 88 * PIX_TO_WORLD * scale;
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
    pos_frame.x += SIN_ENEMY_LIFE_BAR_OFFSET_X;
    pos_frame.y += SIN_ENEMY_LIFE_BAR_OFFSET_Y;
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
    pos_content.x += SIN_ENEMY_LIFE_BAR_OFFSET_X;
    pos_content.y += SIN_ENEMY_LIFE_BAR_OFFSET_Y;
    Camera_WorldToView(camera, pos_content, &dst_content.x, &dst_content.y);
    SDL_RenderCopyF(
    renderer, assets->enemy_life_bar_content, &src_content, &dst_content);
}

void EnemySin_Damage(Enemy *self, int damage)
{
    self->life -= damage;
    if (self->life <= 0)
    {
        self->state = ENEMY_DEAD;
    }
}
