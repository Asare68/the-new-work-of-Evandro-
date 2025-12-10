#ifndef LIST_H
#define LIST_H

// Generic opaque list type
typedef void* ListT;

/*
 * Creates an empty list.
 */
ListT List_Criar();

/*
 * Inserts a generic item (void*) at the end of the list.
 */
void List_Inserir(ListT lst, void* item);

/*
 * Searches the list for an item whose ID matches.
 * "id_ou_criterio" must match an integer field inside the stored object.
 */
void* List_Buscar(ListT lst, int id_ou_criterio);

/*
 * Extracts ALL vertices from ALL segments in the list.
 * Produces a new list of VerticeT objects.
 * Each segment generates 2 vertices: (INICIO, FIM).
 */
ListT List_ExtrairVertices(ListT segmentos_S);

/*
 * Frees the list structure.
 * Does NOT free items inside the list (user must handle those).
 */
void List_Destruir(ListT lst);

#endif
