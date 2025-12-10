#ifndef RECT_H
#define RECT_H

#include "point.h"
#include "list.h"   // Rectangle generates 4 segments

// Opaque type for Rectangle
typedef void* RetanguloT;

/*
 * Creates a Rectangle (r i x y w h corb corp).
 * (x, y) is the lower-left corner [24, 29].
 */
RetanguloT Retangulo_Criar(int i, PontoT ancora, double w, double h,
                           const char* corb, const char* corp);

/*
 * Transformation to Barrier Function (command 'a') [25, 26].
 * Rectangles are replaced by 4 segments corresponding to their sides [26].
 */
ListT Retangulo_Transformar_Anteparos(RetanguloT r);

/* Destructor */
void Retangulo_Destruir(RetanguloT r);

#endif // RECT_H
