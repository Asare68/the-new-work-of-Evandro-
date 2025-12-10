#include <math.h>
#include <stdlib.h>
#include "geo_util.h"

/* Expected representation of a segment */
typedef struct {
    PontoT a;
    PontoT b;
} Segmento;

/*
 * 2D orientation predicate
 */
SIGN orient2d(PontoT p1, PontoT p2, PontoT p3) {
    double x1 = Ponto_get_x(p1), y1 = Ponto_get_y(p1);
    double x2 = Ponto_get_x(p2), y2 = Ponto_get_y(p2);
    double x3 = Ponto_get_x(p3), y3 = Ponto_get_y(p3);

    double val = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);

    if (val > 0) return POSITIVE;
    if (val < 0) return NEGATIVE;
    return ZERO;
}

/*
 * Ray–segment intersection:
 * Ray = R(t) = raio_ini + t*(raio_dir)
 * Segment = S(u) = s->a + u*(s->b - s->a)
 * Solve for t >= 0 and 0 <= u <= 1
 */
PontoT interseccao_raio_segmento(PontoT raio_ini, PontoT raio_fim, void* s) {
    Segmento* seg = (Segmento*)s;
    if (!seg) return NULL;

    PontoT A = raio_ini;
    PontoT B = raio_fim;

    PontoT C = seg->a;
    PontoT D = seg->b;

    double Ax = Ponto_get_x(A), Ay = Ponto_get_y(A);
    double Bx = Ponto_get_x(B), By = Ponto_get_y(B);
    double Cx = Ponto_get_x(C), Cy = Ponto_get_y(C);
    double Dx = Ponto_get_x(D), Dy = Ponto_get_y(D);

    // Ray direction
    double rx = Bx - Ax;
    double ry = By - Ay;

    // Segment direction
    double sx = Dx - Cx;
    double sy = Dy - Cy;

    // Solve cross products
    double denom = rx * sy - ry * sx;

    if (fabs(denom) < 1e-12) {
        return NULL;  // Parallel: no intersection
    }

    double t = ((Cx - Ax) * sy - (Cy - Ay) * sx) / denom;
    double u = ((Cx - Ax) * ry - (Cy - Ay) * rx) / denom;

    // Check if intersection is valid
    if (t < 0) return NULL;      // behind ray origin
    if (u < 0 || u > 1) return NULL;  // outside segment

    // Intersection point
    double xi = Ax + t * rx;
    double yi = Ay + t * ry;

    return Ponto_Criar(xi, yi);
}

/*
 * Creates a ray endpoint far away from x → v direction:
 *
 *    x → v vector scaled by 10000
 */
PontoT raio_criar_fim(PontoT x, PontoT v) {
    double x0 = Ponto_get_x(x);
    double y0 = Ponto_get_y(x);

    double vx = Ponto_get_x(v);
    double vy = Ponto_get_y(v);

    double dx = vx - x0;
    double dy = vy - y0;

    double scale = 10000.0; // large number to ensure “infinite” ray

    return Ponto_Criar(x0 + dx * scale, y0 + dy * scale);
}
