#include <stdlib.h>
#include <math.h>
#include "point.h"
// Struct definition (only in .c, as per the rule) [1, 2]
typedef struct {
 double x;
 double y;
 } Ponto_s;
PontoT Ponto_Criar(double x, double y) {
 Ponto_s* p = (Ponto_s*)malloc(sizeof(Ponto_s));
 if (p == NULL) return NULL;
 p->x = x;
 p->y = y;
 return (PontoT)p;
}
// Implementation of getters (Ponto_get_x, Ponto_get_y),
Ponto_Distancia, Ponto_Igual, and Ponto_Destruir...