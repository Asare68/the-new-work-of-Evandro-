#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"
#include "segment.h"

// Opaque type for Circle
typedef void* CirculoT;

/*
 * Creates a new Circle object 
 * Parameters:
 *   i      → ID
 *   centro → center point
 *   r      → radius
 *   corb   → border color
 *   corp   → fill color
 * Corresponds to: ci x y r corb corp  [24]
 */
CirculoT Circulo_Criar(int i, PontoT centro, double r, 
                       const char* corb, const char* corp);

/* === GETTERS === */
int      Circulo_get_id(CirculoT c);
PontoT   Circulo_get_centro(CirculoT c);
double   Circulo_get_raio(CirculoT c);
const char* Circulo_get_corb(CirculoT c);
const char* Circulo_get_corp(CirculoT c);

/*
 * Transformation to Barrier (command 'a') [25, 26]
 * Converts the circle into a segment located on its diameter.
 *
 * orientacao = 'h' → horizontal segment
 * orientacao = 'v' → vertical segment
 */
SegmentoT Circulo_Transformar_Anteparo(CirculoT c, char orientacao);

/* === SETTERS === */
/*
 * Sets new fill color for command 'p' (paint bomb) [28]
 */
void Circulo_set_cor(CirculoT c, const char* nova_cor);

/* === DESTRUCTOR === */
void Circulo_Destruir(CirculoT c);

#endif // CIRCLE_H
