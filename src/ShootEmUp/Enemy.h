#pragma once

#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;

/// @brief Enumération représentant les états possibles d'un ennemi.
typedef enum EnemyState_e
{
    /// @brief Etat par défaut d'un ennemi.
    ENEMY_FIRING,

    /// @brief Etat d'un ennemi quand il joue l'animation de destruction.
    ENEMY_DYING,

    /// @brief Etat d'un ennemi quand il est mort et que son animation de
    /// destruction est terminée.
    ENEMY_DEAD,
} EnemyState;

/// @brief Enumération des types possibles pour un ennemi.
typedef enum EnemyType_e
{
    /// @brief Ennemi simple.
    ENEMY_FIGHTER,
} EnemyType;

/// @brief Structure représentant un ennemi.
typedef struct Enemy_s
{
    /// @brief Scène associée.
    Scene *scene;

    /// @brief Texture utilisée pour le rendu.
    SDL_Texture *texture;

    /// @brief Position de l'ennemi exprimée dans le référentiel monde.
    Vec2 position;

    /// @brief Type de l'ennemi.
    /// Les valeurs possibles sont définies dans EnemyType.
    int type;

    /// @brief Etat de l'ennemi.
    /// Les valeurs possibles sont définies dans EnemyState.
    int state;

    /// @brief Largeur de la texture de l'ennemi
    /// exprimée dans le référentiel monde.
    float worldW;

    /// @brief Hauteur de la texture de l'ennemi
    /// exprimée dans le référentiel monde.
    float worldH;

    /// @brief Rayon de l'ennemi exprimé dans le référentiel monde.
    /// Il est utilisé dans le moteur physique pour tester les collisions.
    float radius;
} Enemy;

/// @brief Crée un nouvel ennemi.
/// @param scene la scène.
/// @param type le type de l'ennemi.
/// @param position la position de départ de l'ennemi exprimée dans le référentiel monde.
/// @return L'ennemi créé.
Enemy *Enemy_New(Scene *scene, int type, Vec2 position);

/// @brief Détruit un ennemi.
/// Cette méthode est appelée par la scène.
/// @param self l'ennemi.
void Enemy_Delete(Enemy *self);

/// @brief Met à jour un ennemi.
/// @param self l'ennemi.
void Enemy_Update(Enemy *self);

/// @brief Dessine un ennemi dans le moteur de rendu.
/// @param self l'ennemi.
void Enemy_Render(Enemy *self);

/// @brief Inflige des dommages à un ennemi.
/// @param self l'ennemi.
/// @param damage la quantité de dommages (nombre de points de vie à perdre).
void Enemy_Damage(Enemy *self, int damage);
