#pragma once

#include "Settings.h"
#include "Common.h"

#include "Assets.h"
#include "Camera.h"
#include "Input.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_Base.h"
#include "Perks.h"
#include "Bullet.h"
#include "Bullet_Base_Enemy.h"
#include "Bullet_Player.h"
#include "Bullet_Asteroid.h"
#include "Bullet_Sin_Enemy.h"


// Nombre maximal d'ennemis actifs dans un niveau.
#define ENEMY_CAPACITY 32

// Nombre maximal de projectiles actifs dans un niveau.
#define BULLET_CAPACITY 1500

// Nombre maximal de Perk.
#define PERKS_CAPACITY 32

/// @brief Structure repr�sentant la sc�ne principale du jeu (niveau).
typedef struct Scene_s
{
    /// @brief Moteur de rendu.
    SDL_Renderer *renderer;

    /// @brief Assets de la sc�ne (textures, musiques, sons...)
    Assets *assets;

    /// @brief Cam�ra par laquelle est vue la sc�ne.
    Camera *camera;

    /// @brief Entr�e utilisateur.
    Input *input;

    /// @brief Joueur principal.
    Player *player;

    /// @brief Tableau contenant les ennemis courrants.
    Enemy *enemies[ENEMY_CAPACITY];

    /// @brief Nombre d'ennemis courrants.
    int enemyCount;

    /// @brief Tableau contenant les projectiles courrants.
    Bullet *bullets[BULLET_CAPACITY];

    /// @brief Nombre de projectiles courrants.
    int bulletCount;

    /// @brief Indice de la vague d'ennemis courrante.
    /// Utilis� pour impl�menter un niveau complet.
    int waveIdx;

    ///@brief Vie max du joueur pendant le niveau
    int maxLife;

    /* --- Perk --- */
    /// @brief Tableau contenant les Perk courrants.
    Perk *perk[PERKS_CAPACITY];

    /// @brief Nombre de Perk courrants.
    int perkCount;

    // Astro
    bool is_astro;
    float astro_respawn_accumulator;
    float astro_respawn_time;

    // Shield
    bool is_shield;
    float shield_respawn_accumulator;
    float shield_respawn_time;

    // Lifeup
    bool is_lifeup;
    float lifeup_respawn_accumulator;
    float lifeup_respawn_time;

    // powershoot
    bool is_powershoot;
    float powershoot_respawn_accumulator;
    float powershoot_respawn_time;

    // Asteroid
    int asteroid_to_spawn;
    float asteroid_respawn_accumulator;

    /* --- Background rendering --- */
    /// @brief Position du calque de fond.
    SDL_Rect layer0Pos;

    /// @brief Position du calque de fond.
    SDL_Rect layer1Pos;

    /// @brief Multiplicateur de vitesse du calque de fond.
    float backgroundSpeedMultiplier;

    /* --- Final animation --- */
    /// @brief Accumulateur de temps pour l'animation de fin.
    float finalAnimationAccumulator;

    /// @brief Opacité à modifier pour l'anim de fin.
    int opacity;

    /* --- Damage animation --- */
    /// @brief Accumulateur de temps pour l'animation de dégats.
    float damageAnimationAccumulator;

    /* -_-_-_- LEVEL DESIGN -_-_-_- */


} Scene;

/// @brief Cr�e la sc�ne principale du jeu.
/// @param renderer moteur de rendu.
/// @return La sc�ne cr��e.
Scene *Scene_New(SDL_Renderer *renderer);

/// @brief D�truit la sc�ne principale.
/// @param self la sc�ne.
void Scene_Delete(Scene *self);

/// @brief Met � jour la sc�ne.
/// Cette fonction est appel�e � chaque tour de la boucle de rendu.
/// @param self la sc�ne.
/// @return true s'il faut quitter la boucle de rendu, false sinon.
bool Scene_Update(Scene *self);

/// @brief Dessine la sc�ne dans le moteur de rendu.
/// @param self la sc�ne.
void Scene_Render(Scene *self);

/// @brief Ajoute un nouveau projectile � la sc�ne.
/// @param self la sc�ne.
/// @param bullet le projectile � ajouter (correctement initialis�).
void Scene_AppendBullet(Scene *self, Bullet *bullet);

/// @brief Supprime un projectile de la sc�ne.
/// @param self la sc�ne.
/// @param index l'indice du projectile � supprimer dans le tableau self->bullets.
void Scene_RemoveBullet(Scene *self, int index);

/// @brief Ajoute un nouvel ennemi � la sc�ne.
/// @param self la sc�ne.
/// @param enemy l'ennemi � ajouter (correctement initialis�).
void Scene_AppendEnemy(Scene *self, Enemy *enemy);

/// @brief Supprime un ennemi de la sc�ne.
/// @param self la sc�ne.
/// @param index l'indice du l'ennemi � supprimer dans le tableau self->enemies.
void Scene_RemoveEnemy(Scene *self, int index);

/* --- Perk --- */
/// @brief Ajoute un nouveau perk � la sc�ne.
/// @param self la sc�ne.
/// @param perk le perk � ajouter (correctement initialis�).
void Scene_AppendPerk(Scene *self, Perk *perk);

/// @brief Supprime un perk de la sc�ne.
/// @param self la sc�ne.
/// @param index l'indice du perk � supprimer dans le tableau self->Perk.
void Scene_RemovePerk(Scene *self, int index);

/// @brief Renvoie le moteur de rendu de la sc�ne.
/// @param self la sc�ne.
/// @return Le moteur de rendu de la sc�ne.
INLINE SDL_Renderer *Scene_GetRenderer(Scene *self)
{
    return self->renderer;
}

/// @brief Renvoie les assets de la sc�ne.
/// @param self la sc�ne.
/// @return Les assets de la sc�ne.
INLINE Assets *Scene_GetAssets(Scene *self)
{
    return self->assets;
}

/// @brief Renvoie la cam�ra de la sc�ne.
/// @param self la sc�ne.
/// @return La cam�ra de la sc�ne.
INLINE Camera *Scene_GetCamera(Scene *self)
{
    return self->camera;
}

/// @brief Renvoie les entr�e utilisateur de la sc�ne.
/// @param self la sc�ne.
/// @return Les entr�e utilisateur de la sc�ne.
INLINE Input *Scene_GetInput(Scene *self)
{
    return self->input;
}
