#include "battle.h"
#include "game_data.h"
#include "menu.h"
#include "map.h"
#include "map_tile.h"
#include "dialog_renderer.h"
#include "random.h"
#include "enemy_template.h"
#include "enemy.h"
#include "battle_stats.h"

static dqEnemy_t* dqBattle_GenerateEnemyFromTemplate( dqEnemyTemplate_t* template );

void dqBattle_Init()
{
   dqBattle = (dqBattle_t*)dqMalloc( sizeof( dqBattle_t ), sfTrue );

   dqBattle->enemy = 0;

   dqBattle->resultMessage[0] = '\0';
}

void dqBattle_Cleanup()
{
   // I suppose this is possible if there's a way to quit the game during a battle
   if ( dqBattle->enemy != 0 )
   {
      dqFree( dqBattle->enemy->battleStats, sizeof( dqBattleStats_t ), sfTrue );
      dqFree( dqBattle->enemy, sizeof( dqEnemy_t ), sfTrue );
   }

   dqFree( dqBattle, sizeof( dqBattle_t ), sfTrue );
}

void dqBattle_Reset()
{
   dqFree( dqBattle->enemy->battleStats, sizeof( dqBattleStats_t ), sfTrue );
   dqFree( dqBattle->enemy, sizeof( dqEnemy_t ), sfTrue );

   dqBattle->enemy = 0;
}

void dqBattle_Generate()
{
   unsigned int tierIndex, enemyIndex;
   static char logMessage[128];
   dqEnemyTemplate_t* enemyTemplate;
   dqMapTile_t* tile = dqMap_GetCurrentTile();

   sprintf_s( logMessage, 128, "generating encounter: min tier %d, max tier %d", tile->minEnemyTier, tile->maxEnemyTier );
   dqLog_Message( logMessage );

   // TODO:
   //
   // - decide how many enemies we want to generate for this battle
   // - try grouping them based on some flags, like whether they travel alone, and the
   //   min and max group size for this particular enemy
   // - maybe try to do some kind of size system, so we don't accidentally generate
   //   more enemies than will fit on the screen

   tierIndex = dqRandom_UnsignedInt( tile->minEnemyTier, tile->maxEnemyTier );
   
   // TODO: this is probably okay for now, but eventually when we have all the
   // enemy templates we need, this should crash if it's out of range
   if ( tierIndex >= dqGameData->enemyTierCount )
   {
      tierIndex = dqGameData->enemyTierCount - 1;
   }

   enemyIndex = dqRandom_UnsignedInt( 0, dqGameData->enemyTemplateCount - 1 );
   enemyTemplate = &( dqGameData->enemyTemplates[tierIndex][enemyIndex] );
   dqBattle->enemy = dqBattle_GenerateEnemyFromTemplate( enemyTemplate );

   // TODO: display which enemy we're about to fight in the dialog

   dqMenuBattleAction->selectedOption = 0;
   dqBattle_SetState( dqBattleStateIntro );
}

void dqBattle_SetState( dqBattleState state )
{
   dqBattle->state = state;
   dqDialogRenderer_ResetScroll();
}

void dqBattle_Attack()
{
   // TODO: based on whose turn it is, actually attack. we'll need another state in
   // here for "action". we'll also need some kind of min/max attack values for
   // enemies, so we can generate a value.

   if ( dqBattle->state == dqBattleStateSelectAction )
   {
      sprintf_s( dqBattle->resultMessage, 128, "Your killing spree was a success!" );
      dqBattle_SetState( dqBattleStateResult );
   }
}

void dqBattle_Run()
{
   // TODO: later on the player's evasion rate (or whatever we call it) will be called into question
   if ( dqBattle->state == dqBattleStateSelectAction )
   {
      sprintf_s( dqBattle->resultMessage, 128, "Wow, so brave. At least you got away, I guess." );
      dqBattle_SetState( dqBattleStateResult );
   }
}

static dqEnemy_t* dqBattle_GenerateEnemyFromTemplate( dqEnemyTemplate_t* template )
{
   dqEnemy_t* enemy = (dqEnemy_t*)dqMalloc( sizeof( dqEnemy_t ), sfTrue );
   enemy->battleStats = (dqBattleStats_t*)dqMalloc( sizeof( dqBattleStats_t ), sfTrue );

   enemy->battleStats->hitPoints = dqRandom_UnsignedInt( template->minHitPoints, template->maxHitPoints );
   enemy->battleStats->attackPower = template->attackPower;
   enemy->battleStats->defensePower = template->defensePower;

   return enemy;
}
