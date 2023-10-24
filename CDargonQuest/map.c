#include "map.h"
#include "map_tile.h"

dqMapTile_t* dqMap_GetTile( dqMap_t* map, unsigned int x, unsigned int y )
{
   unsigned int tileIndex = ( y * map->width ) + x;
   return &( map->tiles[tileIndex] );
}
