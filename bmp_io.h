#ifndef BMP_IO_H_INCLUDED
#define BMP_IO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tipos.h"

void leerMetadata(FILE *archivo, t_metadata *metadata);

t_pixel **reservarMemoria(const int alto, const int ancho);
void liberarMemoria(t_pixel **matriz, const int alto);
void cargarMatriz(FILE *archivo, t_pixel **matriz, const unsigned int offset, const int ancho, const int alto);
void copiarMatriz(const t_pixel **matriz, t_pixel **copia, const int ancho, const int alto);

void escribirEncabezado(FILE *archivo, const t_metadata *metadata);
void modificarMetadataRecortar(t_metadata *nuevo, const t_metadata *original, int num);
void modificarMetadataRotar(t_metadata *nuevo, const t_metadata *original);
void modificarMetadataAchicar(t_metadata *nuevo, const t_metadata *original, int num);
void modificarMetadataConcat(t_metadata *nuevo, const t_metadata *original, int alto, int ancho);
int calcularPadding(int ancho);

#endif // BMP_IO_H_INCLUDED
