#include "Enemy_Base.h"
#include "Scene.h"
#include "Enemy.h"

EnemyBase *EnemyBase_New(Enemy *enemy, Scene *scene, Vec2 position, int life)
{
    EnemyBase *self = (EnemyBase *)calloc(1, sizeof(EnemyBase));
    AssertNew(self);

    self->scene = scene;
    self->position = position;
    self->state = ENEMY_FIRING;
    self->texture = assets->base_enemy;
    self->life = life;

    Assets *assets = Scene_GetAssets(self->scene);
    self->texture = assets->fighter;

    /* DO NOT REMOVE */
    enemy->enemy = self;

    return self;
}

void EnemyBase_Delete(EnemyBase *self)
{
    if (!self) return;
    free(self);
}

void EnemyBase_Update(EnemyBase *self)
{
    
}

void EnemyBase_Render(EnemyBase *self)
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
    SDL_RenderCopyExF(renderer, self->texture, NULL, &dst, 270.f, NULL, 0);
}

void EnemyBase_Damage(EnemyBase *self, int damage)
{
    self->life -= damage;
    if (self->life <= 0)
    {
        self->state = ENEMY_DEAD;
    }
}
