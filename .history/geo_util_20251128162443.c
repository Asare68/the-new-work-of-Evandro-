// geo_util.c
#include <math.h>
#include "geo_util.h"
// Note: The implementation of orientation uses the determinant
calculation
// (cross product) to find the signed area [10, 13, 14].
SIGN orient2d(PontoT p1, PontoT p2, PontoT p3) {
 // Calculates twice the oriented area (Determinant 3x3) [8,
10]
 double x1 = Ponto_get_x(p1); double y1 = Ponto_get_y(p1);
 double x2 = Ponto_get_x(p2); double y2 = Ponto_get_y(p2);
 double x3 = Ponto_get_x(p3); double y3 = Ponto_get_y(p3);
 // Calculation: (x2 - x1)(y3 - y1) - (y2 - y1)(x3 - x1)
 double val = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
 if (val > 0.0) return POSITIVE; // Left turn [6, 8]
 if (val < 0.0) return NEGATIVE; // Right turn [6, 8]
 return ZERO; // Collinear [6, 8]
}
PontoT interseccao_raio_segmento(PontoT raio_ini, PontoT
raio_fim, void* s) {
 // Requires robust implementation based on parametric form of
 line equations [15, 16].
 // STUB: Placeholder implementation.   