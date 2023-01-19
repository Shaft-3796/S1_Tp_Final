#pragma once

#include "Settings.h"
#include "Math.h"
#include "Player.h"

typedef struct Scene_s Scene;

typedef enum PerkType_e
{
    PERK_TYPE_ASTRO,
    PERK_TYPE_SHIELD,
    PERK_TYPE_LIFEUP,
    PERK_TYPE_POWERSHOOT
} PerkType;

/// @brief Structure repr�sentant une Perk
typedef struct Perk_s
{
    /// @brief Sc�ne associ�e.
    Scene *scene;

    /// @brief Texture utilis�e pour le rendu.
    SDL_Texture *texture;

    /// @brief Position de la Perk exprim�e dans le r�f�rentiel monde.
    Vec2 position;

    /// @brief Type de Perk.
    PerkType type;

    /// @brief Rayon de la Perk exprim� dans le r�f�rentiel monde.
    /// Il est utilis� dans le moteur physique pour tester les collisions.
    float radius;

    /// @brief angle de rotation de la Perk.
    float angle;

    /// @brief Temps �coul� depuis le d�but de l'animation de rotation.
    float rotate_timer;

} Perk;

/// @brief Cr�e une nouvelle Perk.
/// @param scene la sc�ne.
/// @return La Perk.
Perk *Perk_New(Scene *scene, PerkType type, Vec2 position);

/// @brief D�truit une Perk.
/// @param self la Perk.
void Perk_Delete(Perk *self);

/// @brief Met � jour la Perk.
/// @param self la Perk.
void Perk_Update(Perk *self);

/// @brief Dessine la Perk dans le moteur de rendu.
/// @param self la Perk.
void Perk_Render(Perk *self);

/// @brief applique les effets de la Perk.
/// @param self la Perk.
/// @param player le joueur.
void Perk_Apply_Effect(Perk *self, Player *player);

