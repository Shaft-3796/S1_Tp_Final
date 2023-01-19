#pragma once

#include "Settings.h"
#include "Math.h"
#include "Enemy_debug.h"
#include "Bullet.h"

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

typedef enum EnemyMove_e
{
    VERTICAL,
    HORIZONTAL,
    TELEPORT,
} EnemyMove;


/// @brief Structure contenant l'ensemble des types ennemis.
typedef enum EnemyTypes_e
{
    ENEMY_BASE,
    ENEMY_ARC,
    ENEMY_DEBUG,
    ENEMY_TELEPORT,
    ENEMY_SIN,
    ENEMY_BOSS_1,
    ENEMY_BOSS_2,
    ENEMY_RAFAL,
    ENEMY_TRIANGLE,
    ENEMY_REVERT,
    ENEMY_BOMB,
    ENEMY_AUTO
} EnemyTypes;


/// @brief Structure repr�sentant un ennemi.
typedef struct Enemy_s
{
    /* --- VANILLA --- */
    /// @brief Type de l'ennemi
    EnemyTypes type;

    /// @brief type de déplacement.
    EnemyMove moveSens;

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

    /// @brief Vie max de l'ennemi.
    int max_life;

    // @brief Accumulateur pour l'affichage de la barre de vie
    float life_bar_accumulator;

    /* --- Custom --- */
    /// @brief direction de déplacement.
    int direction;
    /// @brief temps avant tir.
    float accumulator_bullet_shot;
    /// @brief temps avant prochain tir.
    float shoot_period;
    /// @brief temps avant teleportation.
    float accumulator_Teleport;
    /// @brief temps avant rafale.
    int rafal_period;
    /// @brief temps avant rafale.
    int bot_counter;

    /* --- FUNCTIONS --- */
    /// @brief Pointeur sur fonction de destruction de l'ennemi.
    void (*Delete)(struct Enemy_s *self);

    /// @brief Pointeur sur fonction de mise � jour de l'ennemi.
    void (*Update)(struct Enemy_s *self);

    /// @brief Pointeur sur fonction de rendu de l'ennemi.
    void (*Render)(struct Enemy_s *self);

    /// @brief Pointeur sur fonction d'infligeance de dommages � l'ennemi.
    void (*Damage)(struct Enemy_s *self, int damage);

    /* --- Custom --- */
    void (*Revert)(struct Enemy_s *self, Bullet* bullet);

} Enemy;


