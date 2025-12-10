#include <stdlib.h>
#include <math.h>
#include "seg_tree.h"
#include "geo_util.h"

// =============================
// AVL Node Structure
// =============================
typedef struct AVLNode {
    SegmentoT seg;
    double chave; // distance to observer
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// =============================
// Tree Structure
// =============================
typedef struct {
    AVLNode* root;
    PontoT observador;
} SegTree_s;

// =============================
// Helpers
// =============================
static int height(AVLNode* n) {
    return n ? n->height : 0;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static AVLNode* rotate_right(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

static AVLNode* rotate_left(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

static int get_balance(AVLNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// =============================
// Compute “key” = distance to intersection
// =============================
static double compute_key(PontoT observer, SegmentoT s, VerticeT v) {
    PontoT inter = interseccao_raio_segmento(observer, Vertice_get_ponto(v), s);
    double d = Ponto_Distancia(observer, inter);
    Ponto_Destruir(inter);
    return d;
}

// =============================
// Insert in AVL
// =============================
static AVLNode* avl_insert(AVLNode* node, SegmentoT s, double chave) {
    if (!node) {
        AVLNode* n = malloc(sizeof(AVLNode));
        n->seg = s;
        n->chave = chave;
        n->left = n->right = NULL;
        n->height = 1;
        return n;
    }

    if (chave < node->chave)
        node->left = avl_insert(node->left, s, chave);
    else if (chave > node->chave)
        node->right = avl_insert(node->right, s, chave);
    else
        return node; // duplicate, ignore

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    // Balancing cases
    if (balance > 1 && chave < node->left->chave)
        return rotate_right(node);

    if (balance < -1 && chave > node->right->chave)
        return rotate_left(node);

    if (balance > 1 && chave > node->left->chave) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance < -1 && chave < node->right->chave) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

// =============================
// Find minimum node
// =============================
static AVLNode* min_node(AVLNode* node) {
    while (node->left) node = node->left;
    return node;
}

// =============================
// AVL delete
// =============================
static AVLNode* avl_delete(AVLNode* root, SegmentoT s) {
    if (!root) return NULL;

    int id_s = Segmento_get_id(s);
    int id_root = Segmento_get_id(root->seg);

    if (id_s < id_root)
        root->left = avl_delete(root->left, s);
    else if (id_s > id_root)
        root->right = avl_delete(root->right, s);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            AVLNode* temp = min_node(root->right);
            root->seg = temp->seg;
            root->chave = temp->chave;
            root->right = avl_delete(root->right, temp->seg);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0)
        return rotate_right(root);

    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && get_balance(root->right) <= 0)
        return rotate_left(root);

    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

// =============================
// Public API
// =============================
SegsAtvsT SegsAtvs_Criar(PontoT x_observador) {
    SegTree_s* T = malloc(sizeof(SegTree_s));
    T->root = NULL;
    T->observador = x_observador;
    return (SegsAtvsT) T;
}

void SegsAtvs_ativaSegmento(SegsAtvsT tree, SegmentoT s) {
    SegTree_s* T = (SegTree_s*) tree;

    // Use segment *final vertex* as default reference
    // Delete: use any vertex because we compare by ID when removing
    PontoT p = Segmento_get_ini(s);
    VerticeT temp = Vertice_Criar(INICIO, s, p, ORIG);

    double chave = compute_key(T->observador, s, temp);
    Vertice_Destruir(temp);

    T->root = avl_insert(T->root, s, chave);
}

void SegsAtvs_desativaSegmento(SegsAtvsT tree, SegmentoT s) {
    SegTree_s* T = (SegTree_s*) tree;
    T->root = avl_delete(T->root, s);
}

SegmentoT SegsAtvs_segAtivoMaisProx(SegsAtvsT tree, VerticeT v) {
    SegTree_s* T = (SegTree_s*) tree;

    double best_dist = INFINITY;
    SegmentoT best_seg = NULL;

    AVLNode* stack[1000];
    int top = 0;
    AVLNode* cur = T->root;

    while (cur || top > 0) {
        while (cur) {
            stack[top++] = cur;
            cur = cur->left;
        }
        cur = stack[--top];

        double dist = compute_key(T->observador, cur->seg, v);

        if (dist < best_dist) {
            best_dist = dist;
            best_seg = cur->seg;
        }
        cur = cur->right;
    }

    return best_seg;
}

static void destroy_nodes(AVLNode* n) {
    if (!n) return;
    destroy_nodes(n->left);
    destroy_nodes(n->right);
    free(n);
}

void SegsAtvs_Destruir(SegsAtvsT tree) {
    SegTree_s* T = (SegTree_s*) tree;
    destroy_nodes(T->root);
    free(T);
}
