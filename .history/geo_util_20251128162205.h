#ifndef GEO_UTIL_H
#define GEO_UTIL_H
#include "point.h"
// Enum for the orientation predicate [6, 7]
typedef enum { NEGATIVE = -1, ZERO = 0, POSITIVE = 1 } SIGN;
/*
* orient2d: 2D Orientation Predicate (Left Turn/Right Turn)
* Returns POSITIVE (>0) for left turn, NEGATIVE (<0) for right
turn,
* ZERO (0) for collinearity [7-10].
*/
SIGN orient2d(PontoT p1, PontoT p2, PontoT p3);
/*
* Segment Intersection.
* y ← interseccao(r, s) [11, 12]. Returns the intersection point
of the ray defined by
* 'raio_ini' and 'raio_fim' with the segment 's' (barrier).
*/
PontoT interseccao_raio_segmento(PontoT raio_ini, PontoT
raio_fim, void* s);
/*
* Ray (Ray): Creates an auxiliary point far away to define the
ray [11, 12].
* x: anchor point (the observer)
* v: the vertex defining the ray's direction
*/
PontoT raio_criar_fim(PontoT x, PontoT v);
#endif // GEO_UTIL_H