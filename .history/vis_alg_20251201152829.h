#ifndef VIS_ALG_H
#define VIS_ALG_H

#include "point.h"
#include "list.h"

/*
 * Algorithm 1: CalculeVisibilidade(S: segmentos; x: ponto) [11, 21]
 * S: input segment set (barriers)
 * x_observador: point of observation (bomb location)
 *
 * Returns V: visibility region segments defining the visible area.
 */
ListT CalculeVisibilidade(ListT S, PontoT x_observador);

#endif // VIS_ALG_H
