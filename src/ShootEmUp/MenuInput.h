#pragma once

#include "Settings.h"

/// @brief Structure repr�sentant un gestionnaire des entr�es utilisateur.
typedef struct MenuInput_s
{
    /// @brief Bool�en indiquant si le bouton "quitter" vient d'�tre press�.
    bool quitPressed;

    /// @brief Bool�en indiquant si la touche de tir vient d'�tre press�e.
    bool spacePressed;

} MenuInput;

/// @brief Cr�e un nouveau gestionnaire des entr�es utilisateur.
/// @return Le gestionnaire cr��.
MenuInput *MenuInput_New();

/// @brief D�truit un gestionnaire des entr�es utilisateur.
/// @param self le gestionnaire.
void MenuInput_Delete(MenuInput *self);

/// @brief Met � jour le gestionnaire des entr�es utilisateur.
/// Cette fonction effectue la boucle des �v�nement SDL.
/// @param self le gestionnaire.
void MenuInput_Update(MenuInput *self);
