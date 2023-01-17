#include "Player.h"
#include "Scene.h"
#include "Common.h"
#include "Settings.h"

Player *Player_New(Scene *scene)
{
    Player *self = (Player *)calloc(1, sizeof(Player));
    AssertNew(self);

    Assets *assets = Scene_GetAssets(scene);

    self->scene = scene;
    self->position = Vec2_Set(1.0f, 4.5f);
    self->radius = 0.25f;
    self->texture = assets->base_player;
    self->speed = BASE_PLAYER_SPEED_MULTIPLIER;
    self->life = 20;

    /* --- Perks --- */
    self->perk_astro = false;
    self->perk_astro_timer = 0;

    /* --- Anim --- */
    self->smoke_timer = 0;

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
// Mise à jour de la vitesse en fonction de l'état des touches
Vec2 velocity = Vec2_Set(input->hAxis*self->speed, input->vAxis*self->speed);
// Mise à jour de la position
// New pos = old pos + speed * time
Vec2 new_position = Vec2_Add(self->position,Vec2_Scale(velocity, Timer_GetDelta(g_time)));
// On vérifie que la nouvelle position est dans les limites de l'écran
if (new_position.x > 0.5 && new_position.x < 8 && new_position.y > 0.5 && new_position.y < 8.5)
{
    // On vérifie si la position change, si oui on change la texture.
    if(self->position.x != new_position.x || self->position.y != new_position.y)
    {
        if(self->texture == Scene_GetAssets(scene)->base_player)
        {
            self->texture = Scene_GetAssets(scene)->moving_base_player;
        }
        else if(self->texture == Scene_GetAssets(scene)->moving_base_player)
        {
            self->smoke_timer += Timer_GetDelta(g_time);
            if(self->smoke_timer > PLAYER_SMOKE_SPEED)
            {
                self->smoke_timer = 0;
                self->texture = Scene_GetAssets(scene)->moving_base_player_2;
            }
        }
        else if(self->texture == Scene_GetAssets(scene)->moving_base_player_2)
        {
            self->smoke_timer += Timer_GetDelta(g_time);
            if(self->smoke_timer > PLAYER_SMOKE_SPEED)
            {
                self->smoke_timer = 0;
                self->texture = Scene_GetAssets(scene)->moving_base_player;
            }
        }
    }
    else
    {
        self->texture = Scene_GetAssets(scene)->base_player;
        self->smoke_timer = 0;
    }
    self->position = new_position;
}



if(self->scene->input->shootPressed)
{
   Vec2 velocity = Vec2_Set(4.0f, 0.0f);
Bullet *bullet = Bullet_New(
self->scene, self->position, velocity, BULLET_PLAYER, 90.0f);
Scene_AppendBullet(self->scene, bullet);
}

/* --- Perks --- */
if(self->perk_astro)
{
    self->perk_astro_timer += Timer_GetDelta(g_time);
    if(self->perk_astro_timer >= ASTRO_BUFF_DURATION)
    {
        self->perk_astro = false;
        self->perk_astro_timer = 0.0f;
        self->speed /= ASTRO_SPEED_MULTIPLIER;
        self->scene->backgroundSpeedMultiplier = 1;
    }
}
}

void Player_Render(Player *self)
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
dst.h = PLAYER_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
dst.w = PLAYER_SIZE_MULTIPLIER * PIX_TO_WORLD * scale;
Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
// Le point de référence est le centre de l'objet
dst.x -= 0.50f * dst.w;
dst.y -= 0.50f * dst.h;
// On affiche en position dst (unités en pixels)
SDL_RenderCopyExF(
renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);

/*
// On render la barre de vie
SDL_Rect source = { 0, 27, 64, 10 };
SDL_Rect source_color = { 0, 27, 64/(20/self->life), 10 };
SDL_FRect life_bar_frame_dst = {0};
life_bar_frame_dst.h = LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale * 10.0;
life_bar_frame_dst.w = LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale * 64.0;
life_bar_frame_dst.x = LOGICAL_WIDTH/2-life_bar_frame_dst.w/2;
life_bar_frame_dst.y = 0 + life_bar_frame_dst.h;
SDL_FRect life_bar_color_dst = {0};
life_bar_color_dst.h = LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale * 10.0;
life_bar_color_dst.w = LIFE_BAR_SIZE_MULTIPLIER * PIX_TO_WORLD * scale * 64.0/(20/self->life);
life_bar_color_dst.x = LOGICAL_WIDTH/2-life_bar_color_dst.w/2;
life_bar_color_dst.y = 0 + life_bar_color_dst.h;
//printf("Life bar dst: %f, %f, %f, %f", life_bar_frame_dst.x, life_bar_frame_dst.y, life_bar_frame_dst.w, life_bar_frame_dst.h);
SDL_RenderCopyF(
renderer, assets->lifeBarFrame, &source, &life_bar_frame_dst);
SDL_RenderCopyF(
renderer, assets->lifeBarColor, &source_color, &life_bar_frame_dst);
 */
}



void Player_Damage(Player *self, int damage)
{
    printf("Le potooship a mal\n");
}