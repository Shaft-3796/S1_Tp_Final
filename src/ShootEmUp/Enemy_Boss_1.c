#include "Enemy_Boss_1.h"
#include "Scene.h"
#include "Enemy.h"
#include "Timer.h"
#include "Math.h"
#include "Bullet.h"
#include "Bullet_Arc_Enemy.h"
#include "Enemy_Sin.h"

// Protos
void EnemyBoss1_Delete(Enemy *self);
void EnemyBoss1_Update(Enemy *self);
void EnemyBoss1_Render(Enemy *self);
void EnemyBoss1_Damage(Enemy *self, int damage);
void PhaseNormal(Enemy *self);
void PhaseAv(Enemy *self);
void SpawnEnemy(Enemy *self);

Enemy *EnemyBoss1_New(Scene *scene, Vec2 position, int life, float shoot_period)
{
    /* --- Base Ini --- */
    Enemy *self = (Enemy*)calloc(1, sizeof(Enemy));
    self->type = ENEMY_BOSS_1;
    Assets *assets = Scene_GetAssets(scene);
    self->texture = assets->boss1;
    self->state = ENEMY_FIRING;
    self->moveSens = VERTICAL;
    self->direction = 1;
    self->worldH = 48;
    self->worldW = 48;
    self->radius = 0.9;
    self->life_bar_accumulator = -1;
    self->max_life = life;
    /* --- --- --- --- */

    /* --- Arguments ini --- */
    self->scene = scene;
    self->position = position;
    self->life = life;

    /* --- Custom Ini --- */
    self->accumulator_bullet_shot = 0;
    self->shoot_period = shoot_period;
    self->accumulator_Teleport = 0;
    self->rafal_period = 0;
    self->bot_counter = 0;

    /* --- Functions bindings --- */
    self->Delete = &EnemyBoss1_Delete;
    self->Update = &EnemyBoss1_Update;
    self->Render = &EnemyBoss1_Render;
    self->Damage = &EnemyBoss1_Damage;
    /* --- --- --- --- --- --- --- */
    return self;
}

void EnemyBoss1_Delete(Enemy *self)
{
    if (!self) return;
    free(self);
}

void EnemyBoss1_Update(Enemy *self)
{
    if (self->life <= 30){
        if(self->accumulator_bullet_shot >= self->shoot_period/2 && self->rafal_period == 0){
            PhaseAv(self);
            self->rafal_period += 1;
        }
        else if(self->accumulator_bullet_shot >= self->shoot_period) {
            PhaseNormal(self);
            self->rafal_period = 0;
        }
    }
    if(self->life > 30){
        if(self->accumulator_bullet_shot >= self->shoot_period){
            PhaseNormal(self);
        }
    }
    if (self->bot_counter == 0 && self->life <= 10){
        SpawnEnemy(self);
        self->bot_counter += 1;
    }
    self->accumulator_bullet_shot += Timer_GetDelta(g_time);
}

void EnemyBoss1_Render(Enemy *self)
{
    // On r??cup??re des infos essentielles (communes ?? tout objet)
    Scene *scene = self->scene;
    SDL_Renderer *renderer = Scene_GetRenderer(scene);
    Assets *assets = Scene_GetAssets(scene);
    Camera *camera = Scene_GetCamera(scene);
    // On calcule la position en pixels en fonction de la position
    // en tuiles, la taille de la fen??tre et la taille des textures.
    float scale = Camera_GetWorldToViewScale(camera);
    SDL_FRect dst = { 0 };
    // Changez 48 par une autre valeur pour grossir ou r??duire l'objet
    dst.h = 125 * PIX_TO_WORLD * scale;
    dst.w = 125 * PIX_TO_WORLD * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
    // Le point de r??f??rence est le centre de l'objet
    dst.x -= 0.5f * dst.w;
    dst.y -= 0.50f * dst.h;
    // On affiche en position dst (unit??s en pixels)
    SDL_RenderCopyExF(renderer, self->texture, NULL, &dst, 270.f, NULL, 0);

    // Rendu de la barre de vie
    // Frame
    SDL_FRect dst_frame = {0};
    dst_frame.h = ENEMY_LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
    dst_frame.w = ENEMY_LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
    Vec2 pos_frame = self->position;
    pos_frame.x += BOSS1_ENEMY_LIFE_BAR_OFFSET_X;
    pos_frame.y += BOSS1_ENEMY_LIFE_BAR_OFFSET_Y;
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
    pos_content.x += BOSS1_ENEMY_LIFE_BAR_OFFSET_X;
    pos_content.y += BOSS1_ENEMY_LIFE_BAR_OFFSET_Y;
    Camera_WorldToView(camera, pos_content, &dst_content.x, &dst_content.y);
    SDL_RenderCopyF(
    renderer, assets->enemy_life_bar_content, &src_content, &dst_content);
}

void EnemyBoss1_Damage(Enemy *self, int damage)
{
    self->life -= damage;
    if (self->life <= 0)
    {
        self->state = ENEMY_DEAD;
    }
}

void PhaseNormal(Enemy *self){
    for(int ang=25.0f; ang>-25.0f; ang-=12.5f){
        Vec2 v = Vec2_Set(-(sinf((90.f-ang)* M_PI / 180.0)*6), cosf((90.f-ang)* M_PI / 180.0)*6);
        Bullet* bullet = BulletArcEnemy_New(self->scene, self->position, v, ang);
        Scene_AppendBullet(self->scene, bullet);
    }
    self->accumulator_bullet_shot = 0;
}

void PhaseAv(Enemy *self){
    for(int ang=90.0f; ang>-270.0f; ang-=10.0f){
        Vec2 v = Vec2_Set(cosf((90.f-ang)* M_PI / 180.0)*6, sinf((90.f-ang)* M_PI / 180.0)*6);
        Bullet* bullet = BulletBaseEnemy_New(self->scene, self->position, v, ang);
        Scene_AppendBullet(self->scene, bullet);
    }
}

void SpawnEnemy(Enemy *self){
    Enemy *enemy = EnemySin_New(self->scene, Vec2_Set(13.0f, 7.75f), 10, 3);
    Scene_AppendEnemy(self->scene, enemy);
    enemy = EnemySin_New(self->scene, Vec2_Set(14.0f, 2.25f), 10, 3);
    Scene_AppendEnemy(self->scene, enemy);
}