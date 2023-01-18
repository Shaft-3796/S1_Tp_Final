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
    /* --- VANILLA --- */
    /// @brief Type de l'ennemi
    EnemyTypes type;

    /// @brief Sc�ne associ�e.
    Scene *scene;

    /// @brief Texture utilis�e pour le rendu.
    SDL_Texture *texture;

    /// @brief Position de l'ennemi exprim�e dans le r�f�rentiel monde.
    Vec2 position;

    /// @brief Etat de l'ennemi.
    /// Les valeurs possibles sont d�finies dans EnemyState.
    int state;

    /// @brief Largeur de la texture de l'ennemi
    /// exprim�e dans le r�f�rentiel monde.
    float worldW;

    /// @brief Hauteur de la texture de l'ennemi
    /// exprim�e dans le r�f�rentiel monde.
    float worldH;

    /// @brief Rayon de l'ennemi exprim� dans le r�f�rentiel monde.
    /// Il est utilis� dans le moteur physique pour tester les collisions.
    float radius;

    /// @brief Vie de l'ennemi.
    int life;

    float accumulator_bullet_shot;

    /* --- Custom --- */

    /* --- VANILLA --- */
    /// @brief Pointeur sur fonction de destruction de l'ennemi.
    void (*Delete)(struct Enemy_s *self);

    /// @brief Pointeur sur fonction de mise � jour de l'ennemi.
    void (*Update)(struct Enemy_s *self);

    /// @brief Pointeur sur fonction de rendu de l'ennemi.
    void (*Render)(struct Enemy_s *self);

    /// @brief Pointeur sur fonction d'infligeance de dommages � l'ennemi.
    void (*Damage)(struct Enemy_s *self, int damage);

} Enemy;


