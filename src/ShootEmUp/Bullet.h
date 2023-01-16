#pragma once

#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;

/// @brief Enumération des types possibles pour un projectile.
typedef enum BulletType_e
{
    /// @brief Projectile normal provenant du joueur.
    BULLET_PLAYER,

    /// @brief Projectile normal provenant d'un ennemi.
    BULLET_FIGHTER,
} BulletType;

/// @brief Structure représentant un projectile.
typedef struct Bullet_s
{
    /// @brief Scène associée.
    Scene *scene;

    /// @brief Texture utilisée pour le rendu.
    SDL_Texture *texture;

    /// @brief Position du projectile exprimée dans le référentiel monde.
    Vec2 position;

    /// @brief Vitesse du projectile exprimée dans le référentiel monde.
    Vec2 velocity;

    /// @brief Booléen indiquant si le projectile provient du joueur.
    /// Si il vaut false, il provient d'un ennemi.
    bool fromPlayer;

    /// @brief Type du projectile.
    /// Les valeurs possibles sont définies dans BulletType.
    int type;

    /// @brief Largeur de la texture du projectile
    /// exprimée dans le référentiel monde.
    float worldW;

    /// @brief Hauteur de la texture du projectile
    /// exprimée dans le référentiel monde.
    float worldH;

    /// @brief Rayon du projectile exprimé dans le référentiel monde.
    /// Il est utilisé dans le moteur physique pour tester les collisions.
    float radius;

    /// @brief Angle de rotation du la texture pour le rendu.
    float angle;
} Bullet;

/// @brief Crée un nouveau projectile. Ce dernier doit ensuite être ajouté à la
/// scène via la méthode Scene_AppendBullet().
/// @param scene la scène.
/// @param position la position de départ du projectile exprimée dans le référentiel monde.
/// @param velocity la vitesse du projectile exprimée dans le référentiel monde.
/// @param type le type du projectile.
/// @param angle angle de rotation de la texture pour le rendu.
/// @return Le projectile créé.
Bullet *Bullet_New(Scene *scene, Vec2 position, Vec2 velocity, int type, float angle);

/// @brief Détruit un projectile.
/// Cette méthode est appelée par la scène.
/// @param self le projectile.
void Bullet_Delete(Bullet *self);

/// @brief Met à jour le projectile.
/// @param self le projectile.
void Bullet_Update(Bullet *self);

/// @brief Dessine le projectile dans le moteur de rendu.
/// @param self le projectile.
void Bullet_Render(Bullet *self);
