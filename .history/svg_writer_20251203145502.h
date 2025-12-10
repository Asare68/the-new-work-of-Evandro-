#ifndef SVG_WRITER_H
#define SVG_WRITER_H

#include "list.h"
#include <stdio.h>

// Main entry point: generates SVG from parsed shapes
int SvgWriter_Gerar(const char* caminho_svg, ListT formas);

// Extra drawing helpers for custom visuals
void SvgWriter_DrawShield(FILE *fp, double x, double y, double size);
void SvgWriter_DrawGrid(FILE *fp, int rows, int cols, double startX, double startY, double size, double spacing);
void SvgWriter_DrawDottedCircle(FILE *fp, double cx, double cy, double radius, int dots);
void SvgWriter_DrawAsterisk(FILE *fp, double cx, double cy, double size);

#endif // SVG_WRITER_H
