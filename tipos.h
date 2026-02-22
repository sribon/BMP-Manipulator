#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

#define TODO_OK 0
#define ARCHIVO_NO_ENCONTRADO 10
#define NO_SE_PUEDE_CREAR_ARCHIVO 20
#define ERROR_MEMORIA -1
#define TAM_NOMBRE 70

typedef struct
{
    unsigned char azul;
    unsigned char verde;
    unsigned char rojo;
}t_pixel;

typedef struct
{
    unsigned short int bm;			        //(2 Bytes)
    unsigned int tamano;			        //(4 Bytes)
    unsigned int reservado;			        //(4 Bytes)
    unsigned int offset;			        //(4 Bytes)
    unsigned int tamanoMetadatos;		    //(4 Bytes)
    int ancho;                              //(4 Bytes)
    int alto;			                    //(4 Bytes)
    unsigned short int numeroPlanos;		//(2 Bytes)
    unsigned short int profundidadColor;    //(2 Bytes)
}t_metadata;

#endif // TIPOS_H_INCLUDED
