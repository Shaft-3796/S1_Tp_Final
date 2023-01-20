# ShootEmUp
##### Bienvenue sur le projet ShootEmUp.
###### Hugo @Shaft - Étudiant ESIEA
###### Antoine @Magicaps - Étudiant ESIEA

## Description

#### Synopsis
*Vous arrivez dans une galaxie lointaine, très lointaine, trop lointaine.
Votre objectif ? Terrasser les ennemis qui vous barrent la route au cours des différentes phases !*

#### Gameplay

##### Pilotage, tirs:

*Votre personnage peut se déplacer dans une zone définie*
*Vous devez tirer des lasers pour anéantir les ennemis, mais attentions à la riposte !*

*Pour vous déplacer avec les touches directionnelles, remplacez la ligne 4 du fichier Settings.h par "#define MOUSE_CONTROL false"*

*Pour vous déplacer avec la souris, remplacez la ligne 4 du fichier Settings.h par "#define MOUSE_CONTROL true"*

*Vous pouvez tirer avec la touche espace ou avec le clique gauche*

##### Perks:
*Vous pouvez collecter des perks au cours de la partie dont voici les effets:*

*Astro: un petit astronaute qui vous fera accélérer à la vitesse de la lumière !*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/shaft/src/Assets/Perks/Perk_Astro.png)

*Shield: un bouclier énergétique pour vous protéger de tous les tirs, mais gare aux explosions !*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/shaft/src/Assets/Perks/Perk_Shield.png)

*LifeUp: un peu d'amour et vous êtes reparti au combat ! Vous refait gagner de la vie.*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/shaft/src/Assets/Perks/Perk_LifeUp.png)

*PowerShoot: surcharge votre canon pour le prochain tir !*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/shaft/src/Assets/Perks/Perk_PowerShoot.png)

##### Astéroïdes:
*Des astéroïdes traversent le champ de bataille ! Attention à votre beau fuselage !*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/shaft/src/Assets/Gameplay/Asteroid.png)

#### Description des ennemies /!\ SPOIL ALERT /!\
*Enemi de base: se déplace de haut en bas et tire de simple lasers*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/shaft/src/Assets/Enemy/BaseEnemy.png)

*Enemi sinus (ne me demandez pas pourquoi ce nom): tir des rockets avec un déplacement spécifique*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/develop/src/Assets/Enemy/EnemySin.png)

*Enemi rafale: envoie des lasers en petites rafales*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/develop/src/Assets/Enemy/EnemyRafale.png)

*Enemi triangle: envoie de puissants arcs électriques*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/develop/src/Assets/Enemy/EnemyTriangle.png)

*Enemi teleport: envoie de simples lasers, se téléporte instantanément sur vous puis effectue un tir puissant et rapide*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/develop/src/Assets/Enemy/EnemyTeleport.png)

*Enemi auto: lance une redoutable rocket auto guidée*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/develop/src/Assets/Enemy/EnemyAuto.png)

*Enemi bomb: envoie une bombe qui va tranquillement s'approcher de vous pour exploser après un certain temps*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/develop/src/Assets/Enemy/EnemyBomb.png)

*Enemi revert: un vrai pot de colle ! Vous retourne vos lasers.*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/develop/src/Assets/Enemy/EnemyRevert.png)

*2 boss: font spawn des ennemies et utilisent diférentes munitions*

![](https://github.com/Shaft-3796/S1_Tp_Final/blob/develop/src/Assets/Enemy/Boss1.png)
![](https://github.com/Shaft-3796/S1_Tp_Final/blob/develop/src/Assets/Enemy/Boss2.png)


## Technique

#### Scenes

*Le jeu se décompose en 3 scenes. La scene d'entrée, un appuie sur espace lance la scene de jeu, une mort lance la scene de mort, un appuie sur espace relance le jeu.*


