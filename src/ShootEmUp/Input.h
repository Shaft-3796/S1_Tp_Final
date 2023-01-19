#pragma once

#include "Settings.h"

/// @brief Structure repr�sentant un gestionnaire des entr�es utilisateur.
typedef struct Input_s
{
    /// @brief Bool�en indiquant si le bouton "quitter" vient d'�tre press�.
    bool quitPressed;

    /// @brief Bool�en indiquant si la touche de tir vient d'�tre press�e.
    bool shootPressed;

    bool waitForMouseUp;

    /// @brief Nombre indiquant le d�placement horizontal du joueur.
    /// Les valeurs pour un clavier ou un joystick sont dans l'intervalle
    /// [-1.0f, 1.0f].
    /// La valeur 0.0f d�signe la position par d�faut.
    /// Une valeur n�gative d�signe un d�placement vers la gauche.
    /// Une valeur positive d�signe un d�placement vers la droite.
    float hAxis;

    /// @brief Nombre indiquant le d�placement vertical du joueur.
    /// Les valeurs pour un clavier ou un joystick sont dans l'intervalle
    /// [-1.0f, 1.0f].
    /// La valeur 0.0f d�signe la position par d�faut.
    /// Une valeur n�gative d�signe un d�placement vers le bas.
    /// Une valeur positive d�signe un d�placement vers le haut.
    float vAxis;

    /// @brief Wave shortcut
    bool switchWave;

    /* --- Easter egg --- */
    bool letters[5];
    bool easter_egg;
    bool resize_bullets;
} Input;

/// @brief Cr�e un nouveau gestionnaire des entr�es utilisateur.
/// @return Le gestionnaire cr��.
Input *Input_New();

/// @brief D�truit un gestionnaire des entr�es utilisateur.
/// @param self le gestionnaire.
void Input_Delete(Input *self);

/// @brief Met � jour le gestionnaire des entr�es utilisateur.
/// Cette fonction effectue la boucle des �v�nement SDL.
/// @param self le gestionnaire.
void Input_Update(Input *self);
