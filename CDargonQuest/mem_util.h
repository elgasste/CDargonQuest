#if !defined( DQ_MEM_UTIL_H )
#define DQ_MEM_UTIL_H

void* dqMalloc( size_t size, sfBool track );
void* dqCalloc( size_t count, size_t size, sfBool track );
void dqFree( void* mem, size_t size, sfBool track );

#endif
