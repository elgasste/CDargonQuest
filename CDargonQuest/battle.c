#include "battle.h"
#include "game_data.h"
#include "render_config.h"
#include "render_data.h"
#include "menu.h"
#include "map.h"
#include "map_tile.h"
#include "dialog_renderer.h"
#include "random.h"
#include "enemy.h"
#include "battle_stats.h"
#include "string_util.h"
#include "battle_renderer.h"

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
   dqFree( dqBattle->enemy->battleStats, sizeof( dqBattleStats_t ), sfTrue );
   dqFree( dqBattle->enemy, sizeof( dqEnemy_t ), sfTrue );

   dqBattle->enemy = 0;
}

void dqBattle_Generate()
{
   unsigned int tier, index;
   static char logMessage[128];
   dqMapTile_t* tile = dqMap_GetCurrentTile();
   sfIntRect enemyTextureRect;

   sprintf_s( logMessage, 128, "generating encounter: min tier %d, max tier %d", tile->minEnemyTier, tile->maxEnemyTier );
   dqLog_Message( logMessage );

   // TODO:
   //
   // - decide how many enemies we want to generate for this battle
   // - try grouping them based on some flags, like whether they travel alone, and the
   //   min and max group size for this particular enemy
   // - use the enemy's sprite size to determine whether we can fit more on the screen

   tier = dqRandom_UnsignedInt( tile->minEnemyTier, tile->maxEnemyTier );
   
   // TODO: this is probably okay for now, but eventually when we have all the
   // enemy templates we need, this should crash if it's out of range
   if ( tier >= dqGameData->enemyTierCount )
   {
      tier = dqGameData->enemyTierCount - 1;
   }

   index = dqRandom_UnsignedInt( 0, dqGameData->enemyTemplateCount - 1 );
   dqBattle->enemy = dqEnemy_Generate( tier, index );

   // TODO: it feels weird to have this in here
   sfSprite_setTexture( dqBattleRenderer->enemySprite, dqRenderData->enemyTextures[dqBattle->enemy->spriteSize], sfFalse );
   enemyTextureRect.left = dqBattle->enemy->spriteIndex * dqRenderConfig->enemySpriteWidths[dqBattle->enemy->spriteSize];
   enemyTextureRect.top = dqRenderConfig->enemySpriteHeight * tier;
   enemyTextureRect.width = dqRenderConfig->enemySpriteWidths[dqBattle->enemy->spriteSize];
   enemyTextureRect.height = dqRenderConfig->enemySpriteHeight;
   sfSprite_setTextureRect( dqBattleRenderer->enemySprite, enemyTextureRect );

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

void dqBattle_Run()
{
   // TODO: later on the player's evasion rate (or whatever we call it) will be called into question
   if ( dqBattle->state == dqBattleStateSelectAction )
   {
      sprintf_s( dqBattle->resultMessage, 128, "Wow, so brave. At least you got away, I guess." );
      dqBattle_SetState( dqBattleStateResult );
   }
}
