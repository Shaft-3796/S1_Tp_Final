#include "Enemy.h"
#include "Enemy_debug.h"
#include "Scene.h"

Enemy *Enemy_New(EnemyTypes type)
{
    Enemy *self = (Enemy *)calloc(1, sizeof(Enemy));
    self->type = type;
    return self;
}


void Enemy_Delete(Enemy *self)
{
    switch (self->type) {
        case ENEMY_DEBUG:
            EnemyDebug_Delete(self->enemy);
            break;
        default:
            break;
    }
    if (!self) return;
    free(self);
}

void Enemy_Update(Enemy *self)
{
    switch (self->type) {
        case ENEMY_DEBUG:
            EnemyDebug_Update(self->enemy);
            break;
        default:
            break;
    }
}

void Enemy_Render(Enemy *self)
{
switch (self->type) {
        case ENEMY_DEBUG:
            EnemyDebug_Render(self->enemy);
            break;
        case ENEMY_BASE:
            EnemyBase_Render(self->enemy);
            break;
        default:
            break;
    }
}

void Enemy_Damage(Enemy *self, int damage)
{
    switch (self->type) {
        case ENEMY_DEBUG:
            EnemyDebug_Damage(self->enemy, damage);
            break;
        default:
            break;
    }
}

GenericEnemy * Enemy_Cast(Enemy* enemy)
{
    return (GenericEnemy *)(enemy->enemy);
}
