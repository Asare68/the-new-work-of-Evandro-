#include "svg_writer.h"
#include "segment.h"
#include <stdio.h>
#include <math.h>
#include <string.h 
#  // for M_PI, cos, sin

// --- Helper functions ---
void SvgWriter_DrawShield(FILE *fp, double x, double y, double size) {
    double rectHeight = size * 0.3;

    // Gray rectangle top
    fprintf(fp, "<rect x='%f' y='%f' width='%f' height='%f' fill='gray' stroke='black'/>\n",
            x, y, size, rectHeight);

    // Triangular bottom divided into red, white, black
    double midX = x + size/2;
    double bottomY = y + size;
    fprintf(fp, "<polygon points='%f,%f %f,%f %f,%f' fill='red' stroke='black'/>\n",
            x, y+rectHeight, midX, bottomY, x+size/3, y+rectHeight);
    fprintf(fp, "<polygon points='%f,%f %f,%f %f,%f' fill='white' stroke='black'/>\n",
            x+size/3, y+rectHeight, midX, bottomY, x+2*size/3, y+rectHeight);
    fprintf(fp, "<polygon points='%f,%f %f,%f %f,%f' fill='black' stroke='black'/>\n",
            x+2*size/3, y+rectHeight, midX, bottomY, x+size, y+rectHeight);
}

void SvgWriter_DrawGrid(FILE *fp, int rows, int cols, double startX, double startY, double size, double spacing) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            double x = startX + c * (size + spacing);
            double y = startY + r * (size + spacing);
            SvgWriter_DrawShield(fp, x, y, size);
        }
    }
}

void SvgWriter_DrawAsterisk(FILE *fp, double cx, double cy, double size) {
    for (int i = 0; i < 8; i++) {
        double angle = M_PI * i / 4.0;
        double x = cx + size * cos(angle);
        double y = cy + size * sin(angle);
        fprintf(fp, "<line x1='%f' y1='%f' x2='%f' y2='%f' stroke='pink' stroke-width='2'/>\n",
                cx, cy, x, y);
    }
}

// --- Main SVG writer ---
int SvgWriter_Gerar(const char* caminho_svg, ListT formas) {
    if (!caminho_svg || !formas) return -1;
    FILE* f = fopen(caminho_svg, "w");
    if (!f) return -1;

    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    // Draw existing segments
    int n = List_Tamanho(formas);
    for (int i = 0; i < n; ++i) {
        SegmentoT s = (SegmentoT)List_Obter(formas, i);
        if (!s) continue;
        PontoT a = Segmento_get_ini(s), b = Segmento_get_fim(s);
        fprintf(f, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" />\n",
                Ponto_get_x(a), Ponto_get_y(a), Ponto_get_x(b), Ponto_get_y(b), Segmento_get_cor(s));
    }

    // Add your custom grid + asterisk
    SvgWriter_DrawGrid(f, 5, 7, 50, 50, 40, 10);
    SvgWriter_DrawAsterisk(f, 200, 200, 20);

    fprintf(f, "</svg>\n");
    fclose(f);
    return 0;
}
