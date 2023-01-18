#include "Bullet.h"
#include "Common.h"
#include "Scene.h"

Bullet *Bullet_New(Scene *scene, Vec2 position, Vec2 velocity, int type, float angle, float ordInit)
{
    Bullet *self = (Bullet *)calloc(1, sizeof(Bullet));
    AssertNew(self);

    self->position = position;
    self->velocity = velocity;
    self->type = type;
    self->angle = angle;
    self->scene = scene;
    self->ordInit = ordInit;
    self->fromPlayer = false;

    Assets *assets = Scene_GetAssets(scene);
    switch (type)
    {
    case BULLET_FIGHTER:
        self->texture = assets->fighterBullet;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = false;
        break;
    case BULLET_BASE_ENEMY:
        self->texture = assets->base_enemy_bullet;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = false;
        break;
    case BULLET_SIN_ENEMY:
        self->texture = assets->base_enemy_bullet;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = false;
        break;
    default:
    case BULLET_PLAYER:
        self->texture = assets->base_player_bullets;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = true;
        break;

    case ASTEROID:
        self->texture = assets->asteroid;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = false;
        break;
    }

    return self;
}

void Bullet_Delete(Bullet *self)
{
    if (!self) return;
    free(self);
}

void Bullet_Update(Bullet *self)
{
    switch (type) {
        case BULLET_SIN_ENEMY:
            if(self->position.y >= self->ordInit+1){
                self->position = Vec2_Add(self->position,Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));
                self->position.y = -1;
            }
            else{
                self->position = Vec2_Add(self->position,Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));
                self->position.y = 1;
            }
            break;
        default:
            // On récupère des infos essentielles (communes à tout objet)
            Scene *scene = self->scene;
            Input *input = Scene_GetInput(scene);
            // Mise à jour de la vitesse en fonction de l'état des touches
            // Mise à jour de la position
            // New pos = old pos + speed * time
            self->position = Vec2_Add(self->position,Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));
            break;
    }
}

void Bullet_Render(Bullet *self)
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
switch (self->type) {
    case BULLET_PLAYER:
        float multiplier = 1.f;
        if(self->scene->input->resize_bullets){multiplier = 0.25f;
        }
        dst.h = PLAYER_SIZE_MULTIPLIER * PIX_TO_WORLD * scale * multiplier;
        dst.w = PLAYER_SIZE_MULTIPLIER * PIX_TO_WORLD * scale * multiplier;
        break;
    case ASTEROID:
        dst.h = ASTEROID_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
        dst.w = ASTEROID_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
        break;
    default:
        dst.h = BULLET_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
        dst.w = BULLET_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
        break;

}

Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
// Le point de référence est le centre de l'objet
dst.x -= 0.50f * dst.w;
dst.y -= 0.50f * dst.h;
    switch (self->type) {
        case BULLET_BASE_ENEMY:
            dst.x -= 0.25f * dst.w;
            break;
        default:
            break;
    }
// On affiche en position dst (unités en pixels)
SDL_RenderCopyExF(
renderer, self->texture, NULL, &dst, self->angle, NULL, 0);
}

/* --- Gameplay --- */

// Shortcut function to create an asteroid
Bullet* Asteroid_New(Scene *scene, int y_pos, float angle){
    Vec2 position = {18, y_pos};
    Vec2 velocity = {-1*ASTEROID_SPEED_MULTIPLIER, 0};
    return Bullet_New(scene, position, velocity, ASTEROID, angle);
}