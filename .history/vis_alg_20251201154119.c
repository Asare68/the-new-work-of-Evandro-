/* vis_alg.c
 *
 * Implements Algorithm 1: CalculeVisibilidade(S: segmentos; x: ponto)
 *
 * Depends on:
 *  - geo_util.h (intersections, raio_criar_fim)
 *  - vertex.h
 *  - seg_tree.h
 *  - segment.h
 *  - list.h
 *  - point.h
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vis_alg.h"
#include "geo_util.h"
#include "vertex.h"
#include "seg_tree.h"
#include "segment.h"
#include "list.h"
#include "point.h"

#define EPS 1e-9

/* Helper: create a new segment between two points with a generated id and color.
 * The function returns a SegmentoT that uses the provided PontoT pointers.
 * The id counter is local static; adapt if you want externally controlled ids.
 */
static SegmentoT criar_segmento_com_pontos(PontoT a, PontoT b, const char* cor) {
    static int next_id = 1000000; // large base to avoid colliding with original ids
    int id = next_id++;
    return Segmento_Criar(id, a, b, cor ? cor : "black");
}

/* Helper: distance from observer to a point (squared or real).
 * We use Euclidean distance (not squared) since comparisons are numeric.
 */
static double distancia_obs(PontoT obs, PontoT p) {
    if (!obs || !p) return INFINITY;
    return Ponto_Distancia(obs, p);
}

/*
 * Determines whether vertex 'v' is occluded (covered) by some active segment in `ativos`.
 * Logic:
 *  - Find the currently active segment 's' that lies immediately in front of `v` (SegsAtvs_segAtivoMaisProx).
 *  - If there is no such segment, vertex is not covered.
 *  - Compute the intersection point y of the ray (obs -> v) with segment s.
 *  - If distance(obs, y) < distance(obs, v) - EPS  then v is covered by s.
 *
 * Returns 1 if covered, 0 otherwise.
 */
static int vertice_encoberto(SegsAtvsT ativos, VerticeT v, PontoT obs) {
    if (!ativos || !v || !obs) return 0;

    SegmentoT s = SegsAtvs_segAtivoMaisProx(ativos, v);
    if (s == NULL) return 0;

    // build ray endpoint and compute intersection with s
    PontoT p_v = Vertice_get_ponto(v);
    PontoT raio_end = raio_criar_fim(obs, p_v);
    PontoT y = interseccao_raio_segmento(obs, raio_end, s);

    // cleanup temporary ray_end
    Ponto_Destruir(raio_end);

    if (y == NULL) return 0; // if no intersection, not covered (shouldn't happen if s is "active")

    double d_y = distancia_obs(obs, y);
    double d_v = distancia_obs(obs, p_v);

    // keep the intersection point y memory if caller needs it (caller will destroy or use it)
    // but here we created y as temporary: destroy it and only return flag
    Ponto_Destruir(y);

    return (d_y < d_v - EPS) ? 1 : 0;
}

/*
 * Adds to output list V the two segments:
 *   [biombo -> v_point]   and   [v_point -> y]
 * Where 'biombo' is a PontoT current screen point (may be NULL for first call),
 * 'v_point' is the vertex coordinates, and 'y' is intersection of ray with new screen segment.
 *
 * This function expects:
 *   - points a and b are PontoT objects (ownership: the new Segmento will reference them).
 *   - if biombo is NULL, segment [biombo, v] is skipped.
 *
 * The function returns the new 'biombo' (PontoT y) or the unchanged biombo if no intersection was made.
 */
static PontoT inserir_vis_e_atualizar_biombo(ListT V, PontoT biombo, PontoT v_point, PontoT y_point) {
    if (!V || !v_point) return biombo;

    // If we have a current biombo, insert segment [biombo, v_point]
    if (biombo != NULL) {
        SegmentoT s1 = criar_segmento_com_pontos(biombo, v_point, "black");
        List_Inserir(V, s1);
    }

    // If intersection exists, insert [v_point, y_point] and return y_point as new biombo
    if (y_point != NULL) {
        SegmentoT s2 = criar_segmento_com_pontos(v_point, y_point, "black");
        List_Inserir(V, s2);
        return y_point; // caller must not destroy y_point (it's now owned by the segment)
    }

    // no new intersection — keep biombo unchanged
    return biombo;
}

/*
 * Compute the minimal bounding rectangle (enclosing rectangle, RE) for all segments in S.
 * Creates 4 segments representing the rectangle and inserts them into the list S (so they will
 * be included in vertex extraction and sweep). The function returns nothing; it mutates S.
 *
 * We add small padding to ensure RE strictly encloses all segments.
 */
static void inserir_retangulo_embutido(ListT S) {
    if (!S) return;

    // We need to iterate S to find min/max of endpoints.
    // I assume List_Tamanho and List_Obter exist for iteration; if not, adapt to your list iteration functions.
    int n = List_Tamanho(S);
    if (n == 0) return;

    double minX = INFINITY, minY = INFINITY;
    double maxX = -INFINITY, maxY = -INFINITY;

    for (int i = 0; i < n; ++i) {
        SegmentoT seg = (SegmentoT) List_Obter(S, i);
        if (!seg) continue;
        PontoT a = Segmento_get_ini(seg);
        PontoT b = Segmento_get_fim(seg);
        if (a) {
            double ax = Ponto_get_x(a), ay = Ponto_get_y(a);
            if (ax < minX) minX = ax;
            if (ax > maxX) maxX = ax;
            if (ay < minY) minY = ay;
            if (ay > maxY) maxY = ay;
        }
        if (b) {
            double bx = Ponto_get_x(b), by = Ponto_get_y(b);
            if (bx < minX) minX = bx;
            if (bx > maxX) maxX = bx;
            if (by < minY) minY = by;
            if (by > maxY) maxY = by;
        }
    }

    // Add padding (10% of largest dimension or a minimal delta)
    double dx = maxX - minX;
    double dy = maxY - minY;
    double pad = fmax(1.0, 0.1 * fmax(dx, dy));

    minX -= pad; minY -= pad;
    maxX += pad; maxY += pad;

    // Build the 4 rectangle corner points
    PontoT p_bl = Ponto_Criar(minX, minY); // bottom-left
    PontoT p_br = Ponto_Criar(maxX, minY); // bottom-right
    PontoT p_tr = Ponto_Criar(maxX, maxY); // top-right
    PontoT p_tl = Ponto_Criar(minX, maxY); // top-left

    // Create four segments (use special id base)
    SegmentoT s_bottom = Segmento_Criar(-1, p_bl, p_br, "black");
    SegmentoT s_right  = Segmento_Criar(-2, p_br, p_tr, "black");
    SegmentoT s_top    = Segmento_Criar(-3, p_tl, p_tr, "black");
    SegmentoT s_left   = Segmento_Criar(-4, p_bl, p_tl, "black");

    // Insert RE segments into S (so they become part of sweep)
    List_Inserir(S, s_bottom);
    List_Inserir(S, s_right);
    List_Inserir(S, s_top);
    List_Inserir(S, s_left);
}

/*
 * Main function: CalculeVisibilidade
 * Implements a rotational sweep (Algorithm 1) that returns a list V of segments
 * describing the visible region polygonal chain from x_observador.
 */
ListT CalculeVisibilidade(ListT S, PontoT x_observador) {
    if (!S || !x_observador) return NULL;

    // Output list
    ListT V = List_Criar();

    // 1) Insert enclosing rectangle (RE) segments into S so the sweep is bounded
    inserir_retangulo_embutido(S);

    // 2) Extract all vertices (including RE vertices)
    ListT vertices = List_ExtrairVertices(S);
    if (!vertices) {
        return V;
    }

    // 3) Sort vertices by angular order relative to observer, then by farther-first, then by type
    // This uses your Vertice_Comparar comparator (signature adapted to List_Ordenar)
    List_Ordenar(vertices, x_observador, Vertice_Comparar); // ADAPT: ensure List_Ordenar exists

    // 4) Create active segments structure
    SegsAtvsT ativos = SegsAtvs_Criar(x_observador);

    // 5) Sweep vertices
    PontoT biombo = NULL; // current 'screen' point
    int m = List_Tamanho(vertices); // ADAPT: ensure List_Tamanho exists
    for (int i = 0; i < m; ++i) {
        VerticeT v = (VerticeT) List_Obter(vertices, i); // ADAPT: ensure List_Obter exists
        if (!v) continue;

        PontoT p_v = Vertice_get_ponto(v);
        TipoVerticeT tipo = Vertice_get_tipo(v);
        SegmentoT seg_v = Vertice_get_segmento(v);

        if (tipo == INICIO) {
            // Activate the segment
            SegsAtvs_ativaSegmento(ativos, seg_v);

            // After inserting, check whether the vertex itself is visible (i.e., not occluded right now)
            if (!vertice_encoberto(ativos, v, x_observador)) {
                // Ray from observer to v, find intersection with the currently active closest segment s
                PontoT raio_end = raio_criar_fim(x_observador, p_v);
                SegmentoT s_closest = SegsAtvs_segAtivoMaisProx(ativos, v);
                PontoT y = NULL;
                if (s_closest != NULL) {
                    y = interseccao_raio_segmento(x_observador, raio_end, s_closest);
                }
                Ponto_Destruir(raio_end);

                // Insert into V segments [biombo, v] and [v, y], and update biombo
                biombo = inserir_vis_e_atualizar_biombo(V, biombo, p_v, y);
                // note: y is not destroyed here because it is now owned by the segment created in inserir_vis...
                // if y == NULL nothing was added beyond [biombo, v]
            }

        } else { // tipo == FIM
            // Before deactivating, check if the vertex is currently visible (not already occluded)
            if (!vertice_encoberto(ativos, v, x_observador)) {
                PontoT raio_end = raio_criar_fim(x_observador, p_v);
                SegmentoT s_closest = SegsAtvs_segAtivoMaisProx(ativos, v);
                PontoT y = NULL;
                if (s_closest != NULL) {
                    y = interseccao_raio_segmento(x_observador, raio_end, s_closest);
                }
                Ponto_Destruir(raio_end);

                biombo = inserir_vis_e_atualizar_biombo(V, biombo, p_v, y);
            }

            // Now deactivate the segment this end vertex belongs to
            SegsAtvs_desativaSegmento(ativos, seg_v);
        }
    }

    // 6) Cleanup
    SegsAtvs_Destruir(ativos);
    List_Destruir(vertices);

    return V;
}
