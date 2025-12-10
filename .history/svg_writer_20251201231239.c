#include "../include/svg_writer.h"
#include "../include/segment.h"
#include <stdio.h>

int SvgWriter_Gerar(const char* caminho_svg, ListT formas) {
    if (!caminho_svg || !formas) return -1;
    FILE* f = fopen(caminho_svg, "w");
    if (!f) return -1;
    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    int n = List_Tamanho(formas);
    for (int i = 0; i < n; ++i) {
        SegmentoT s = (SegmentoT)List_Obter(formas, i);
        if (!s) continue;
        PontoT a = Segmento_get_ini(s), b = Segmento_get_fim(s);
        fprintf(f, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" />\n",
                Ponto_get_x(a), Ponto_get_y(a), Ponto_get_x(b), Ponto_get_y(b), Segmento_get_cor(s));
    }
    fprintf(f, "</svg>\n");
    fclose(f);
    return 0;
}
