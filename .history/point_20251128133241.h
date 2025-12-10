
#ifndef POINT_H
#define POINT_H
#include <stdbool.h>
// Opaque type for Point/Coordinate (PontoT)
typedef void* PontoT;
/*
* Creates a new Point object.
* x, y: real coordinates [4].
*/
PontoT Ponto_Criar(double x, double y);
/* Getters */
double Ponto_get_x(PontoT p);
double Ponto_get_y(PontoT p);
double Ponto_Distancia(PontoT p1, PontoT p2); // Used in vertex
ordering tie-breaker [5]
bool Ponto_Igual(PontoT p1, PontoT p2);
/* Destructor */
void Ponto_Destruir(PontoT p);
#endif // POINT_