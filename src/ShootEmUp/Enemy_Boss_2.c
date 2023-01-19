#include "Enemy_Boss_2.h"
#include "Scene.h"
#include "Enemy.h"
#include "Timer.h"
#include "Math.h"
#include "Bullet.h"
#include "Bullet_Bomb_Enemy.h"
#include "Bullet_Auto.h"
#include "Bullet_Base_Enemy.h"
#include "Enemy_Sin.h"

// Protos
void EnemyBoss2_Delete(Enemy *self);
void EnemyBoss2_Update(Enemy *self);
void EnemyBoss2_Render(Enemy *self);
void EnemyBoss2_Damage(Enemy *self, int damage);
void PhaseNormalB2(Enemy *self);
void PhaseAvB2(Enemy *self);
void SpawnEnemyB2(Enemy *self);

Enemy *EnemyBoss2_New(Scene *scene, Vec2 position, int life, float shoot_period)
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
    self->radius = 0.5;
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
    self->Delete = &EnemyBoss2_Delete;
    self->Update = &EnemyBoss2_Update;
    self->Render = &EnemyBoss2_Render;
    self->Damage = &EnemyBoss2_Damage;
    /* --- --- --- --- --- --- --- */
    return self;
}

void EnemyBoss2_Delete(Enemy *self)
{
    if (!self) return;
    free(self);
}

void EnemyBoss2_Update(Enemy *self)
{
    if (self->life > 30){
        PhaseNormalB2(self);
    }
    if(self->life <= 30){
        PhaseAvB2(self);
    }
    if (self->bot_counter == 0 && self->life <= 10){
        SpawnEnemyB2(self);
        self->bot_counter += 1;
    }
    self->accumulator_bullet_shot += Timer_GetDelta(g_time);
}

void EnemyBoss2_Render(Enemy *self)
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
}

void EnemyBoss2_Damage(Enemy *self, int damage)
{
    self->life -= damage;
    if (self->life <= 0)
    {
        self->state = ENEMY_DEAD;
    }
}

void PhaseNormalB2(Enemy *self){
    if(self->accumulator_bullet_shot >= self->shoot_period && self->rafal_period == 0) {
        for(int ang=90.0f; ang>-270.0f; ang-=10.0f){
            Vec2 v = Vec2_Set(cosf((90.f-ang)* M_PI / 180.0)*6, sinf((90.f-ang)* M_PI / 180.0)*6);
            Bullet* bullet = BulletBaseEnemy_New(self->scene, self->position, v, ang);
            Scene_AppendBullet(self->scene, bullet);
        }
        self->rafal_period += 1;
    }
    else if(self->accumulator_bullet_shot >= self->shoot_period*2){
        Vec2 v = Vec2_Set(-2.0f, 0.0f);
        Vec2 bulletPosition = self->position;
        bulletPosition.y += 1.0f;
        Bullet *bullet = BulletBombEnemy_New(self->scene, bulletPosition, v, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
        bulletPosition.y -= 2.0f;
        bullet = BulletBombEnemy_New(self->scene, bulletPosition, v, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
        self->accumulator_bullet_shot = 0;
        self->rafal_period = 0;
    }
}

void PhaseAvB2(Enemy *self){
    if(self->accumulator_bullet_shot >= self->shoot_period && self->rafal_period == 0) {
        for(int ang=90.0f; ang>-270.0f; ang-=10.0f){
            Vec2 v = Vec2_Set(cosf((90.f-ang)* M_PI / 180.0)*6, sinf((90.f-ang)* M_PI / 180.0)*6);
            Bullet* bullet = BulletBaseEnemy_New(self->scene, self->position, v, ang);
            Scene_AppendBullet(self->scene, bullet);
        }
        self->rafal_period += 1;
    }
    else if(self->accumulator_bullet_shot >= self->shoot_period && self->rafal_period == 1){
        Vec2 velocity = Vec2_Set(-4.0f, 0.0f);
        Bullet *bullet = BulletAuto_New(self->scene, self->position, velocity, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
        self->rafal_period += 1;
    }
    else if(self->accumulator_bullet_shot >= self->shoot_period*2){
        Vec2 v = Vec2_Set(-2.0f, 0.0f);
        Vec2 bulletPosition = self->position;
        bulletPosition.y += 1.0f;
        Bullet *bullet = BulletBombEnemy_New(self->scene, bulletPosition, v, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
        bulletPosition.y -= 2.0f;
        bullet = BulletBombEnemy_New(self->scene, bulletPosition, v, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
        self->accumulator_bullet_shot = 0;
        self->rafal_period = 0;
    }
}

void SpawnEnemyB2(Enemy *self){
    Enemy *enemy = EnemySin_New(self->scene, Vec2_Set(13.0f, 7.75f), 10, 3);
    Scene_AppendEnemy(self->scene, enemy);
    enemy = EnemySin_New(self->scene, Vec2_Set(14.0f, 2.25f), 10, 3);
    Scene_AppendEnemy(self->scene, enemy);
}