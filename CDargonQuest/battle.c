#include "battle.h"
#include "game_data.h"
#include "menu.h"
#include "map.h"
#include "map_tile.h"
#include "dialog_renderer.h"
#include "random.h"
#include "enemy.h"
#include "battle_stats.h"
#include "string_util.h"

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
      dqEnemy_Cleanup( dqBattle->enemy );
   }

   dqFree( dqBattle, sizeof( dqBattle_t ), sfTrue );
}

void dqBattle_Reset()
{
   dqEnemy_Cleanup( dqBattle->enemy );
   dqBattle->enemy = 0;
}

void dqBattle_Generate()
{
   unsigned int tier, index;
   static char logMessage[128];
   dqMapTile_t* tile = dqMap_GetCurrentTile();

   sprintf_s( logMessage, 128, "generating encounter: min tier %d, max tier %d", tile->minEnemyTier, tile->maxEnemyTier );
   dqLog_Message( logMessage );

   // TODO:
   //
   // - decide how many enemies we want to generate for this battle
   // - try grouping them based on some flags, like whether they travel alone, and the
   //   min and max group size for this particular enemy
   // - use the enemy's sprite size to determine whether we can fit more on the screen

   tier = dqRandom_UnsignedInt( tile->minEnemyTier, tile->maxEnemyTier );
   index = dqRandom_UnsignedInt( 0, dqGameData->enemyTierTemplateCounts[tier] - 1);
   dqBattle->enemy = dqEnemy_Generate( tier, index );

   sprintf_s( dqBattle->introMessage, 128, STR_BATTLE_INTRO_FORMATTER,
              dqStringUtil_GetIndefiniteArticleText( dqBattle->enemy->indefiniteArticle, sfTrue ),
              dqBattle->enemy->name );

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

void dqBattle_CastSpell()
{
   // TODO: implement spells and magic points

   if ( dqBattle->state == dqBattleStateSelectAction )
   {
      sprintf_s( dqBattle->resultMessage, 128, "You cast 'ava duh ken doll bra', and the enemy has laughed itself to death." );
      dqBattle_SetState( dqBattleStateResult );
   }
}

void dqBattle_UseItem()
{
   // TODO: implement inventory system

   if ( dqBattle->state == dqBattleStateSelectAction )
   {
      sprintf_s( dqBattle->resultMessage, 128, "You found a coin in your pocket, and bribed your foe to walk away." );
      dqBattle_SetState( dqBattleStateResult );
   }
}

void dqBattle_Guard()
{
   // TODO: this might be a good place to start implementing battle actions and text scrolling

   if ( dqBattle->state == dqBattleStateSelectAction )
   {
      sprintf_s( dqBattle->resultMessage, 128, "You hid behind your shield so well that your foe forgot you were there, and wandered off." );
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
