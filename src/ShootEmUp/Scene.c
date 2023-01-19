#include "Scene.h"
#include "Perks.h"
#include "Enemy.h"
#include "Enemy_debug.h"
#include "Enemy_Sin.h"
#include "Enemy_Boss_1.h"
#include "Bullet_Asteroid.h"
#include "Enemy_Teleport.h"
#include "Enemy_Rafale.h"
#include "Enemy_triangle.h"
#include "Enemy_Revert.h"
#include "Bullet_Auto.h"
#include "Enemy_Boss_2.h"
#include "Enemy_Auto.h"
#include "Enemy_Bomb.h"
#include "Bullet.h"
#include "Music.h"

// Protos
void randomSpawnPerk(Scene *self, PerkType type);

Scene *Scene_New(SDL_Renderer *renderer)
{
    Scene *self = (Scene *)calloc(1, sizeof(Scene));
    AssertNew(self);

    self->renderer = renderer;

    self->assets = Assets_New(renderer);
    self->camera = Camera_New(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    self->input = Input_New();
    self->player = Player_New(self);
    self->waveIdx = 0;
    self->maxLife = 20;

    /* Perks */
    self->is_astro = true;
    self->astro_respawn_accumulator = 0.0f;
    self->astro_respawn_time = 0.0f;

    self->is_shield = true;
    self->shield_respawn_accumulator = 0.0f;
    self->shield_respawn_time = 0.0f;

    self->is_lifeup = true;
    self->lifeup_respawn_accumulator = 0.0f;
    self->lifeup_respawn_time = 0.0f;

    self->is_powershoot = true;
    self->powershoot_respawn_accumulator = 0.0f;
    self->powershoot_respawn_time = 0.0f;

    // Background
    SDL_Rect layer1Pos = { 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT};
    self->layer1Pos = layer1Pos;
    SDL_Rect layer0Pos = { 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT};
    self->layer0Pos = layer0Pos;
    self->backgroundSpeedMultiplier = 1.f;

    // Anim de fin
    self->finalAnimationAccumulator = 0.f;
    self->opacity = 0;
    self->soundAnim = 0;

    // Anim de damage
    self->damageAnimationAccumulator = -1.f; // -1 = pas d'anim

    return self;
}

void Scene_Delete(Scene *self)
{
    if (!self) return;

    Assets_Delete(self->assets);
    Camera_Delete(self->camera);
    Input_Delete(self->input);
    Player_Delete(self->player);

    for (int i = 0; i < self->enemyCount; i++)
    {
        self->enemies[i]->Delete(self->enemies[i]);
        self->enemies[i] = NULL;
    }
    for (int i = 0; i < self->bulletCount; i++)
    {
        self->bullets[i]->Delete(self->bullets[i]);
        self->bullets[i] = NULL;
    }

    free(self);
}

void Scene_UpdateLevel(Scene *self)
{
    if (self->enemyCount > 0)
        return;

    if (self->waveIdx == 0)
    {
        /* Add two Base enemy */
        Enemy *enemy = EnemyBase_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_1), MAX_LIFE_ENEMY_1, SHOOT_PERIOD_ENEMY_1);
        Scene_AppendEnemy(self, enemy);

        /* Add one Perks */
        randomSpawnPerk(self, PERK_TYPE_ASTRO);
        randomSpawnPerk(self, PERK_TYPE_SHIELD);
        randomSpawnPerk(self, PERK_TYPE_LIFEUP);
        randomSpawnPerk(self, PERK_TYPE_POWERSHOOT);

        self->waveIdx++;
    }
    else if(self->waveIdx == 1)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyBase_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_1, SHOOT_PERIOD_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyRafal_New(self, Vec2_Set(POSITION_X_ENEMY_2, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_1, SHOOT_PERIOD_ENEMY_2);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
    else if(self->waveIdx == 2)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyBase_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_1, SHOOT_PERIOD_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyBase_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_1, SHOOT_PERIOD_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemySin_New(self, Vec2_Set(POSITION_X_ENEMY_2, POSITION_Y_ENEMY_1), MAX_LIFE_ENEMY_2, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);

        /* Add an asteroid */
        self->asteroid_to_spawn = 3;

        self->waveIdx++;
    }
    else if(self->waveIdx == 3)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyTriangle_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_2, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyTriangle_New(self, Vec2_Set(POSITION_X_ENEMY_2, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_2, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
    else if(self->waveIdx == 4)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyRafal_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_1, SHOOT_PERIOD_ENEMY_2);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyRafal_New(self, Vec2_Set(POSITION_X_ENEMY_2, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_1, SHOOT_PERIOD_ENEMY_2);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemySin_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_1), MAX_LIFE_ENEMY_2, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
    else if(self->waveIdx == 5)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyBoss1_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_1), MAX_LIFE_BOSS, SHOOT_PERIOD_ENEMY_4);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
    else if(self->waveIdx == 6)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyTeleport_New(self, Vec2_Set(POSITION_X_ENEMY_2, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_3, SHOOT_PERIOD_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyRafal_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_1, SHOOT_PERIOD_ENEMY_2);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
    else if(self->waveIdx == 7)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyAuto_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_3, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyAuto_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_3, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
    else if(self->waveIdx == 8)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyTriangle_New(self, Vec2_Set(POSITION_X_ENEMY_2, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_2, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyRevert_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyRevert_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyTriangle_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_2, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
    else if(self->waveIdx == 9)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyRafal_New(self, Vec2_Set(POSITION_X_ENEMY_2, POSITION_Y_ENEMY_1), MAX_LIFE_ENEMY_2, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyRevert_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyRevert_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyBomb_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_1), MAX_LIFE_ENEMY_3, SHOOT_PERIOD_ENEMY_4);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
    else if(self->waveIdx == 10)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyAuto_New(self, Vec2_Set(POSITION_X_ENEMY_2, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_2, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyRevert_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyRevert_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_2), MAX_LIFE_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyRevert_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_1), MAX_LIFE_ENEMY_1);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyAuto_New(self, Vec2_Set(POSITION_X_ENEMY_2, POSITION_Y_ENEMY_3), MAX_LIFE_ENEMY_3, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyBomb_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_1), MAX_LIFE_ENEMY_3, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
    else if(self->waveIdx == 11)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyBoss2_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_1), MAX_LIFE_BOSS, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
    else if(self->waveIdx == 12)
    {
        /* Add one Base enemy and one rafal enemy*/
        Enemy* enemy = EnemyBoss2_New(self, Vec2_Set(POSITION_X_ENEMY_1, POSITION_Y_ENEMY_1), MAX_LIFE_BOSS, SHOOT_PERIOD_ENEMY_3);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyBoss1_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_2), MAX_LIFE_BOSS, SHOOT_PERIOD_ENEMY_4);
        Scene_AppendEnemy(self, enemy);
        enemy = EnemyBoss1_New(self, Vec2_Set(POSITION_X_ENEMY_3, POSITION_Y_ENEMY_3), MAX_LIFE_BOSS, SHOOT_PERIOD_ENEMY_4);
        Scene_AppendEnemy(self, enemy);

        self->waveIdx++;
    }
}

/* --- Perks --- */

void randomSpawnPerk(Scene *self, PerkType type){
    switch (type) {
        case PERK_TYPE_ASTRO:
            self->is_astro = true;
            self->astro_respawn_accumulator = 0.0f;
            self->astro_respawn_time = 0.0f;
            break;
        case PERK_TYPE_SHIELD:
            self->is_shield = true;
            self->shield_respawn_accumulator = 0.0f;
            self->shield_respawn_time = 0.0f;
            break;
        case PERK_TYPE_LIFEUP:
            self->is_lifeup = true;
            self->lifeup_respawn_accumulator = 0.0f;
            self->lifeup_respawn_time = 0.0f;
            break;
        case PERK_TYPE_POWERSHOOT:
            self->is_powershoot = true;
            self->powershoot_respawn_accumulator = 0.0f;
            self->powershoot_respawn_time = 0.0f;
            break;
        default:
            break;

    }
    Vec2 pos = Vec2_Set(((float)rand()/(float)RAND_MAX)*7+0.5, ((float)rand()/(float)RAND_MAX)*8+0.5);
    Perk *perk = Perk_New(self, type, pos);
    Scene_AppendPerk(self, perk);
}

void randomSpawnAsteroid(Scene *self){
    Vec2 pos = Vec2_Set(18.f, (rand()%(71)+5)/10);
    Bullet* asteroid = BulletAsteroid_New(self, pos, Vec2_Set(-1*ASTEROID_SPEED_MULTIPLIER, 0.f), 90.f);
    Scene_AppendBullet(self, asteroid);
}

void Scene_UpdatePerks(Scene *self)
{
    if(!self->is_astro)
    {
        self->astro_respawn_accumulator += Timer_GetDelta(g_time);
        if(self->astro_respawn_accumulator >= self->astro_respawn_time)
        {
            randomSpawnPerk(self, PERK_TYPE_ASTRO);
        }
    }

    if(!self->is_shield)
    {
        self->shield_respawn_accumulator += Timer_GetDelta(g_time);
        if(self->shield_respawn_accumulator >= self->shield_respawn_time)
        {

            randomSpawnPerk(self, PERK_TYPE_SHIELD);
        }
    }

    if(!self->is_lifeup)
    {
        self->lifeup_respawn_accumulator += Timer_GetDelta(g_time);
        if(self->lifeup_respawn_accumulator >= self->lifeup_respawn_time)
        {

            randomSpawnPerk(self, PERK_TYPE_LIFEUP);
        }
    }

    if(!self->is_powershoot)
    {
        self->powershoot_respawn_accumulator += Timer_GetDelta(g_time);
        if(self->powershoot_respawn_accumulator >= self->powershoot_respawn_time)
        {

            randomSpawnPerk(self, PERK_TYPE_POWERSHOOT);
        }
    }


    // We also update asteroids
    if(self->asteroid_to_spawn > 0)
    {
        self->asteroid_respawn_accumulator += Timer_GetDelta(g_time);
        if(self->asteroid_respawn_accumulator >= 1)
        {
            self->asteroid_to_spawn -= 1;
            self->asteroid_respawn_accumulator = 0.0f;
            randomSpawnAsteroid(self);
        }
    }

}

int Scene_Update(Scene *self)
{
    Player *player = self->player;

    // Met � jour les entr�es utilisateur
    Input_Update(self->input);

    // Mouse control
    if(MOUSE_CONTROL){
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        Vec2 mouse_pos = Vec2_Set(mouse_x, mouse_y);
        Vec2 player_pos = Vec2_Set(player->position.x, player->position.y);
        player_pos.x *= Camera_GetWorldToViewScale(self->camera);
        player_pos.y *= Camera_GetWorldToViewScale(self->camera);
        player_pos.y = LOGICAL_HEIGHT - player_pos.y;
        fflush(stdout);

        if(mouse_pos.x > player_pos.x+5){
            self->input->hAxis = 1.f;
        }
        else if(mouse_pos.x < player_pos.x-5){
            self->input->hAxis = -1.f;
        }
        else{
            self->input->hAxis = 0.f;
        }

        if(mouse_pos.y < player_pos.y-5){
            self->input->vAxis = 1.f;
        }
        else if(mouse_pos.y > player_pos.y+5){
            self->input->vAxis = -1.f;
        }
        else{
            self->input->vAxis = 0.f;
        }


    }

        // Avance d'une vague si le shortcut a été activé
    if(self->input->switchWave)
    {
        // Remove all enemies
        while(self->enemyCount > 0)
        {
            Scene_RemoveEnemy(self, 0);
        }
        // Remove all bullets
        while(self->bulletCount > 0)
        {
            Scene_RemoveBullet(self, 0);
        }
    }


    // Met � jour la positions et les dimensions des calques du background
    int offset = Timer_GetDelta(g_time)*(float)BACKGROUND_1_SPEED_MULTIPLIER*self->backgroundSpeedMultiplier;
    self->layer1Pos.x += offset;
    if(self->layer1Pos.x+self->layer1Pos.w >= BACKGROUND_WIDTH)
    {
        self->layer1Pos.x -= BACKGROUND_PERIOD*2;
    }
    offset = Timer_GetDelta(g_time)*(float)BACKGROUND_0_SPEED_MULTIPLIER*self->backgroundSpeedMultiplier;
    self->layer0Pos.x += offset;
    if(self->layer0Pos.x+self->layer0Pos.w >= BACKGROUND_WIDTH)
    {
        self->layer0Pos.x -= BACKGROUND_PERIOD*2;
    }

    // Met à jour l'anim de fin
    if(self->player->state == PLAYER_DEAD){
        self->finalAnimationAccumulator += Timer_GetDelta(g_time);
        if(self->finalAnimationAccumulator >= 0.02f){
            self->finalAnimationAccumulator = 0.f;
            self->opacity += 1;
        }
        if(self->soundAnim == 0){
            playSound("Death_Player");
            self->soundAnim += 1;
        }
    }

    // -------------------------------------------------------------------------
    // Met � jour les tirs

    int i = 0;
    while (i < self->bulletCount)
    {
        Bullet *bullet = self->bullets[i];
        bool removed = false;

        bullet->Update(bullet);

        bool outOfBounds =
            (bullet->position.x < -5.0f) ||
            (bullet->position.x > 20.0f) ||
            (bullet->position.y < -5.0f) ||
            (bullet->position.y > 20.0f);

        if (outOfBounds || (bullet->type == BULLET_BOMB_ENEMY && bullet->ready_to_delete))
        {
            // Supprime le tir
            if(bullet->type == BULLET_BOMB_ENEMY && bullet->ready_to_delete==1){
                bullet->ready_to_delete=2;
            }
            else if(bullet->type == BULLET_BOMB_ENEMY && bullet->ready_to_delete==2){
                Scene_RemoveBullet(self, i);
                removed = true;
                continue;
            }
            else{Scene_RemoveBullet(self, i);
            removed = true;
            continue;}
        }

        if (bullet->fromPlayer)
        {
            // Teste les collisions avec les ennemis
            for (int j = 0; j < self->enemyCount; j++)
            {
                Enemy *enemy = self->enemies[j];
                float dist = Vec2_Distance(bullet->position, enemy->position);
                if (dist < bullet->radius + enemy->radius)
                {
                    // Inflige des dommages � l'ennemi
                    enemy->Damage(enemy, 1);

                    // On verifie si l'ennemi est un Enemy revert
                    if(enemy->type == ENEMY_REVERT){
                        enemy->Revert(enemy, bullet);
                        break;
                    }

                    // Supprime le tir
                    Scene_RemoveBullet(self, i);
                    removed = true;
                    break;
                }
            }
        }
        else
        {
            // Teste la collision avec le bouclié
            float dist = Vec2_Distance(bullet->position, self->player->position);
            if (dist < bullet->radius + player->shield_radius && player->perk_shield)
            {
                // Supprime le tir
                Scene_RemoveBullet(self, i);
                removed = true;
            }

            // Teste la collision avec le joueur

            else if (dist < bullet->radius + player->radius)
            {
                // Inflige des dommages au joueur
                Player_Damage(player, bullet->damage);

                // Supprime le tir
                Scene_RemoveBullet(self, i);
                removed = true;

                playSound("Player_Hit");
            }
        }

        // Passe au prochain tir
        if (removed == false)
        {
            i++;
        }
    }

    // -------------------------------------------------------------------------
    // Met � jour les ennemis

    i = 0;
    while (i < self->enemyCount)
    {
        Enemy *enemy = self->enemies[i];
        bool removed = false;

        enemy->Update(enemy);

        if (enemy->state == ENEMY_DEAD)
        {
            // Supprime l'ennemi
            Scene_RemoveEnemy(self, i);
            removed = true;
            playSound("Death_Enemy");
        }

        // Passe au prochain ennemi
        if (removed == false)
        {
            i++;
        }
    }

    // -------------------------------------------------------------------------
    // Met � jour le joueur

    Player_Update(self->player);

    // -------------------------------------------------------------------------
    // Met � jour les Perk

    i = 0;
    while (i < self->perkCount)
    {
        Perk *perk = self->perk[i];
        bool removed = false;

        Perk_Update(perk);

        // Check for Perk collision with player
        float dist = Vec2_Distance(perk->position, self->player->position);
        if (dist < perk->radius + player->radius)
        {
            // Applique l'effet de la Perk
            Perk_Apply_Effect(perk, self->player);
            Scene_RemovePerk(self, i);
            removed = true;
            playSound("Bonus");
        }

        // Passe au prochain perk
        if (removed == false)
        {
            i++;
        }
    }

    Scene_UpdatePerks(self);

    // -------------------------------------------------------------------------
    // Met � jour le niveau

    Scene_UpdateLevel(self);

    // -------------------------------------------------------------------------

    /* --- Return --- */
    if(self->input->quitPressed){
        return 1;
    }
    else if(self->opacity >= 255){
        return 2;
    }
    else{
        return 0;
    }
}

void Scene_Render(Scene *self)
{
    // Affichage du fond
    SDL_Renderer *renderer = Scene_GetRenderer(self);
    Assets *assets = Scene_GetAssets(self);
    SDL_RenderCopy(renderer, assets->layers[0], &(self->layer0Pos), NULL);
    SDL_RenderCopy(renderer, assets->layers[1], &(self->layer1Pos), NULL);
    SDL_RenderCopy(renderer, assets->layers[2], &(self->layer1Pos), NULL);
    // SDL_RenderCopy(renderer, assets->layers[0], &selection_l2, NULL);


    // Affichage des bullets
    int bulletCount = self->bulletCount;
    for (int i = 0; i < bulletCount; i++)
    {
        self->bullets[i]->Render(self->bullets[i]);
    }

    // Affichage des ennemis
    int enemyCount = self->enemyCount;
    for (int i = 0; i < enemyCount; i++)
    {
        self->enemies[i]->Render(self->enemies[i]);
    }

    // Affichage du joueur
    Player_Render(self->player);

    // Affichage des Perk
    int perkCount = self->perkCount;
    for (int i = 0; i < perkCount; i++)
    {
        Perk_Render(self->perk[i]);
    }

        // Anim de fin
    if(self->player->state == PLAYER_DEAD){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, self->opacity);
        SDL_RenderFillRect(renderer, NULL);
    }

    // Anim de damage
    if(self->damageAnimationAccumulator != -1.f){
        self->damageAnimationAccumulator += Timer_GetDelta(g_time);
        if(self->damageAnimationAccumulator > 0.1f){
            self->damageAnimationAccumulator = -1.f;
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 35);
            SDL_RenderFillRect(renderer, NULL);
        }
    }
}

void Scene_AppendObject(void *object, void **objectArray, int *count, int capacity)
{
    int index = *count;
    if (index >= capacity)
        return;

    if (objectArray[index] != NULL)
    {
        assert(false);
        abort();
    }

    objectArray[index] = object;
    (*count)++;
}

void Scene_AppendEnemy(Scene *self, Enemy *enemy)
{
    Scene_AppendObject(
        enemy,
        (void **)(self->enemies),
        &(self->enemyCount),
        ENEMY_CAPACITY
    );

}

void Scene_AppendBullet(Scene *self, Bullet *bullet)
{
    Scene_AppendObject(
        bullet,
        (void **)(self->bullets),
        &(self->bulletCount),
        BULLET_CAPACITY
    );
}

void Scene_RemoveObject(int index, void **objectArray, int *count)
{
    int lastIndex = *count - 1;
    assert(0 <= index && index < *count);

    if (objectArray[index] == NULL)
    {
        assert(false);
        abort();
    }

    if (index == lastIndex)
    {
        // Supprime le pointeur
        objectArray[index] = NULL;
    }
    else
    {
        // Remplace le pointeur par le dernier du tableau
        objectArray[index] = objectArray[lastIndex];
        objectArray[lastIndex] = NULL;
    }
    (*count)--;
}

void Scene_RemoveEnemy(Scene *self, int index)
{
    self->enemies[index]->Delete(self->enemies[index]);
    Scene_RemoveObject(index, (void **)(self->enemies), &(self->enemyCount));
}

void Scene_RemoveBullet(Scene *self, int index)
{
    self->bullets[index]->Delete(self->bullets[index]);
    Scene_RemoveObject(index, (void **)(self->bullets), &(self->bulletCount));
}

/* --- Perk --- */
void Scene_AppendPerk(Scene *self, Perk *perk)
{
    Scene_AppendObject(
        perk,
        (void **)(self->perk),
        &(self->perkCount),
        PERKS_CAPACITY
    );
}

void Scene_RemovePerk(Scene *self, int index)
{
    Perk_Delete(self->perk[index]);
    Scene_RemoveObject(index, (void **)(self->perk), &(self->perkCount));
}
