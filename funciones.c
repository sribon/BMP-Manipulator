#include "funciones.h"

/*********************************************************************************/

int negativo(t_pixel **copia, const t_metadata *metadata, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "negativo_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, metadata->offset, SEEK_SET);

    for(i=0; i < metadata->alto; i++)
    {
        for(j=0; j < metadata->ancho; j++)
        {
            copia[i][j].azul = 255 - copia[i][j].azul;
            copia[i][j].verde = 255 - copia[i][j].verde;
            copia[i][j].rojo = 255 - copia[i][j].rojo;

            fwrite(&copia[i][j], sizeof(t_pixel), 1, archivo);
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int escalaGrises(t_pixel **copia, const t_metadata *metadata, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "escala-de-grises_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;
    unsigned char promedio;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, metadata->offset, SEEK_SET);

    for(i=0; i < metadata->alto; i++)
    {
        for(j=0; j < metadata->ancho; j++)
        {
            promedio = (copia[i][j].azul + copia[i][j].verde + copia[i][j].rojo) / 3;
            copia[i][j].azul = promedio;
            copia[i][j].verde = promedio;
            copia[i][j].rojo = promedio;
            fwrite(&copia[i][j], sizeof(t_pixel), 1, archivo);
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int espejar_horizontal(const t_pixel **matriz, const t_metadata *metadata, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "espejar-horizontal_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, metadata->offset, SEEK_SET);

    for(i=0; i < metadata->alto; i++)
    {
        for(j=0; j < metadata->ancho; j++)
        {
            fwrite(&matriz[i][metadata->ancho - j - 1], sizeof(t_pixel), 1, archivo);
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int espejar_vertical(const t_pixel **matriz, const t_metadata *metadata, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "espejar-vertical_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, metadata->offset, SEEK_SET);

    for(i=0; i < metadata->alto; i++)
    {
        for(j=0; j < metadata->ancho; j++)
        {
            fwrite(&matriz[metadata->alto - i - 1][j], sizeof(t_pixel), 1, archivo);
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int tonalidadAzul(t_pixel **copia, const t_metadata *metadata, int num, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "tonalidad-azul_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;
    float porcentaje = (float)num/100 + 1;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, metadata->offset, SEEK_SET);

    for(i=0; i < metadata->alto; i++)
    {
        for(j=0; j < metadata->ancho; j++)
        {
            if(copia[i][j].azul * porcentaje > 255)
                copia[i][j].azul = 255;
            else
                copia[i][j].azul = copia[i][j].azul * porcentaje;
            fwrite(&copia[i][j], sizeof(t_pixel), 1, archivo);
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int tonalidadVerde(t_pixel **copia, const t_metadata *metadata, int num, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "tonalidad-verde_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;
    float porcentaje = (float)num/100 + 1;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, metadata->offset, SEEK_SET);

    for(i=0; i < metadata->alto; i++)
    {
        for(j=0; j < metadata->ancho; j++)
        {
            if(copia[i][j].verde * porcentaje > 255)
                copia[i][j].verde = 255;
            else
                copia[i][j].verde = copia[i][j].verde * porcentaje;
            fwrite(&copia[i][j], sizeof(t_pixel), 1, archivo);
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int tonalidadRoja(t_pixel **copia, const t_metadata *metadata, int num, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "tonalidad-roja_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;
    float porcentaje = (float)num/100 + 1;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, metadata->offset, SEEK_SET);

    for(i=0; i < metadata->alto; i++)
    {
        for(j=0; j < metadata->ancho; j++)
        {
            if(copia[i][j].rojo * porcentaje > 255)
                copia[i][j].rojo = 255;
            else
                copia[i][j].rojo = copia[i][j].rojo * porcentaje;
            fwrite(&copia[i][j], sizeof(t_pixel), 1, archivo);
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int recortarImagen(const t_pixel **matriz, const t_metadata *metadata, int num, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "recortar_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    t_metadata nuevo_metadata;
    int i, j;
    unsigned char padding[3] = {0, 0, 0};

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Modifica tama�o, alto y ancho de la imagen
    modificarMetadataRecortar(&nuevo_metadata, metadata, num);

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, &nuevo_metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, nuevo_metadata.offset , SEEK_SET);

    for(i = nuevo_metadata.alto; i > 0; i--)
    {
        for(j=0; j < nuevo_metadata.ancho; j++)
        {
            fwrite(&matriz[metadata->alto - i][j], sizeof(t_pixel), 1, archivo);
        }
        fwrite(padding, calcularPadding(nuevo_metadata.ancho), 1, archivo);
    }

    fclose(archivo);
    return TODO_OK;

}

/*********************************************************************************/

int aumentarContraste(t_pixel **copia, const t_metadata *metadata, int num, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "aumentar-contraste_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;
    unsigned char promedio;
    float pMayor = 1 + (float)num/100;
    float pMenor = 1 - (float)num/100 ;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, metadata->offset, SEEK_SET);

    for(i=0; i < metadata->alto; i++)
    {
        for(j=0; j < metadata->ancho; j++)
        {
            promedio = (copia[i][j].azul + copia[i][j].verde + copia[i][j].rojo) / 3;

            if(promedio > 127)
            {
                if(copia[i][j].azul * pMayor < 255)
                    copia[i][j].azul = copia[i][j].azul * pMayor;
                else
                    copia[i][j].azul = 255;

                if(copia[i][j].verde * pMayor < 255)
                    copia[i][j].verde = copia[i][j].verde * pMayor;
                else
                    copia[i][j].verde = 255;

                if(copia[i][j].rojo * pMayor < 255)
                    copia[i][j].rojo = copia[i][j].rojo * pMayor;
                else
                    copia[i][j].rojo = 255;
            }

            if(promedio < 127)
            {
                copia[i][j].azul = copia[i][j].azul * pMenor;
                copia[i][j].verde = copia[i][j].verde * pMenor;
                copia[i][j].rojo = copia[i][j].rojo * pMenor;
            }
            fwrite(&copia[i][j], sizeof(t_pixel), 1, archivo);
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int reducirContraste(t_pixel **copia, const t_metadata *metadata, int num, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "reducir-contraste_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;
    unsigned char promedio;
    float pMayor = (float)num/100 + 1;
    float pMenor = 1 - (float)num/100 ;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, metadata->offset, SEEK_SET);

    for(i=0; i < metadata->alto; i++)
    {
        for(j=0; j < metadata->ancho; j++)
        {
            promedio = (copia[i][j].azul + copia[i][j].verde + copia[i][j].rojo) / 3;

            if(promedio <= 127)
            {
                if(copia[i][j].azul * pMayor < 127)
                    copia[i][j].azul = copia[i][j].azul * pMayor;
                else
                    copia[i][j].azul = 127;

                if(copia[i][j].verde * pMayor < 127)
                    copia[i][j].verde = copia[i][j].verde * pMayor;
                else
                    copia[i][j].verde = 127;

                if(copia[i][j].rojo * pMayor < 127)
                    copia[i][j].rojo = copia[i][j].rojo * pMayor;
                else
                    copia[i][j].rojo = 127;
            }

            if(promedio > 127)
            {
                if(copia[i][j].azul * pMenor > 127)
                    copia[i][j].azul = (copia[i][j].azul * pMenor);
                else
                    copia[i][j].azul = 127;

                if(copia[i][j].verde * pMenor > 127)
                    copia[i][j].verde = (copia[i][j].verde * pMenor);
                else
                    copia[i][j].verde = 127;

                if(copia[i][j].rojo * pMenor > 127)
                    copia[i][j].rojo = (copia[i][j].rojo * pMenor);
                else
                    copia[i][j].rojo = 127;
            }

            fwrite(&copia[i][j], sizeof(t_pixel), 1, archivo);
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int achicarImagen(const t_pixel **matriz, const t_metadata *metadata, int num, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "achicar_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    t_metadata nuevo_metadata;
    int i, j, k, l;
    int rSum, vSum, aSum, cont;
    t_pixel pixelPromedio;
    unsigned char padding[3] = {0, 0, 0};

    if (!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Modifica tama�o, alto y ancho de la imagen
    modificarMetadataAchicar(&nuevo_metadata, metadata, num);

    // Escribir el encabezado con la nueva metadata
    escribirEncabezado(archivo, &nuevo_metadata);

    // Posicionar el archivo en el comienzo de los datos de la imagen
    fseek(archivo, nuevo_metadata.offset, SEEK_SET);

    float incX = (float)metadata->ancho / nuevo_metadata.ancho;
    float incY = (float)metadata->alto / nuevo_metadata.alto;

    for (i = 0; i < nuevo_metadata.alto; i++)
    {
        for (j = 0; j < nuevo_metadata.ancho; j++)
        {
            rSum = 0;
            vSum = 0;
            aSum = 0;
            cont = 0;

            // Calcular coordenadas en la imagen original
            int origY = round(i * incY);
            int origX = round(j * incX);

            // Ajustar la suma de colores dentro del bloque correspondiente
            for (k = 0; k < (int)incY && origY + k < metadata->alto; k++)
            {
                for (l = 0; l < (int)incX && origX + l < metadata->ancho; l++)
                {
                    rSum += matriz[origY + k][origX + l].rojo;
                    vSum += matriz[origY + k][origX + l].verde;
                    aSum += matriz[origY + k][origX + l].azul;
                    cont++;
                }
            }

            pixelPromedio.rojo = rSum / cont;
            pixelPromedio.verde = vSum / cont;
            pixelPromedio.azul = aSum / cont;

            fwrite(&pixelPromedio, sizeof(t_pixel), 1, archivo);
        }
        fwrite(padding, calcularPadding(nuevo_metadata.ancho), 1, archivo);
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int rotarImagenDerecha(const t_pixel **matriz, const t_metadata *metadata, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "rotar-derecha_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    t_metadata nuevo_metadata;
    int i, j, padding;
    char relleno[3] = {0,0,0};

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Modifica alto y ancho de la imagen
    modificarMetadataRotar(&nuevo_metadata, metadata);

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, &nuevo_metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, nuevo_metadata.offset, SEEK_SET);

    padding = calcularPadding(nuevo_metadata.ancho);

    for (i = 0; i < nuevo_metadata.alto; i++) {
        for (j = 0; j < nuevo_metadata.ancho; j++) {
            fwrite(&matriz[j][nuevo_metadata.alto - i - 1], sizeof(t_pixel), 1, archivo);
        }
        fwrite(relleno, sizeof(char), padding, archivo);
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int rotarImagenIzquierda(const t_pixel **matriz, const t_metadata *metadata, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "rotar-izquierda_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    t_metadata nuevo_metadata;
    int i, j, padding;
    char relleno[3] = {0,0,0};

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Modifica alto y ancho de la imagen
    modificarMetadataRotar(&nuevo_metadata, metadata);

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, &nuevo_metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, nuevo_metadata.offset, SEEK_SET);

    padding = calcularPadding(nuevo_metadata.ancho);

    for (i = 0; i < nuevo_metadata.alto; i++)
    {
        for (j = 0; j < nuevo_metadata.ancho; j++)
        {
            fwrite(&matriz[nuevo_metadata.ancho - j - 1][i], sizeof(t_pixel), 1, archivo);
        }
        fwrite(relleno, sizeof(char), padding, archivo);
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int concatenarHorizontal(const t_pixel **matriz1, const t_pixel **matriz2, const t_metadata *metadata1, const t_metadata *metadata2, const char *nombImg1, const char *nombImg2)
{
    char nombArchivo[TAM_NOMBRE] = "concatenar-horizontal_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, "_");
    strcat(nombArchivo, nombImg2);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;
    t_metadata nuevo_metadata;
    int alto, ancho;
    t_pixel pixelVerde = {0, 255, 0};

    ancho = metadata1->ancho + metadata2->ancho;

    if(metadata1->alto > metadata2->alto)
        alto = metadata1->alto;
    else
        alto = metadata2->alto;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    modificarMetadataConcat(&nuevo_metadata, metadata1, alto, ancho);

    escribirEncabezado(archivo, &nuevo_metadata);

    fseek(archivo, nuevo_metadata.offset, SEEK_SET);

    for (i = 0; i < nuevo_metadata.alto; i++)
    {
        // Copiar p�xeles de la primera imagen
        for (j = 0; j < metadata1->ancho; j++)
        {
            if (i < metadata1->alto)
            {
                fwrite(&matriz1[i][j], sizeof(t_pixel), 1, archivo);
            }
            else
            {
                fwrite(&pixelVerde, sizeof(t_pixel), 1, archivo);
            }
        }

        // Copiar p�xeles de la segunda imagen
        for (j = 0; j < metadata2->ancho; j++)
        {
            if (i < metadata2->alto)
            {
                fwrite(&matriz2[i][j], sizeof(t_pixel), 1, archivo);
            }
            else
            {
                fwrite(&pixelVerde, sizeof(t_pixel), 1, archivo);
            }
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int concatenarVertical(const t_pixel **matriz1, const t_pixel **matriz2, const t_metadata *metadata1, const t_metadata *metadata2, const char *nombImg1, const char *nombImg2)
{
    char nombArchivo[TAM_NOMBRE] = "concatenar-vertical_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, "_");
    strcat(nombArchivo, nombImg2);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;
    t_metadata nuevo_metadata;
    int alto, ancho;
    t_pixel pixelVerde = {0, 255, 0};

    alto = metadata1->alto + metadata2->alto;

    if(metadata1->ancho > metadata2->ancho)
        ancho = metadata1->ancho;
    else
        ancho = metadata2->ancho;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    modificarMetadataConcat(&nuevo_metadata, metadata1, alto, ancho);

    escribirEncabezado(archivo, &nuevo_metadata);

    fseek(archivo, nuevo_metadata.offset, SEEK_SET);

    for (i = 0; i < metadata1->alto; i++)
    {
        // Copiar p�xeles de la primera imagen
        for (j = 0; j < nuevo_metadata.ancho; j++)
        {
            if (j < metadata1->ancho)
            {
                fwrite(&matriz1[i][j], sizeof(t_pixel), 1, archivo);
            }
            else
            {
                fwrite(&pixelVerde, sizeof(t_pixel), 1, archivo);
            }
        }
    }

    for (i = 0; i < metadata2->alto; i++)
    {
        // Copiar p�xeles de la primera imagen
        for (j = 0; j < nuevo_metadata.ancho; j++)
        {
            if (j < metadata2->ancho)
            {
                fwrite(&matriz2[i][j], sizeof(t_pixel), 1, archivo);
            }
            else
            {
                fwrite(&pixelVerde, sizeof(t_pixel), 1, archivo);
            }
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/

int comodin(t_pixel **copia, const t_metadata *metadata, const char *nombImg1)
{
    char nombArchivo[TAM_NOMBRE] = "comodin_";
    strcat(nombArchivo, nombImg1);
    strcat(nombArchivo, ".bmp");

    FILE *archivo = fopen(nombArchivo, "wb");
    int i, j;

    if(!archivo)
    {
        printf("Error en la creacion de la imagen '%s'", nombArchivo);
        fclose(archivo);
        return NO_SE_PUEDE_CREAR_ARCHIVO;
    }

    // Escribir el encabezado con la metadata
    escribirEncabezado(archivo, metadata);

    // Posiciono el archivo en el comienzo de los datos de la imagen
    fseek(archivo, metadata->offset, SEEK_SET);



    for(i=0; i < metadata->alto; i++)
    {
        for(j=0; j < metadata->ancho; j++)
        {
            if(j < metadata->ancho/3)
            {
                if(copia[i][j].rojo * 2 > 255)
                    copia[i][j].rojo = 255;
                else
                    copia[i][j].rojo = copia[i][j].rojo * 2;
                fwrite(&copia[i][j], sizeof(t_pixel), 1, archivo);
            }
            else if(j < metadata->ancho * 2 / 3)
            {
                if(copia[i][j].verde * 2 > 255)
                    copia[i][j].verde = 255;
                else
                    copia[i][j].verde = copia[i][j].verde * 2;
                fwrite(&copia[i][j], sizeof(t_pixel), 1, archivo);
            }
            else
            {
                if(copia[i][j].azul * 2 > 255)
                    copia[i][j].azul = 255;
                else
                    copia[i][j].azul = copia[i][j].azul * 2;
                fwrite(&copia[i][j], sizeof(t_pixel), 1, archivo);
            }
        }
    }

    fclose(archivo);
    return TODO_OK;
}

/*********************************************************************************/
