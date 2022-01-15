# Trabajo Practico N6

Para este trabajo realice el mapeo en memoria de un archivo binario con mmap y lo almacene en un array de Structs que contenia variables del mismo tipo que hay en el archivo.  
Primero debia calcular cuantas estructuras habia, por lo tanto dividí el tamaño del archivo en el tamaño de cada estructura para obtener ese valor, luego mapeo el archivo y checkeo que no haya ningun error en ese proceso y por último imprimo toda la información solicitada y libero la memoria que había mapeado.