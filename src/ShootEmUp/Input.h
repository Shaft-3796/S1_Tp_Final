#pragma once

#include "Settings.h"

/// @brief Structure représentant un gestionnaire des entrées utilisateur.
typedef struct Input_s
{
    /// @brief Booléen indiquant si le bouton "quitter" vient d'être pressé.
    bool quitPressed;

    /// @brief Booléen indiquant si la touche de tir vient d'être pressée.
    //bool shootPressed;

    /// @brief Nombre indiquant le déplacement horizontal du joueur.
    /// Les valeurs pour un clavier ou un joystick sont dans l'intervalle
    /// [-1.0f, 1.0f].
    /// La valeur 0.0f désigne la position par défaut.
    /// Une valeur négative désigne un déplacement vers la gauche.
    /// Une valeur positive désigne un déplacement vers la droite.
    float hAxis;

    /// @brief Nombre indiquant le déplacement vertical du joueur.
    /// Les valeurs pour un clavier ou un joystick sont dans l'intervalle
    /// [-1.0f, 1.0f].
    /// La valeur 0.0f désigne la position par défaut.
    /// Une valeur négative désigne un déplacement vers le bas.
    /// Une valeur positive désigne un déplacement vers le haut.
    float vAxis;
} Input;

/// @brief Crée un nouveau gestionnaire des entrées utilisateur.
/// @return Le gestionnaire créé.
Input *Input_New();

/// @brief Détruit un gestionnaire des entrées utilisateur.
/// @param self le gestionnaire.
void Input_Delete(Input *self);

/// @brief Met à jour le gestionnaire des entrées utilisateur.
/// Cette fonction effectue la boucle des événement SDL.
/// @param self le gestionnaire.
void Input_Update(Input *self);
