#include "Player.h"
#include "Scene.h"
#include "Common.h"

Player *Player_New(Scene *scene)
{
    Player *self = (Player *)calloc(1, sizeof(Player));
    AssertNew(self);

    Assets *assets = Scene_GetAssets(scene);

    self->scene = scene;
    self->position = Vec2_Set(1.0f, 4.5f);
    self->radius = 0.25f;

    return self;
}

void Player_Delete(Player *self)
{
    if (!self) return;
    free(self);
}

void Player_Update(Player *self)
{

}

void Player_Render(Player *self)
{

}

void Player_Damage(Player *self, int damage)
{
    printf("Le potooship a mal\n");
}