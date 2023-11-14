#include "player.h"
#include "entity_overworld_state.h"
#include "battle_stats.h"
#include "game_config.h"
#include "game_data.h"
#include "map.h"
#include "map_tile.h"

dqPlayer_t* dqPlayer_Create()
{
   dqMap_t* map;
   dqMapTile_t* tile;

   dqPlayer_t* player = (dqPlayer_t*)dqMalloc( sizeof( dqPlayer_t ) );
   player->overworldState = (dqEntityOverworldState_t*)dqMalloc( sizeof( dqEntityOverworldState_t ) );
   player->battleStats = (dqBattleStats_t*)dqMalloc( sizeof( dqBattleStats_t ) );
   dqGameData->player = player;

   // TODO: most of this will eventually be loaded from a file
   player->overworldState->hitBoxSize.x = 14;
   player->overworldState->hitBoxSize.y = 14;
   player->overworldState->hitBoxPosition.x = dqGameData->playerStartTileCoordinates.x * dqGameConfig->mapTileSize;
   player->overworldState->hitBoxPosition.y = dqGameData->playerStartTileCoordinates.y * dqGameConfig->mapTileSize;
   player->overworldState->centerPosition.x = player->overworldState->hitBoxPosition.x + ( player->overworldState->hitBoxSize.x / 2 );
   player->overworldState->centerPosition.y = player->overworldState->hitBoxPosition.y + ( player->overworldState->hitBoxSize.y / 2 );
   player->overworldState->velocityX = 0;
   player->overworldState->velocityY = 0;
   player->overworldState->direction = dqDirectionDown;

   player->battleStats->hitPoints = 50;
   player->battleStats->attackPower = 10;
   player->battleStats->defensePower = 10;

   map = dqGameData_GetCurrentMap();
   tile = dqMap_GetTileFromPosition( map, &( player->overworldState->centerPosition ) );
   map->playerTileCache = tile;

   return player;
}

void dqPlayer_Cleanup( dqPlayer_t* player )
{
   dqFree( player->battleStats );
   dqFree( player->overworldState );
   dqFree( player );
}
