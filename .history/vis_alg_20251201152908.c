#include <stdlib.h>
#include <math.h>
#include "vis_alg.h"
#include "vertex.h"
#include "segment.h"
#include "list.h"
#include "seg_tree.h"

/* ----------------------------------------------------------
 * Helper: Compute angle of a point relative to observer
 * ---------------------------------------------------------- */
static double compute_angle(PontoT p, PontoT obs) {
    double dx = Ponto_get_x(p) - Ponto_get_x(obs);
    double dy = Ponto_get_y(p) - Ponto_get_y(obs);
    return atan2(dy, dx);
}

/* ----------------------------------------------------------
 * Main Visibility Algorithm Implementation
 * ---------------------------------------------------------- */
ListT CalculeVisibilidade(ListT S, PontoT x_observador)
{
    if (!S || !x_observador) return NULL;

    /* --------------------------------------
     * Step 1: Extract vertices from segments
     * -------------------------------------- */
    ListT vertices = List_ExtrairVertices(S);
    if (!vertices) return NULL;

    /* --------------------------------------
     * Step 2: Sort vertices by:
     *   1. angle
     *   2. distance (farther first)
     *   3. type (INICIO > FIM)
     * -------------------------------------- */
    List_Ordenar(vertices, x_observador, Vertice_Comparar);

    /* --------------------------------------
     * Step 3: Create active segments structure
     * -------------------------------------- */
    SegsAtvsT ativos = SegsAtvs_Criar(x_observador);

    /* --------------------------------------
     * Step 4: Sweep and compute visibility
     * -------------------------------------- */
    ListT vis = List_Criar();  // result list

    int n = List_Tamanho(vertices);

    for (int i = 0; i < n; i++) {

        VerticeT v = List_Obter(vertices, i);
        SegmentoT seg = Vertice_get_segmento(v);
        TipoVerticeT tipo = Vertice_get_tipo(v);

        if (tipo == INICIO) {
            SegsAtvs_ativaSegmento(ativos, seg);
        } else {
            SegsAtvs_desativaSegmento(ativos, seg);
        }

        /* Find active segment immediately behind this vertex */
        SegmentoT closest = SegsAtvs_segAtivoMaisProx(ativos, v);
        if (closest) {
            // Visible piece added to output (clone segment)
            SegmentoT visSeg = Segmento_Clone(closest);
            List_Inserir(vis, visSeg);
        }
    }

    /* --------------------------------------
     * Cleanup
     * -------------------------------------- */
    SegsAtvs_Destruir(ativos);
    List_Destruir(vertices);

    return vis;
}
