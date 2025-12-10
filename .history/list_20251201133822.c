#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "segment.h"
#include "vertex.h"
#include "point.h"

/* ============================================================
   Data Structures
   ============================================================ */

typedef struct node {
    void* item;
    struct node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} List_s;

/* ============================================================
   Create list
   ============================================================ */
ListT List_Criar() {
    List_s* lst = (List_s*) malloc(sizeof(List_s));
    if (!lst) return NULL;

    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;

    return (ListT) lst;
}

/* ============================================================
   Insert item
   ============================================================ */
void List_Inserir(ListT lst, void* item) {
    if (!lst) return;

    List_s* L = (List_s*) lst;

    Node* n = (Node*) malloc(sizeof(Node));
    n->item = item;
    n->next = NULL;

    if (L->head == NULL) {
        L->head = n;
        L->tail = n;
    } else {
        L->tail->next = n;
        L->tail = n;
    }

    L->size++;
}

/* ============================================================
   Search item by ID
   ============================================================ */
void* List_Buscar(ListT lst, int id_criterio) {
    if (!lst) return NULL;

    List_s* L = (List_s*) lst;
    Node* n = L->head;

    while (n != NULL) {
        // Try to interpret as Segment
        SegmentoT s = (SegmentoT) n->item;
        int sid = Segmento_get_id(s);

        if (sid == id_criterio)
            return n->item;

        n = n->next;
    }
    return NULL;
}

/* ============================================================
   Extract Vertices from Segments List
   Each segment produces 2 vertices.
   ============================================================ */
ListT List_ExtrairVertices(ListT segmentos_S) {
    if (!segmentos_S) return NULL;

    List_s* L = (List_s*) segmentos_S;
    Node* n = L->head;

    ListT vertices = List_Criar();

    while (n != NULL) {
        SegmentoT seg = (SegmentoT) n->item;

        // Extract start and end points
        PontoT p_ini = Segmento_get_ini(seg);
        PontoT p_fim = Segmento_get_fim(seg);

        // Create vertices
        VerticeT vIni = Vertice_Criar(INICIO, seg, p_ini, ORIG);
        VerticeT vFim = Vertice_Criar(FIM, seg, p_fim, ORIG);

        // Insert into list
        List_Inserir(vertices, vIni);
        List_Inserir(vertices, vFim);

        n = n->next;
    }

    return vertices;
}

/* ============================================================
   Destroy list (but NOT items!)
   ============================================================ */
void List_Destruir(ListT lst) {
    if (!lst) return;

    List_s* L = (List_s*) lst;
    Node* n = L->head;

    while (n != NULL) {
        Node* temp = n;
        n = n->next;
        free(temp);
    }

    free(L);
}
