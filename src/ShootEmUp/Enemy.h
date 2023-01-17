#pragma once

#include "Settings.h"
#include "Math.h"
#include "Enemy_debug.h"

typedef struct Scene_s Scene;

/// @brief Enum�ration repr�sentant les �tats possibles d'un ennemi.
typedef enum EnemyState_e
{
    /// @brief Etat par d�faut d'un ennemi.
    ENEMY_FIRING,

    /// @brief Etat d'un ennemi quand il joue l'animation de destruction.
    ENEMY_DYING,

    /// @brief Etat d'un ennemi quand il est mort et que son animation de
    /// destruction est termin�e.
    ENEMY_DEAD,
} EnemyState;

/// @brief Any enemy is cated to this structure by functions in the scene.c
/// to acess enemies attributes from a void pointer
typedef struct GenericEnemy_s{
    Vec2 position;
    float radius;
    EnemyState state;
} GenericEnemy;

/// --- Manager ---
/// @brief Structure contenant l'ensemble des types ennemis.
typedef enum EnemyTypes_e
{
    ENEMY_BASE,
    ENEMY_ARC,
    ENEMY_DEBUG
} EnemyTypes;


/// @brief Structure repr�sentant un ennemi.
typedef struct Enemy_s
{
    /// @brief Type de l'ennemi
    EnemyTypes type;

    /// @brief Structure de l'ennemi crée
    void *enemy;

} Enemy;

/// @brief Cr�e un nouvel ennemi.
/// @param scene la sc�ne.
/// @param type le type de l'ennemi.
/// @param position la position de d�part de l'ennemi exprim�e dans le r�f�rentiel monde.
/// @return L'ennemi cr��.
Enemy *Enemy_New(EnemyTypes type);

/// @brief D�truit un ennemi.
/// Cette m�thode est appel�e par la sc�ne.
/// @param self l'ennemi.
void Enemy_Delete(Enemy *self);

/// @brief Met � jour un ennemi.
/// @param self l'ennemi.
void Enemy_Update(Enemy *self);

/// @brief Dessine un ennemi dans le moteur de rendu.
/// @param self l'ennemi.
void Enemy_Render(Enemy *self);

/// @brief Inflige des dommages � un ennemi.
/// @param self l'ennemi.
/// @param damage la quantit� de dommages (nombre de points de vie � perdre).
void Enemy_Damage(Enemy *self, int damage);

/// @brief caste un ennemi en son type
GenericEnemy * Enemy_Cast(Enemy * enemy);

