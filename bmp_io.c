#include "bmp_io.h"

/*********************************************************************************/

void leerMetadata(FILE *archivo, t_metadata *metadata)
{
    fseek(archivo, 0, SEEK_SET);
    fread(&metadata->bm, sizeof (char), 2, archivo);
    fread(&metadata->tamano, sizeof (int), 1, archivo);
    fread(&metadata->reservado, sizeof (int), 1, archivo);
    fread(&metadata->offset, sizeof (int), 1, archivo);
    fread(&metadata->tamanoMetadatos, sizeof (int), 1, archivo);
    fread(&metadata->ancho, sizeof (int), 1, archivo);
    fread(&metadata->alto, sizeof (int), 1, archivo);
    fread(&metadata->numeroPlanos, sizeof (short int), 1, archivo);
    fread(&metadata->profundidadColor, sizeof (short int), 1, archivo);
}

/*********************************************************************************/

t_pixel **reservarMemoria(const int alto, const int ancho)
{
    int i;
    t_pixel **matriz;

    matriz = (t_pixel **)malloc(alto * sizeof(t_pixel *));
    if(!matriz)
    {
        return NULL;
    }

    for(i=0; i < alto; i++)
    {
        matriz[i] = (t_pixel *)malloc(ancho * sizeof(t_pixel));
        if(!matriz[i])
        {
            liberarMemoria(matriz, i);
            return NULL;
        }
    }

    return matriz;
}

/*********************************************************************************/

void liberarMemoria(t_pixel **matriz, const int alto)
{
    int i;

    for (i = 0; i < alto; i++)
        free(matriz[i]);
    free(matriz);
}

/*********************************************************************************/

void cargarMatriz(FILE *archivo, t_pixel **matriz, const unsigned int offset, const int ancho, const int alto)
{
    int i, j;
    fseek(archivo, offset, SEEK_SET);
    for(i=0; i < alto; i++)
    {
        for(j=0; j < ancho; j++)
            fread(&matriz[i][j], sizeof(t_pixel), 1, archivo);
    }
}

/*********************************************************************************/

void copiarMatriz(const t_pixel **matriz, t_pixel **copia, const int ancho, const int alto)
{
    int i, j;
    for(i=0; i < alto; i++)
    {
        for(j=0; j < ancho; j++)
        {
            copia[i][j].azul = matriz[i][j].azul;
            copia[i][j].verde = matriz[i][j].verde;
            copia[i][j].rojo = matriz[i][j].rojo;
        }
    }
}

/*********************************************************************************/

void escribirEncabezado(FILE *archivo, const t_metadata *metadata)
{
    fseek(archivo, 0, SEEK_SET);
    fwrite(&metadata->bm, sizeof(char), 2, archivo);
    fwrite(&metadata->tamano, sizeof(int), 1, archivo);
    fwrite(&metadata->reservado, sizeof(int), 1, archivo);
    fwrite(&metadata->offset, sizeof(int), 1, archivo);
    fwrite(&metadata->tamanoMetadatos, sizeof(int), 1, archivo);
    fwrite(&metadata->ancho, sizeof(int), 1, archivo);
    fwrite(&metadata->alto, sizeof(int), 1, archivo);
    fwrite(&metadata->numeroPlanos, sizeof(short int), 1, archivo);
    fwrite(&metadata->profundidadColor, sizeof(short int), 1, archivo);
}

/*********************************************************************************/

void modificarMetadataRotar(t_metadata *nuevo, const t_metadata *original)
{
    nuevo->bm = original->bm;
    nuevo->reservado = original->reservado;
    nuevo->offset = original->offset;
    nuevo->tamanoMetadatos = original->tamanoMetadatos;
    nuevo->ancho = original->alto;
    nuevo->alto = original->ancho;
    nuevo->numeroPlanos = original->numeroPlanos;
    nuevo->profundidadColor = original->profundidadColor;

    int padding = calcularPadding(nuevo->ancho);
    int bytesPorFila = (nuevo->ancho * sizeof(t_pixel)) + padding;
    int tamanoImg = bytesPorFila * nuevo->alto;
    nuevo->tamano = nuevo->offset + tamanoImg;
}

/*********************************************************************************/

void modificarMetadataRecortar(t_metadata *nuevo, const t_metadata *original, int num)
{
    nuevo->bm = original->bm;
    nuevo->reservado = original->reservado;
    nuevo->offset = original->offset;
    nuevo->tamanoMetadatos = original->tamanoMetadatos;
    nuevo->ancho = original->ancho * num / 100;
    nuevo->alto = original->alto * num / 100;
    int padding = calcularPadding(nuevo->ancho);
    nuevo->tamano = (nuevo->ancho * sizeof(t_pixel) + padding) * nuevo->alto;
    nuevo->numeroPlanos = original->numeroPlanos;
    nuevo->profundidadColor = original->profundidadColor;
}

/*********************************************************************************/

void modificarMetadataAchicar(t_metadata *nuevo, const t_metadata *original, int num)
{
    nuevo->bm = original->bm;
    nuevo->reservado = original->reservado;
    nuevo->offset = original->offset;
    nuevo->tamanoMetadatos = original->tamanoMetadatos;
    nuevo->ancho = round(original->ancho * num / 100.0);
    nuevo->alto = round(original->alto * num / 100.0);
    int padding = calcularPadding(nuevo->ancho);
    nuevo->tamano = (nuevo->ancho * sizeof(t_pixel) + padding) * nuevo->alto + nuevo->offset;

    nuevo->numeroPlanos = original->numeroPlanos;
    nuevo->profundidadColor = original->profundidadColor;
}

/*********************************************************************************/

void modificarMetadataConcat(t_metadata *nuevo, const t_metadata *original, int alto, int ancho)
{
    nuevo->bm = original->bm;
    nuevo->reservado = original->reservado;
    nuevo->offset = original->offset;
    nuevo->tamanoMetadatos = original->tamanoMetadatos;
    nuevo->ancho = ancho;
    nuevo->alto = alto;
    int padding = calcularPadding(nuevo->ancho);
    nuevo->tamano = nuevo->offset + (nuevo->ancho * sizeof(t_pixel) + padding) * nuevo->alto;
    nuevo->numeroPlanos = original->numeroPlanos;
    nuevo->profundidadColor = original->profundidadColor;
}

/*********************************************************************************/

int calcularPadding(int ancho)
{
    int padding = (4 - (ancho * sizeof(t_pixel)) % 4) % 4;
    return padding;
}

/*********************************************************************************/
