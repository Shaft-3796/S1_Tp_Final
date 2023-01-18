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
Enemy *EnemySin_New(Scene *scene, Vec2 position, int life);

/// @brief D�truit un ennemi.
/// Cette m�thode est appel�e par la sc�ne.
/// @param self l'ennemi.
void EnemySin_Delete(Enemy *self);

/// @brief Met � jour un ennemi.
/// @param self l'ennemi.  
void EnemySin_Update(Enemy *self);

/// @brief Dessine un ennemi dans le moteur de rendu.
/// @param self l'ennemi.
void EnemySin_Render(Enemy *self);

/// @brief Inflige des dommages � un ennemi.
/// @param self l'ennemi.
/// @param damage la quantit� de dommages (nombre de points de vie � perdre).
void EnemySin_Damage(Enemy *self, int damage);
