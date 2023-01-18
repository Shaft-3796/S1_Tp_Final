#ifndef S1_TP_FINAL_BULLET_PLAYER_H
#define S1_TP_FINAL_BULLET_PLAYER_H

#endif //S1_TP_FINAL_BULLET_PLAYER_H

#include "Bullet.h"
#include "Scene.h"
#include "Math.h"

/// @brief Creates a new Bullet_Player.
/// @param scene The scene where the bullet will be created.
/// @param position The position of the bullet.
/// @param velocity The velocity of the bullet.
Bullet* BulletSinEnemy_New(Scene *scene, Vec2 position, Vec2 velocity, float angle, float oscillation_period);
