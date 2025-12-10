
#ifndef SEG_TREE_H
#define SEG_TREE_H

#include "segment.h"
#include "vertex.h"
#include "point.h"

// Opaque type for the Balanced Tree of Active Segments
typedef void* SegsAtvsT;

/*
 * Creates and initializes the balanced tree.
 * Requires O(log n) operations.
 */
SegsAtvsT SegsAtvs_Criar(PontoT x_observador);

/*
 * Activates (inserts) a segment into the active set.
 */
void SegsAtvs_ativaSegmento(SegsAtvsT tree, SegmentoT s);

/*
 * Deactivates (removes) a segment from the active set.
 */
void SegsAtvs_desativaSegmento(SegsAtvsT tree, SegmentoT s);

/*
 * Returns the segment ACTIVE and closest to vertex v.
 * This is the “screen” or “biombo”.
 */
SegmentoT SegsAtvs_segAtivoMaisProx(SegsAtvsT tree, VerticeT v);

/*
 * Destructor
 */
void SegsAtvs_Destruir(SegsAtvsT tree);

#endif // SEG_TREE_H
