#ifndef POINT_H
#define POINT_H
#include <stdbool.h>
typedef void* PontoT;
PontoT Ponto_Criar(double x, double y);
double Ponto_get_x(PontoT p);
double Ponto_get_y(PontoT p);
double Ponto_Distancia(PontoT p1, PontoT p2);
bool Ponto_Igual(PontoT p1, PontoT p2);
void Ponto_Destruir(PontoT p);
#endif // POINT_H
