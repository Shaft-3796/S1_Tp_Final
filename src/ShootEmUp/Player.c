#include "Player.h"
#include "Scene.h"
#include "Common.h"
#include "Settings.h"
#include "Bullet.h"
#include "Math.h"
#include "Music.h"

Player *Player_New(Scene *scene)
{
    Player *self = (Player *)calloc(1, sizeof(Player));
    AssertNew(self);

    Assets *assets = Scene_GetAssets(scene);

    self->scene = scene;
    self->position = Vec2_Set(1.0f, 4.5f);
    self->radius = 0.5f;
    self->texture = assets->base_player;
    self->speed = BASE_PLAYER_SPEED_MULTIPLIER;
    self->life = 20;
    self->max_life = 20;

    /* --- Perks --- */
    self->perk_astro = false;
    self->perk_astro_timer = 0;
    self->perk_shield = false;
    self->perk_shield_timer = 0;
    self->shield_radius = 1.f;
    self->power_shoot = false;

    /* --- Anim --- */
    self->animation_timer = 0;
    self->animation_frame = 0;
    self->animating = false;

    return self;
}

void Player_Delete(Player *self)
{
    if (!self) return;
    free(self);
}

void Player_Update(Player *self)
{
// On récupère des infos essentielles (communes à tout objet)
Scene *scene = self->scene;
Input *input = Scene_GetInput(scene);
int mod = 0;
// Mise à jour de la vitesse en fonction de l'état des touches
Vec2 velocity = Vec2_Set(input->hAxis*self->speed, input->vAxis*self->speed);
check:;
// Mise à jour de la position
// New pos = old pos + speed * time
Vec2 new_position = Vec2_Add(self->position,Vec2_Scale(velocity, Timer_GetDelta(g_time)));
// On vérifie que la nouvelle position est dans les limites de l'écran
if (new_position.x > 0.5 && new_position.x < 8 && new_position.y > 0.5 && new_position.y < 8.5)
{
    // ANIMATION
    if(self->position.x != new_position.x || self->position.y != new_position.y)
    {
        self->animating = true;
        self->texture = Scene_GetAssets(scene)->moving_base_player;
        self->animation_timer += Timer_GetDelta(g_time);
        if(self->animation_timer > PLAYER_MOVING_ANIMATION_DURATION)
        {
            self->animation_timer = 0;
            self->animation_frame++;
            if(self->animation_frame >= PLAYER_MOVING_ANIMATION_FRAMES)
                self->animation_frame = 0;
        }
    }
    else
    {
        self->animating = false;
        self->texture = Scene_GetAssets(scene)->base_player;
        self->animation_timer = 0;
        self->animation_frame = 0;
    }
    self->position = new_position;
}
else{
    if(mod==0){
        velocity = Vec2_Set(0, input->vAxis*self->speed);
        mod++;
        goto check;
    }
    else if(mod==1){
        velocity = Vec2_Set(input->hAxis*self->speed, 0);
        mod++;
        goto check;
    }
}


if(self->scene->input->shootPressed)
{
    if(!self->power_shoot){
        Vec2 v = Vec2_Set(6.0f, 0.0f);
        Bullet *bullet = BulletPlayer_New(
        self->scene, self->position, v, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
    }
    else{
        for(int ang=90.0f; ang>-270.0f; ang-=5.0f){
            Vec2 v = Vec2_Set(cosf((90.f-ang)* M_PI / 180.0)*6, sinf((90.f-ang)* M_PI / 180.0)*6);
            Bullet* bullet = BulletPlayer_New(
            self->scene, self->position, v, ang);
            Scene_AppendBullet(self->scene, bullet);
        }
        self->power_shoot = false;
    }
    playSound("Laser_Gun");
}

/* --- Perks --- */
if(self->perk_astro)
{
    self->perk_astro_timer += Timer_GetDelta(g_time);
    if(self->perk_astro_timer >= ASTRO_BUFF_DURATION)
    {
        self->scene->is_astro = false;
        self->scene->astro_respawn_accumulator = 0;
        self->scene->astro_respawn_time = (rand() % (ASTRO_RESPAWN_TIME_MAX - ASTRO_RESPAWN_TIME_MIN + 1)) + ASTRO_RESPAWN_TIME_MIN;
        self->perk_astro = false;
        self->perk_astro_timer = 0.0f;
        self->speed /= ASTRO_SPEED_MULTIPLIER;
        self->scene->backgroundSpeedMultiplier = 1;
    }
}
}

// PROTO
void RenderPlayerUi(Player *self, SDL_Renderer *renderer, Assets* assets, Camera* camera, float scale);

void Player_Render(Player *self) {
// On récupère des infos essentielles (communes à tout objet)
    Scene *scene = self->scene;
    SDL_Renderer *renderer = Scene_GetRenderer(scene);
    Assets *assets = Scene_GetAssets(scene);
    Camera *camera = Scene_GetCamera(scene);
// On calcule la position en pixels en fonction de la position
// en tuiles, la taille de la fenêtre et la taille des textures.
    float scale = Camera_GetWorldToViewScale(camera);  // Taille d'une tuile en pixel
    SDL_FRect dst = {0};
    dst.h = PLAYER_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
    dst.w = PLAYER_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
// Le point de référence est le centre de l'objet
    dst.x -= 0.50f * dst.w;
    dst.y -= 0.50f * dst.h;
// On determine la source de la texture en fonction de la frame si nous sommes en animation
    if (self->animating) {
        SDL_Rect src = {0};
        src.x = self->animation_frame * PLAYER_MOVING_ANIMATION_PERIOD;
        src.y = 0;
        src.w = PLAYER_MOVING_ANIMATION_PERIOD;
        src.h = PLAYER_MOVING_ANIMATION_HEIGHT;
        SDL_RenderCopyExF(renderer, self->texture, &src, &dst, 90.0f, NULL, 0);
    } else {
        // On affiche en position dst (unités en pixels)
        SDL_RenderCopyExF(
                renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);
    }
// On affiche et updtadte le shield
    if (self->perk_shield) {
        SDL_FRect shield_dst = {0};
        shield_dst.h = PLAYER_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
        shield_dst.w = PLAYER_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
        Camera_WorldToView(camera, self->position, &shield_dst.x, &shield_dst.y);
        // Le point de référence est le centre de l'objet
        shield_dst.x -= 0.50f * shield_dst.w;
        shield_dst.y -= 0.50f * shield_dst.h;
        SDL_RenderCopyExF(renderer, assets->shield_render, NULL, &shield_dst, 90.0f, NULL, 0);
        self->perk_shield_timer += Timer_GetDelta(g_time);
        if (self->perk_shield_timer >= SHIELD_BUFF_DURATION) {
            self->scene->is_shield = false;
            self->scene->shield_respawn_accumulator = 0;
            self->scene->shield_respawn_time = (rand() % (SHIELD_RESPAWN_TIME_MAX - SHIELD_RESPAWN_TIME_MIN + 1)) + SHIELD_RESPAWN_TIME_MIN;
            self->perk_shield = false;
            self->perk_shield_timer = 0.0f;
        }
    }

// On update la barre de vie
RenderPlayerUi(self, renderer, assets, camera, scale);

}

void Player_Damage(Player *self, int damage)
{
    self->life -= damage;
    if (self->life <= 0)
    {
        self->life = 0;
        self->state = PLAYER_DEAD;
    }

    // Animation de dégats
    if(self->scene->damageAnimationAccumulator == -1.f){
        self->scene->damageAnimationAccumulator = 0.f;
    }
}

/* Ui */
void RenderPlayerUi(Player *self, SDL_Renderer *renderer, Assets* assets, Camera* camera, float scale)
{
// On render la frame de la barre de vie
SDL_FRect dst = {0};
dst.h = LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
dst.w = LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
Vec2 pos = Vec2_Set(0.2, 9.8);
Camera_WorldToView(camera, pos, &dst.x, &dst.y);
SDL_RenderCopyF(
renderer, assets->player_life_bar_frame, NULL, &dst);


// On rend le contenu de la barre de vie
SDL_Rect src = {0};
src.h = 64;
src.w = 10 + (float)54/((float)self->max_life/self->life);
src.x = 0;
src.y = 0;
SDL_FRect dst2 = {0};
dst2.h = LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
dst2.w = (LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale) * ((float)src.w/64);
Vec2 pos2 = Vec2_Set(0.2, 9.8);
Camera_WorldToView(camera, pos2, &dst2.x, &dst2.y);
SDL_RenderCopyF(
renderer, assets->player_life_bar_content, &src, &dst2);

// On rend la wave actuelle
SDL_Rect src2 = {0};
src2.h = 62;
src2.w = 62;
src2.x = 62 * (self->scene->waveIdx);
src2.y = 0;
SDL_FRect dst3 = {0};
dst3.h = WAVE_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
dst3.w = WAVE_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
Vec2 pos3 = Vec2_Set(2.6, 9.55);
Camera_WorldToView(camera, pos3, &dst3.x, &dst3.y);
SDL_RenderCopyF(
renderer, assets->waves, &src2, &dst3);
}

