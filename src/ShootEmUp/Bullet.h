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

    /// @brief Asteroid
    ASTEROID,
} BulletType;

/// @brief Structure repr�sentant un projectile.
typedef struct Bullet_s
{
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

    /// @brief ordonné initiale du tir.
    float ordInit;
} Bullet;

/// @brief Cr�e un nouveau projectile. Ce dernier doit ensuite �tre ajout� � la
/// sc�ne via la m�thode Scene_AppendBullet().
/// @param scene la sc�ne.
/// @param position la position de d�part du projectile exprim�e dans le r�f�rentiel monde.
/// @param velocity la vitesse du projectile exprim�e dans le r�f�rentiel monde.
/// @param type le type du projectile.
/// @param angle angle de rotation de la texture pour le rendu.
/// @return Le projectile cr��.
Bullet *Bullet_New(Scene *scene, Vec2 position, Vec2 velocity, int type, float angle);

/// @brief D�truit un projectile.
/// Cette m�thode est appel�e par la sc�ne.
/// @param self le projectile.
void Bullet_Delete(Bullet *self);

/// @brief Met � jour le projectile.
/// @param self le projectile.
void Bullet_Update(Bullet *self);

/// @brief Dessine le projectile dans le moteur de rendu.
/// @param self le projectile.
void Bullet_Render(Bullet *self);

/// @brief Shortcut function for asteroid creation
Bullet* Asteroid_New(Scene *scene, int y_pos, float angle);
