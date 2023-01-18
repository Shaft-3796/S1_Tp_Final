#pragma once

#include "Settings.h"
#include "Common.h"

#include "Assets.h"
#include "Camera.h"
#include "MenuInput.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Perks.h"

/// @brief Structure repr�sentant la sc�ne principale du jeu (niveau).
typedef struct DeathScene_s
{
    /// @brief Moteur de rendu.
    SDL_Renderer *renderer;

    /// @brief Assets de la sc�ne (textures, musiques, sons...)
    Assets *assets;

    /// @brief Cam�ra par laquelle est vue la sc�ne.
    Camera *camera;

    /// @brief Entr�e utilisateur.
    MenuInput *input;


    /* --- Background rendering --- */
    float angle;
    float angle_accumulator;

} DeathScene;

/// @brief Cr�e la sc�ne principale du jeu.
/// @param renderer moteur de rendu.
/// @return La sc�ne cr��e.
DeathScene *DeathScene_New(SDL_Renderer *renderer);

/// @brief D�truit la sc�ne principale.
/// @param self la sc�ne.
void DeathScene_Delete(DeathScene *self);

/// @brief Met � jour la sc�ne.
/// Cette fonction est appel�e � chaque tour de la boucle de rendu.
/// @param self la sc�ne.
/// @return true s'il faut quitter la boucle de rendu, false sinon.
bool DeathScene_Update(DeathScene *self);

/// @brief Dessine la sc�ne dans le moteur de rendu.
/// @param self la sc�ne.
void DeathScene_Render(DeathScene *self);

/// @brief Renvoie le moteur de rendu de la sc�ne.
/// @param self la sc�ne.
/// @return Le moteur de rendu de la sc�ne.
INLINE SDL_Renderer *DeathScene_GetRenderer(DeathScene *self)
{
    return self->renderer;
}

/// @brief Renvoie les assets de la sc�ne.
/// @param self la sc�ne.
/// @return Les assets de la sc�ne.
INLINE Assets *DeathScene_GetAssets(DeathScene *self)
{
    return self->assets;
}

/// @brief Renvoie la cam�ra de la sc�ne.
/// @param self la sc�ne.
/// @return La cam�ra de la sc�ne.
INLINE Camera *DeathScene_GetCamera(DeathScene *self)
{
    return self->camera;
}

/// @brief Renvoie les entr�e utilisateur de la sc�ne.
/// @param self la sc�ne.
/// @return Les entr�e utilisateur de la sc�ne.
INLINE MenuInput *DeathScene_GetInput(DeathScene *self)
{
    return self->input;
}
