#include "../include/vis_alg.h"
#include "../include/geo_util.h"
#include "vertex.h"
#include "  seg_tree.h"
#include "list.h"
#include "segment.h"
#include <stdlib.h>

/* Helper: create segment between two points (simple id generation) */
static SegmentoT criar_segmento_temp(PontoT a, PontoT b) {
    static int nid = 1000000;
    return Segmento_Criar(nid++, a, b, "black");
}

/* Simple visibility pipeline: extract vertices, sort, sweep using active set.
   This is a workable skeleton; extend for correctness/robustness as needed. */
ListT CalculeVisibilidade(ListT S, PontoT x_observador) {
    if (!S || !x_observador) return NULL;
    ListT V = List_Criar();
    ListT vertices = List_ExtrairVertices(S);
    if (!vertices) return V;

    /* Sort vertices using observer as context */
    List_Ordenar(vertices, x_observador, (int(*)(const void*,const void*,void*))Vertice_Comparar);

    SegsAtvsT ativos = SegsAtvs_Criar(x_observador);

    int m = List_Tamanho(vertices);
    PontoT biombo = NULL;

    for (int i = 0; i < m; ++i) {
        VerticeT v = (VerticeT)List_Obter(vertices, i);
        if (!v) continue;
        TipoVerticeT tipo = Vertice_get_tipo(v);
        PontoT p_v = Vertice_get_ponto(v);
        SegmentoT seg_v = Vertice_get_segmento(v);

        if (tipo == INICIO) {
            SegsAtvs_ativaSegmento(ativos, seg_v);
            SegmentoT s = SegsAtvs_segAtivoMaisProx(ativos, v);
            if (s) {
                PontoT ray_end = raio_criar_fim(x_observador, p_v);
                PontoT y = interseccao_raio_segmento(x_observador, ray_end, s);
                Ponto_Destruir(ray_end);
                if (biombo) List_Inserir(V, criar_segmento_temp(biombo, p_v));
                if (y) { List_Inserir(V, criar_segmento_temp(p_v, y)); biombo = y; }
            }
        } else {
            SegmentoT s = SegsAtvs_segAtivoMaisProx(ativos, v);
            PontoT ray_end = raio_criar_fim(x_observador, p_v);
            PontoT y = interseccao_raio_segmento(x_observador, ray_end, s);
            Ponto_Destruir(ray_end);
            if (biombo) List_Inserir(V, criar_segmento_temp(biombo, p_v));
            if (y) { List_Inserir(V, criar_segmento_temp(p_v, y)); biombo = y; }
            SegsAtvs_desativaSegmento(ativos, seg_v);
        }
    }

    SegsAtvs_Destruir(ativos);
    List_Destruir(vertices);
    return V;
}
