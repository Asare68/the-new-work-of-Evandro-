
#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.h"
#include "segment.h"
typedef void* CirculoT;
CirculoT Circulo_Criar(int i, PontoT centro, double r, const char* corb, const char* corp);
SegmentoT Circulo_Transformar_Anteparo(CirculoT c, char orientacao);
void Circulo_set_cor(CirculoT c, const char* nova_cor);
void Circulo_Destruir(CirculoT c);
#endif // CIRCLE_H
