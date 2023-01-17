#pragma once

#include "Settings.h"
#include "Math.h"
#include "Enemy.h"

typedef struct Scene_s Scene;
typedef struct Enemy_s Enemy;


/// @brief Structure repr�sentant un ennemi.
typedef struct EnemyDebug_s
{
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
    int hp;
} EnemyDebug;

/// @brief Cr�e un nouvel ennemi.
/// @param scene la sc�ne.
/// @param type le type de l'ennemi.
/// @param position la position de d�part de l'ennemi exprim�e dans le r�f�rentiel monde.
/// @return L'ennemi cr��.
EnemyDebug *EnemyDebug_New(Enemy *enemy, Scene *scene, Vec2 position, int hp);

/// @brief D�truit un ennemi.
/// Cette m�thode est appel�e par la sc�ne.
/// @param self l'ennemi.
void EnemyDebug_Delete(EnemyDebug *self);

/// @brief Met � jour un ennemi.
/// @param self l'ennemi.
void EnemyDebug_Update(EnemyDebug *self);

/// @brief Dessine un ennemi dans le moteur de rendu.
/// @param self l'ennemi.
void EnemyDebug_Render(EnemyDebug *self);

/// @brief Inflige des dommages � un ennemi.
/// @param self l'ennemi.
/// @param damage la quantit� de dommages (nombre de points de vie � perdre).
void EnemyDebug_Damage(EnemyDebug *self, int damage);
