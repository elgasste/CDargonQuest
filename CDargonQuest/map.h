#if !defined( DQ_MAP_H )
#define DQ_MAP_H

#include "common.h"

typedef struct dqMapTile_t dqMapTile_t;

typedef struct dqMap_t
{
   dqMapTile_t* tiles;
   unsigned int tileCount;
   unsigned int columns;
   unsigned int rows;
   sfVector2f size;

   dqMapTile_t* playerTileCache;
}
dqMap_t;

dqMapTile_t* dqMap_GetTileFromCoordinates( dqMap_t* map, unsigned int column, unsigned int row );
dqMapTile_t* dqMap_GetTileFromPosition( dqMap_t* map, sfVector2f* pos );
dqMapTile_t* dqMap_GetCurrentTile();
void dqMap_CheckSwap();
void dqMap_Swap( unsigned int newMapIndex, unsigned int newTileIndex );
void dqMap_CheckEncounter();

#endif
