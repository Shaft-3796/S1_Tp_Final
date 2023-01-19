#pragma once

#include "Settings.h"
#include "Math.h"
#include "Enemy.h"

typedef struct Scene_s Scene;
typedef struct Enemy_s Enemy;

/// @brief Cr�e un nouvel ennemi.
/// @param scene la sc�ne.
/// @param type le type de l'ennemi.
/// @param position la position de d�part de l'ennemi exprim�e dans le r�f�rentiel monde.
/// @return L'ennemi cr��.
Enemy *EnemyRevert_New(Scene *scene, Vec2 position, int life);

