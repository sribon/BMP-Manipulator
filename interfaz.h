#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "tipos.h"
#include "bmp_io.h"
#include "filtros.h"

int solucion(int argc, char* argv[]);

FILE *abrirArchivo(int argc, char* argv[], int* num);
void extraerNombreArch(char *argv[], int *pos, char *res);
bool validarBMP(const char *cad);
bool validarPorcentaje(const char *cad);
void funcionesPorArgumentos(const t_pixel **matriz1, const t_pixel **matriz2, const t_metadata *metadata1, const t_metadata *metadata2, t_pixel **copia, int argc, char *argv[], const char *nombImg1, const char *nombImg2);

#endif // INTERFAZ_H_INCLUDED
