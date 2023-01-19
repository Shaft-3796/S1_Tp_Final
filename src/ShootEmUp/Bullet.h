#pragma once

#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;

/// @brief Enum�ration des types possibles pour un projectile.
typedef enum BulletType_e
{
    /// @brief Projectile normal provenant du joueur.
    BULLET_PLAYER,

    /// @brief Projectile normal provenant d'un ennemi.
    BULLET_FIGHTER,

    /// @brief Projectile normal provenant d'un ennemi basique.
    BULLET_BASE_ENEMY,

    /// @brief Projectile normal provenant d'un ennemi sin.
    BULLET_SIN_ENEMY,

    BULLET_ARC_ENEMY,

    BULLET_AUTO,

    /// @brief Asteroid
    ASTEROID,
} BulletType;

/// @brief Structure repr�sentant un projectile.
typedef struct Bullet_s
{
    /* --- VANILLA --- */
    /// @brief Sc�ne associ�e.
    Scene *scene;

    /// @brief Texture utilis�e pour le rendu.
    SDL_Texture *texture;

    /// @brief Position du projectile exprim�e dans le r�f�rentiel monde.
    Vec2 position;

    /// @brief Vitesse du projectile exprim�e dans le r�f�rentiel monde.
    Vec2 velocity;

    /// @brief Bool�en indiquant si le projectile provient du joueur.
    /// Si il vaut false, il provient d'un ennemi.
    bool fromPlayer;

    /// @brief Type du projectile.
    /// Les valeurs possibles sont d�finies dans BulletType.
    int type;

    /// @brief Largeur de la texture du projectile
    /// exprim�e dans le r�f�rentiel monde.
    float worldW;

    /// @brief Hauteur de la texture du projectile
    /// exprim�e dans le r�f�rentiel monde.
    float worldH;

    /// @brief Rayon du projectile exprim� dans le r�f�rentiel monde.
    /// Il est utilis� dans le moteur physique pour tester les collisions.
    float radius;

    /// @brief Angle de rotation du la texture pour le rendu.
    float angle;

    /* --- Custom --- */
    /// @brief periode d'oscillation.
    float oscillation_period;

    /// @brief acumulateur d'oscillations.
    float oscillation_acumulator;


    bool follow_disable;


    /* --- Function Pointers --- */
    /// @brief Pointeur sur fonction de destruction de l'ennemi.
    void (*Delete)(struct Bullet_s *self);

    /// @brief Pointeur sur fonction de mise � jour de l'ennemi.
    void (*Update)(struct Bullet_s *self);

    /// @brief Pointeur sur fonction de rendu de l'ennemi.
    void (*Render)(struct Bullet_s *self);
} Bullet;