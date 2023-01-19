#include "Enemy_triangle.h"
#include "Scene.h"
#include "Enemy.h"
#include "Timer.h"
#include "Math.h"
#include "Bullet.h"
#include "Bullet_Arc_Enemy.h"

// Protos
void EnemyTriangle_Delete(Enemy *self);
void EnemyTriangle_Update(Enemy *self);
void EnemyTriangle_Render(Enemy *self);
void EnemyTriangle_Damage(Enemy *self, int damage);

Enemy *EnemyTriangle_New(Scene *scene, Vec2 position, int life, float shoot_period)
{
    /* --- Base Ini --- */
    Enemy *self = (Enemy*)calloc(1, sizeof(Enemy));
    self->type = ENEMY_TRIANGLE;
    Assets *assets = Scene_GetAssets(scene);
    self->texture = assets->base_enemy;
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

    /* --- Functions bindings --- */
    self->Delete = &EnemyTriangle_Delete;
    self->Update = &EnemyTriangle_Update;
    self->Render = &EnemyTriangle_Render;
    self->Damage = &EnemyTriangle_Damage;
    /* --- --- --- --- --- --- --- */
    return self;
}

void EnemyTriangle_Delete(Enemy *self)
{
    if (!self) return;
    free(self);
}

void EnemyTriangle_Update(Enemy *self)
{
    if (self->accumulator_bullet_shot >= self->shoot_period){
        for(int ang=12.5f; ang>-12.5f; ang-=12.5f){
            Vec2 v = Vec2_Set(-(sinf((90.f-ang)* M_PI / 180.0)*6), cosf((90.f-ang)* M_PI / 180.0)*6);
            Bullet* bullet = BulletArcEnemy_New(self->scene, self->position, v, ang);
            Scene_AppendBullet(self->scene, bullet);
            self->accumulator_bullet_shot =0;
        }
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

void EnemyTriangle_Render(Enemy *self)
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

void EnemyTriangle_Damage(Enemy *self, int damage)
{
    self->life -= damage;
    if (self->life <= 0)
    {
        self->state = ENEMY_DEAD;
    }
}
