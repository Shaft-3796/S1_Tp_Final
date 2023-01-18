#pragma once

#include "Bullet.h"

/// @brief Creates a new Bullet_Player.
/// @param scene The scene where the bullet will be created.
/// @param position The position of the bullet.
/// @param velocity The velocity of the bullet.
Bullet BulletBaseEnemy_New(Scene *scene, Vec2 position, Vec2 velocity, float angle);
