#include "interfaz.h"

/*********************************************************************************/

int solucion(int argc, char* argv[])
{
    FILE *imagen1, *imagen2;
    t_metadata metadata1, metadata2;
    t_pixel **matriz1, **matriz2, **copia;
    char nombreImagen1[TAM_NOMBRE], nombreImagen2[TAM_NOMBRE];
    int numArch=1;

    // Abrir archivo bmp
    imagen1 = abrirArchivo(argc, argv, &numArch);
    extraerNombreArch(argv, &numArch, nombreImagen1);
    imagen2 = abrirArchivo(argc, argv, &numArch);
    extraerNombreArch(argv, &numArch, nombreImagen2);

    if(!imagen1)
    {
        puts("No se pudo leer la imagen");
        return ARCHIVO_NO_ENCONTRADO;
    }

    // Cargar encabezado en metadata
    leerMetadata(imagen1, &metadata1);

    // Reserva memoria para cargar los pixeles de la imagen
    matriz1 = reservarMemoria(metadata1.alto, metadata1.ancho);
    if(!matriz1)
    {
        fclose(imagen1);
        puts("Error de memoria");
        return ERROR_MEMORIA;
    }

    // Leer y cargar pixeles de la imagen en la matriz
    cargarMatriz(imagen1, matriz1, metadata1.offset, metadata1.ancho, metadata1.alto);

    fclose(imagen1);

    // Copiamos la matriz original para trabajar sobre ella
    copia = reservarMemoria(metadata1.alto, metadata1.ancho);
    if(!copia)
    {
        puts("Error de memoria");
        liberarMemoria(matriz1, metadata1.alto);
        return ERROR_MEMORIA;
    }

    if(imagen2 != NULL)
    {
        leerMetadata(imagen2, &metadata2);

        matriz2 = reservarMemoria(metadata2.alto, metadata2.ancho);

        if(matriz2 != NULL)
            cargarMatriz(imagen2, matriz2, metadata2.offset, metadata2.ancho, metadata2.alto);

        fclose(imagen2);
    }

    // Funcion que ejecuta accion segun lo pasado por argumento a main
    funcionesPorArgumentos((const t_pixel**)matriz1, (const t_pixel**)matriz2, &metadata1, &metadata2, copia, argc, argv, nombreImagen1, nombreImagen2);

    // Liberar memoria de la matriz
    liberarMemoria(matriz1, metadata1.alto);
    liberarMemoria(copia, metadata1.alto);
    liberarMemoria(matriz2, metadata2.alto);

    return TODO_OK;
}

/*********************************************************************************/

FILE *abrirArchivo(int argc, char* argv[], int *num)
{
    int i;

    for(i=*num; i<argc; i++)
    {
        // Si no comienza con -- es un archivo bmp
        if(strncmp(argv[i],"--",2) != 0 && validarBMP(argv[i]) == true)
        {
            if(fopen(argv[i], "rb") !=NULL)
            {
                *num += 1;
                return fopen(argv[i], "rb");
            }
        }

        *num += 1;
    }

    return NULL;
}

/*********************************************************************************/

void extraerNombreArch(char *argv[], int *pos, char *res)
{
    const char *nomArch = strrchr(argv[*pos - 1], '\\');
    if(nomArch == NULL)
        nomArch = argv[*pos - 1];
    else
        nomArch++;

    const char *punto = strrchr(nomArch, '.');
    if(punto == NULL)
        strcpy(res, nomArch);
    else
    {
        size_t longitud = punto - nomArch;
        strncpy(res, nomArch, longitud);
        res[longitud] = '\0';
    }
}

/*********************************************************************************/

bool validarBMP(const char *cad)
{
    const char *tipo = ".bmp";
    for(int i = 0; i < strlen(tipo); i++)
    {
        if(*(cad + strlen(cad) - 1 - i) != *(tipo + strlen(tipo) - 1 - i))
            return false;
    }
    return true;
}

/*********************************************************************************/

bool validarPorcentaje(const char *cad)
{
    char *letra = strchr(cad, '=') + 1;

    if(*letra == '\0')
        return false;

    while(*letra != '\0')
    {
        if(*letra < '0' || *letra > '9')
            return false;
        letra++;
    }

    return true;
}

/*********************************************************************************/

void funcionesPorArgumentos(const t_pixel **matriz1, const t_pixel **matriz2, const t_metadata *metadata1, const t_metadata *metadata2, t_pixel **copia, int argc, char *argv[], const char *nombImg1, const char *nombImg2)
{
    bool grises=false, azul=false, verde=false, rojo=false, aContraste=false, rContraste=false, neg=false, recortar=false, rotarD=false,\
            rotarI=false, esph=false, espv=false, achicar=false, concatH=false, concatV = false, com=false;
    int i, porcentaje;

    for(i=1; i<argc; i++)
    {
        // Si comienza con -- es una accion a realizar
        if(strncmp(argv[i], "--", 2) == 0)
        {
            if(grises == false && strcmp(argv[i], "--escala-de-grises") == 0)
            {
                // Cargo la matriz copia con los valores de la matriz original
                copiarMatriz(matriz1, copia, metadata1->ancho, metadata1->alto);
                escalaGrises(copia, metadata1, nombImg1);
                grises = true;
                puts("Funcion 'escala-de-grises' ejecutada correctamente.");
            }

            else if(neg == false && strcmp(argv[i], "--negativo") == 0)
            {
                copiarMatriz(matriz1, copia, metadata1->ancho, metadata1->alto);
                negativo(copia, metadata1, nombImg1);
                neg = true;
                puts("Funcion 'negativo' ejecutada correctamente.");
            }

            else if(azul == false && strncmp(argv[i], "--tonalidad-azul=", 17) == 0)
            {
                if(validarPorcentaje(argv[i]) == true)
                {
                    porcentaje = atoi(argv[i] + 17);
                    if(porcentaje >= 0 && porcentaje <= 100)
                    {
                        copiarMatriz(matriz1, copia, metadata1->ancho, metadata1->alto);
                        tonalidadAzul(copia, metadata1, porcentaje, nombImg1);
                        puts("Funcion 'tonalidad-azul' ejecutada correctamente.");
                    }
                    else
                        puts("El porcentaje ingresado en la funcion 'tonalidad-azul' debe estar comprendido entre 0 y 100.");
                }
                else
                    puts("El porcentaje ingresado en la funcion 'tonalidad-azul' no es valido.");
                azul = true;
            }

            else if(verde == false && strncmp(argv[i], "--tonalidad-verde=", 18) == 0)
            {
                if(validarPorcentaje(argv[i]) == true)
                {
                    porcentaje = atoi(argv[i] + 18);
                    if(porcentaje >= 0 && porcentaje <= 100)
                    {
                        copiarMatriz(matriz1, copia, metadata1->ancho, metadata1->alto);
                        tonalidadVerde(copia, metadata1, porcentaje, nombImg1);
                        puts("Funcion 'tonalidad-verde' ejecutada correctamente.");
                    }
                    else
                        puts("El porcentaje ingresado en la funcion 'tonalidad-verde' debe estar comprendido entre 0 y 100.");
                }
                else
                    puts("El porcentaje ingresado en la funcion 'tonalidad-verde' no es valido.");
                verde = true;
            }

            else if(rojo == false && strncmp(argv[i], "--tonalidad-roja=", 17) == 0)
            {
                if(validarPorcentaje(argv[i]) == true)
                {
                    porcentaje = atoi(argv[i] + 17);
                    if(porcentaje >= 0 && porcentaje <= 100)
                    {
                        copiarMatriz(matriz1, copia, metadata1->ancho, metadata1->alto);
                        tonalidadRoja(copia, metadata1, porcentaje, nombImg1);
                        puts("Funcion 'tonalidad-roja' ejecutada correctamente.");
                    }
                    else
                        puts("El porcentaje ingresado en la funcion 'tonalidad-roja' debe estar comprendido entre 0 y 100.");
                }
                else
                    puts("El porcentaje ingresado en la funcion 'tonalidad-roja' no es valido.");
                rojo = true;
            }

            else if(aContraste == false && strncmp(argv[i], "--aumentar-contraste=", 21) == 0)
            {
                if(validarPorcentaje(argv[i]) == true)
                {
                    porcentaje = atoi(argv[i] + 21);
                    if(porcentaje >= 0 && porcentaje <= 100)
                    {
                        copiarMatriz(matriz1, copia, metadata1->ancho, metadata1->alto);
                        aumentarContraste(copia, metadata1, porcentaje, nombImg1);
                        puts("Funcion 'aumentar-contraste' ejecutada correctamente.");
                    }
                    else
                        puts("El porcentaje ingresado en la funcion 'aumentar-contraste' debe estar comprendido entre 0 y 100.");
                }
                else
                    puts("El porcentaje ingresado en la funcion 'aumentar-contraste' no es valido.");
                aContraste = true;
            }

            else if(rContraste == false && strncmp(argv[i], "--reducir-contraste=", 20) == 0)
            {
                if(validarPorcentaje(argv[i]) == true)
                {
                    porcentaje = atoi(argv[i] + 20);
                    if(porcentaje >= 0 && porcentaje <= 100)
                    {
                        copiarMatriz(matriz1, copia, metadata1->ancho, metadata1->alto);
                        reducirContraste(copia, metadata1, porcentaje, nombImg1);
                        puts("Funcion 'reducir-contraste' ejecutada correctamente.");
                    }
                    else
                        puts("El porcentaje ingresado en la funcion 'reducir-contraste' debe estar comprendido entre 0 y 100.");
                }
                else
                    puts("El porcentaje ingresado en la funcion 'reducir-contraste' no es valido.");
                rContraste = true;
            }

            else if(recortar == false && strncmp(argv[i], "--recortar=", 11) == 0)
            {
                if(validarPorcentaje(argv[i]) == true)
                {
                    porcentaje = atoi(argv[i] + 11);
                    if(porcentaje >= 0 && porcentaje <= 100)
                    {
                        recortarImagen(matriz1, metadata1, porcentaje, nombImg1);
                        puts("Funcion 'recortar' ejecutada correctamente.");
                    }
                    else
                        puts("El porcentaje ingresado en la funcion 'recortar' debe estar comprendido entre 0 y 100.");
                }
                else
                    puts("El porcentaje ingresado en la funcion 'recortar' no es valido.");
                recortar = true;
            }

            else if(achicar == false && strncmp(argv[i], "--achicar=", 10) == 0)
            {
                if(validarPorcentaje(argv[i]) == true)
                {
                    porcentaje = atoi(argv[i] + 10);
                    if(porcentaje >= 0 && porcentaje <= 100)
                    {
                        achicarImagen(matriz1, metadata1, porcentaje, nombImg1);
                        puts("Funcion 'achicar' ejecutada correctamente.");
                    }
                    else
                        puts("El porcentaje ingresado en la funcion 'achicar' debe estar comprendido entre 0 y 100.");
                }
                else
                    puts("El porcentaje ingresado en la funcion 'achicar' no es valido.");
                achicar = true;
            }

            else if(rotarD == false && strcmp(argv[i], "--rotar-derecha") == 0)
            {
                rotarImagenDerecha(matriz1, metadata1, nombImg1);
                rotarD = true;
                puts("Funcion 'rotar-derecha' ejecutada correctamente.");
            }

            else if(rotarI == false && strcmp(argv[i], "--rotar-izquierda") == 0)
            {
                rotarImagenIzquierda(matriz1, metadata1, nombImg1);
                rotarI = true;
                puts("Funcion 'rotar-izquierda' ejecutada correctamente.");
            }

            else if(esph == false && strcmp(argv[i], "--espejar-horizontal") == 0)
            {
                //copiarMatriz(matriz1, copia, metadata1->ancho, metadata1->alto);
                espejar_horizontal(matriz1, metadata1, nombImg1);
                esph = true;
                puts("Funcion 'espejado-horizontal' ejecutada correctamente.");
            }

            else if(espv == false && strcmp(argv[i], "--espejar-vertical") == 0)
            {
                //copiarMatriz(matriz1, copia, metadata1->ancho, metadata1->alto);
                espejar_vertical(matriz1, metadata1, nombImg1);
                espv = true;
                puts("Funcion 'espejado-vertical' ejecutada correctamente.");
            }

            else if(concatH==false && matriz2 != NULL && strcmp(argv[i], "--concatenar-horizontal") == 0)
            {
                concatenarHorizontal(matriz1, matriz2, metadata1, metadata2, nombImg1, nombImg2);
                concatH = true;
                puts("Funcion 'concatenar-horizontal' ejecutada correctamente.");
            }

            else if(concatV==false && matriz2 != NULL && strcmp(argv[i], "--concatenar-vertical") == 0)
            {
                concatenarVertical(matriz1, matriz2, metadata1, metadata2, nombImg1, nombImg2);
                concatV = true;
                puts("Funcion 'concatenar-vertical' ejecutada correctamente.");
            }

            else if(matriz2 == NULL && strncmp(argv[i], "--concatenar", 12) == 0)
                puts("No se encontraron dos imagenes para concatenar");

            else if(com == false && strcmp(argv[i], "--comodin") == 0)
            {
                copiarMatriz(matriz1, copia, metadata1->ancho, metadata1->alto);
                comodin(copia, metadata1, nombImg1);
                com = true;
                puts("Funcion 'comodin' ejecutada correctamente.");
            }

            else
                printf("La funcion '%s' enviada por parametro no es valida.\n", argv[i]);
        }
    }

}

/*********************************************************************************/
