#include "map.h"
#include "map_tile.h"

dqMapTile_t* dqMap_GetTile( dqMap_t* map, unsigned int column, unsigned int row )
{
   unsigned int tileIndex = ( row * map->columns ) + column;
   return &( map->tiles[tileIndex] );
}
