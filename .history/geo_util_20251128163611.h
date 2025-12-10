#ifndef GEO_UTIL_H
#define GEO_UTIL_H

#include "point.h"

// Enum for the orientation predicate
typedef enum { NEGATIVE = -1, ZERO = 0, POSITIVE = 1 } SIGN;

/*
 * orient2d: Orientation Predicate (p1 → p2 → p3)
 */
SIGN orient2d(PontoT p1, PontoT p2, PontoT p3);

/*
 * Returns the intersection point between a ray (raio_ini → raio_fim)
 * and a segment s = {a, b}.
 * Returns NULL if no intersection.
 */
PontoT interseccao_raio_segmento(PontoT raio_ini, PontoT raio_fim, void* s);

/*
 * Creates a far-away point in the direction x → v.
 * Used to form a ray.
 */
PontoT raio_criar_fim(PontoT x, PontoT v);

#endif // GEO_UTIL_H
