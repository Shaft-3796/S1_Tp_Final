#include "Enemy_Sin.h"
#include "Scene.h"
#include "Enemy.h"
#include "Timer.h"
#include "Math.h"
#include "Bullet.h"

// Protos
void EnemySin_Delete(Enemy *self);
void EnemySin_Update(Enemy *self);
void EnemySin_Render(Enemy *self);
void EnemySin_Damage(Enemy *self, int damage);

Enemy *EnemySin_New(Scene *scene, Vec2 position, int life)
{
    /* --- Base Ini --- */
    Enemy *self = (Enemy*)calloc(1, sizeof(Enemy));
    self->type = ENEMY_SIN;
    Assets *assets = Scene_GetAssets(scene);
    self->texture = assets->base_enemy;
    self->state = ENEMY_FIRING;
    self->worldH = 48;
    self->worldW = 48;
    self->radius = 0.5;
    /* --- --- --- --- */

    /* --- Custom Ini --- */
    self->scene = scene;
    self->position = position;
    self->life = life;
    self->moveSens = VERTICAL;
    self->direction = 1;
    self->accumulator_bullet_shot = 0;

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
    while (self->accumulator_bullet_shot >= 1){
        Vec2 velocity = Vec2_Set(-4.0f, 0.0f);
        Bullet *bullet = BulletSinEnemy_New(self->scene, self->position, velocity, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
        bullet->ordInit = self->position.y;
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
}

void EnemySin_Damage(Enemy *self, int damage)
{
    self->life -= damage;
    if (self->life <= 0)
    {
        self->state = ENEMY_DEAD;
    }
}
