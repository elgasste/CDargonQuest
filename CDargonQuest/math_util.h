#if !defined( DQ_MATH_H )
#define DQ_MATH_H

inline int dqMathUtil_IndexFromCoordinates( unsigned int column,
                                            unsigned int row,
                                            unsigned int columnCount )
{
   return ( row * columnCount ) + column;
}

inline void dqMathUtil_CoordinatesFromIndex( unsigned int index,
                                             unsigned int columnCount,
                                             unsigned int* column,
                                             unsigned int* row )
{
   *column = index % columnCount;
   *row = index / columnCount;
}

#endif
