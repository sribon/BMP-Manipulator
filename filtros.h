#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>

#include "tipos.h"
#include "bmp_io.h"

int negativo(t_pixel **copia, const t_metadata *metadata, const char *nombImg1);
int escalaGrises(t_pixel **copia, const t_metadata *metadata, const char *nombImg1);
int espejar_horizontal(const t_pixel **matriz, const t_metadata *metadata, const char *nombImg1);
int espejar_vertical(const t_pixel **matriz, const t_metadata *metadata, const char *nombImg1);
int tonalidadAzul(t_pixel **copia, const t_metadata *metadata, int num, const char *nombImg1);
int tonalidadVerde(t_pixel **copia, const t_metadata *metadata, int num, const char *nombImg1);
int tonalidadRoja(t_pixel **copia, const t_metadata *metadata, int num, const char *nombImg1);
int recortarImagen(const t_pixel **matriz, const t_metadata *metadata, int num, const char *nombImg1);
int aumentarContraste(t_pixel **copia, const t_metadata *metadata, int num, const char *nombImg1);
int reducirContraste(t_pixel **copia, const t_metadata *metadata, int num, const char *nombImg1);
int achicarImagen(const t_pixel **matriz, const t_metadata *metadata, int num, const char *nombImg1);
int rotarImagenDerecha(const t_pixel **matriz, const t_metadata *metadata, const char *nombImg1);
int rotarImagenIzquierda(const t_pixel **matriz, const t_metadata *metadata, const char *nombImg1);
int concatenarHorizontal(const t_pixel **matriz1, const t_pixel **matriz2, const t_metadata *metadata1, const t_metadata *metadata2, const char *nombImg1, const char *nombImg2);
int concatenarVertical(const t_pixel **matriz1, const t_pixel **matriz2, const t_metadata *metadata1, const t_metadata *metadata2, const char *nombImg1, const char *nombImg2);
int comodin(t_pixel **copia, const t_metadata *metadata, const char *nombImg1);

#endif // FUNCIONES_H_INCLUDED
