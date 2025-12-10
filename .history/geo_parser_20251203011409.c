#include "geo_parser.h"
#include "segment.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Minimal parser: supports lines:
   r id x y w h corb corp
   c id x y r corb corp
   For other commands, ignore.
   This parser creates geometric objects as segments directly (rectangle -> 4 segments; circle -> 1 horizontal segment)
   Note: points allocated are owned by segments.
*/

int GeoParser_Ler(const char* caminho_geo, ListT formas) {
    if (!caminho_geo || !formas) return -1;

    FILE* f = fopen(caminho_geo, "r");
    if (!f) return -1;

    char cmd[32];
    while (fscanf(f, "%31s", cmd) == 1) {
        if (strcmp(cmd, "r") == 0) {
            int id; double x,y,w,h; char corb[32], corp[32];
            if (fscanf(f, "%d %lf %lf %lf %lf %31s %31s",
                       &id, &x, &y, &w, &h, corb, corp) >= 6) {
                PontoT bl = Ponto_Criar(x,y);
                PontoT br = Ponto_Criar(x+w,y);
                PontoT tr = Ponto_Criar(x+w,y+h);
                PontoT tl = Ponto_Criar(x,y+h);
                List_Inserir(formas, Segmento_Criar(id, bl, br, corb));
                List_Inserir(formas, Segmento_Criar(id, br, tr, corb));
                List_Inserir(formas, Segmento_Criar(id, tr, tl, corb));
                List_Inserir(formas, Segmento_Criar(id, tl, bl, corb));
            }
        } else if (strcmp(cmd, "c") == 0) {
            int id; double x,y,r; char corb[32], corp[32];
            if (fscanf(f, "%d %lf %lf %lf %31s %31s",
                       &id, &x, &y, &r, corb, corp) >= 5) {
                // Represent circle as a horizontal diameter segment
                PontoT left  = Ponto_Criar(x-r, y);
                PontoT right = Ponto_Criar(x+r, y);
                List_Inserir(formas, Segmento_Criar(id, left, right, corb));
            }
        } else {
            /* skip rest of line */
            char line[256];
            fgets(line, sizeof(line), f);
        }
    }

    fclose(f);
    return 0;
}
