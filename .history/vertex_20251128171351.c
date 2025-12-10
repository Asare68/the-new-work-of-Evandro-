one
#endif // VERTEX_H
vertex.c (Excerpt of the Comparator logic)
// vertex.c
#include <stdlib.h>
#include <math.h>
#include "vertex.h"
// ...
// Struct definition
typedef struct {
 TipoVerticeT tipo;
 SegmentoT pSeg;
 PontoT ponto;
 CodigoT codigo;
} Vertice_s;
// ... Vertice_Criar and Getters implementation ...
int Vertice_Comparar(const void* a, const void* b, PontoT
x_observador) {
 // Comparison criteria (in order of priority) [5]:
 // 1. Angle (α(vi) < α(vj))
 // 2. Distance (distance(x, vi) > distance(x, vj)) - Farther
segments processed first
 // 3. Type (start vertex has priority over end vertex if all
else is equal)

 // ... Detailed angle and distance comparison ...

 // If angles and distances are equal, check type:
 if (Vertice_get_tipo(vA) == INICIO && Vertice_get_tipo(vB==
FIM) return -1;
 if (Vertice_get_tipo(vA) == FIM && Vertice_get_tipo(vB) ==
INICIO) return 1;
 return 0;
}
// ..