# 🖼️ Manipulación de imágenes bmp

Se solicita realizar un programa en lenguaje C llamado bmpmanipulator, que a partir de un archivo BMP de 24 bits de profundidad genere otro archivo BMP con las modificaciones solicitadas como argumentos a main. 


### 📌 Ejemplo
> bmpmanipuleitor.exe --negativo imagen.bmp

Debe generar un archivo llamado *"negativo_imagen.bmp"* que contenga la misma imagen, pero con los colores invertidos.

Del mismo modo, deberá soportar las siguientes funcionalidades:

***--escala-de-grises*** // deberá promediar los valores de cada color RGB y transformarlo a gris.

***--espejar-horizontal*** // deberá invertir horizontalmente la imagen.

***--espejar-vertical*** // deberá invertir la imagen verticalmente.

***--aumentar-contraste=10*** // aumenta el contraste en un 10%.

***--reducir-contraste=20*** // reduce el contraste en un 20%.

***--tonalidad-azul=50*** // aumenta en un 50% la intensidad del color azul.

***--tonalidad-verde=5*** // aumenta en un 5% la intensidad del color verde. 

***--tonalidad-roja=15*** // aumenta en un 15% la intensidad del color rojo.

***--recortar=30*** // reduce el tamaño de la imagen al 30%, sin cambiar sus proporciones, solamente descarta lo que exceda ese tamaño. Por ejemplo: una imagen de 1000px x 500px, deberá mantener todos los píxeles que estén entre 0 y 299 en el eje X y entre 0 y 149 el eje Y.

***--achicar=10*** // reduce la imagen al 10%. Por ejemplo: una imagen de 1000px x 500px, deberá reescribir todos los píxeles para que se ubiquen entre 0 y 99 en el eje X y entre 0 y 49 el eje Y, formando la misma imagen inicial (con peor calidad, claro).

Estas últimas siete funcionalidades requieren que el porcentaje llegue como argumento y tolere cualquier número entre 0 y 100 (no es necesario que pueda aumentar un 200%, por decir, deben validar que los parámetros tengan el rango adecuado).

***--rotar-derecha*** // gira la imagen 90 grados a la derecha (sentido horario).

***--rotar-izquierda*** // gira la imagen 90 grados a la izquierda (sentido antihorario).

***--concatenar-horizontal*** // recibirá como argumento dos imágenes, y creará una nueva con el contenido de ambas, una al lado de la otra. En caso de tener distinto alto, la más pequeña se rellenará con algún color a gusto (que no sea ni blanco ni negro, dejando de lado el debate de que sean o no un color) hasta completar el alto.

***--concatenar-vertical*** // recibirá como argumento dos imágenes, y creará una nueva con el contenido de ambas, una arriba de la otra, en caso de tener distinto ancho, la más pequeña se rellenará con algún color a gusto (que no sea ni blanco ni negro, dejando de lado el debate de que sean o no un color) hasta completar el ancho de la otra.

***--comodin*** // una funcionalidad nueva, decidida por el grupo (no se puede repetir con alguna de las solicitadas previamente en el TP).


## 🛡️ Validaciones y manejo de errores
Los argumentos pueden enviarse de a uno, o de a varios, de modo que, en un solo llamado al programa, ejecute todas las modificaciones y genere todos los archivos necesarios. Si un parámetro es incorrecto, el error debe ser informado por consola, y ejecutar todos los otros filtros.

Si algún comando no pudiese ejecutarse, debe informarse el motivo (por ejemplo: no se pueden concatenar las imágenes porque sólo se haya enviado una por argumentos, archivo no encontrado, etc).

### 📌 Ejemplo completo
Un llamado válido al programa podría ser:
>bmpmanipuleitor.exe --negativo unlam.bmp --escala-de-grises --argumento-incorrecto-que-debera-ser-ignorado --aumentar-contraste=18 --negativo 

Ese llamado debería generar los archivos:
- escala-de-grises_unlam.bmp 
- negativo_unlam.bmp
- aumentar-contraste_unlam.bmp 

El argumento --negativo aparece dos veces, deberá ejecutarse sólo una. El argumento incorrecto no deberá generar ningún archivo ni abordar la ejecución del programa. Pero sí informar el error en pantalla. Todas las modificaciones deben hacerse sobre los archivos previamente mencionados, y no en el main.

## 🧩 Decisiones de diseño

+ Uso de memoria dinámica para matriz de píxeles.

+ No se realizan transformaciones dentro de main.

+ Validaciones exhaustivas antes de procesar datos.

+ Manejo manual de padding para respetar especificación BMP.

+ Modularización del proyecto:
  + "tipos.h": definición de estructuras y macros.
  + "bmp_io.h": lectura y escritura de archivos BMP, gestión de memoria dinámica y reconstrucción de headers.
  + "funciones.h": implementación de filtros y transformaciones sobre la matriz de píxeles.
  + "interfaz.h": gestión de la interacción del usuario y validación de los argumentos enviados por línea de consola.

## 👨‍💻 Autor
**Santiago Ribon**<br> 
*Estudiante Ingenieria en informática, UNLaM*
<p align = center>
  <a href="https://www.linkedin.com/in/santiago-ribon/" target="_blank">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/81/LinkedIn_icon.svg/3840px-LinkedIn_icon.svg.png" width=30px>
  </a>
  <a href="https://github.com/TU-USUARIO-GITHUB" target="_blank">
    <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/github/github-original.svg" width="35" height="35">
  </a>
</p>

