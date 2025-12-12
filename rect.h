#ifndef RECT_H
#define RECT_H

#include "point.h"
#include "list.h"
#include "segment.h" 

typedef void* RetanguloT;

/* Construtor */
RetanguloT Retangulo_Criar(int id, PontoT ancora, double w, double h, const char* corb, const char* corp);

/* Destrutor */
void Retangulo_Destruir(RetanguloT r);


int Retangulo_GetId(RetanguloT r);
PontoT Retangulo_GetAncora(RetanguloT r);
double Retangulo_GetW(RetanguloT r);
double Retangulo_GetH(RetanguloT r);
const char* Retangulo_GetCorB(RetanguloT r);
const char* Retangulo_GetCorP(RetanguloT r);

ListT Retangulo_Transformar_Anteparos(RetanguloT r);

#endif // RECT_H