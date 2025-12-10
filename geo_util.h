#ifndef GEO_UTIL_H
#define GEO_UTIL_H
#include "point.h"
#include "segment.h"
#include "vertex.h"
typedef enum { NEGATIVE = -1, ZERO = 0, POSITIVE = 1 } SIGN;
SIGN orient2d(PontoT p1, PontoT p2, PontoT p3);
PontoT interseccao_raio_segmento(PontoT raio_ini, PontoT raio_fim, void* s);
PontoT raio_criar_fim(PontoT x, PontoT v);
#endif // GEO_UTIL_H
