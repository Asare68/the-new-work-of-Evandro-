#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.h"
#include "segment.h"
typedef void* CirculoT;
CirculoT Circulo_Criar(int i, PontoT centro, double r, const char* corb, const char* corp);
SegmentoT Circulo_Transformar_Anteparo(CirculoT c, char orientacao);
void Circulo_set_cor(CirculoT c, const char* nova_cor);
void Circulo_Destruir(CirculoT c);

int Circulo_GetId(CirculoT c);
PontoT Circulo_GetCentro(CirculoT c);
double Circulo_GetRaio(CirculoT c);
const char* Circulo_GetCorB(CirculoT c);
const char* Circulo_GetCorP(CirculoT c);
#endif // CIRCLE_H