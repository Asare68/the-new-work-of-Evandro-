#include "geo_util.h"
#include "../include/point.h"
#include "segment.h"
#include <stdlib.h>
#include <math.h>

SIGN orient2d(PontoT p1, PontoT p2, PontoT p3) {
    double x1 = Ponto_get_x(p1), y1 = Ponto_get_y(p1);
    double x2 = Ponto_get_x(p2), y2 = Ponto_get_y(p2);
    double x3 = Ponto_get_x(p3), y3 = Ponto_get_y(p3);
    double val = (x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1);
    if (val > 0.0) return POSITIVE;
    if (val < 0.0) return NEGATIVE;
    return ZERO;
}

PontoT interseccao_raio_segmento(PontoT raio_ini, PontoT raio_fim, void* s) {
    SegmentoT seg = (SegmentoT)s;
    if (!seg) return NULL;
    PontoT A = raio_ini, B = raio_fim, C = Segmento_get_ini(seg), D = Segmento_get_fim(seg);
    double Ax = Ponto_get_x(A), Ay = Ponto_get_y(A);
    double Bx = Ponto_get_x(B), By = Ponto_get_y(B);
    double Cx = Ponto_get_x(C), Cy = Ponto_get_y(C);
    double Dx = Ponto_get_x(D), Dy = Ponto_get_y(D);
    double rx = Bx - Ax, ry = By - Ay;
    double sx = Dx - Cx, sy = Dy - Cy;
    double denom = rx*sy - ry*sx;
    if (fabs(denom) < 1e-12) return NULL;
    double t = ((Cx - Ax)*sy - (Cy - Ay)*sx) / denom;
    double u = ((Cx - Ax)*ry - (Cy - Ay)*rx) / denom;
    if (t < 0) return NULL;
    if (u < 0 || u > 1) return NULL;
    double xi = Ax + t*rx, yi = Ay + t*ry;
    return Ponto_Criar(xi, yi);
}

PontoT raio_criar_fim(PontoT x, PontoT v) {
    double x0 = Ponto_get_x(x), y0 = Ponto_get_y(x);
    double vx = Ponto_get_x(v), vy = Ponto_get_y(v);
    double dx = vx - x0, dy = vy - y0;
    double scale = 1e6; // far-away sentinel
    return Ponto_Criar(x0 + dx*scale, y0 + dy*scale);
}
