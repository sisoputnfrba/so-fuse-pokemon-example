# FUSE_EJEMPLO_POKEMON

## Compilación

Como parametros de compilación se debe colocar:

+ *-DFUSE_USE_VERSION=27*
+ *-D_FILE_OFFSET_BITS=64*

Como parametros de linkeo se debe colocar:

+ *-lpthread*
+ *-lfuse*

## Ejecución

Previo a la ejecución se debe mover el directorio *fuse_pokemon* que tiene el contenido de los archivos (video, audio, imagen) a la ruta */home/utnso*. 
En caso contrario, modificar las rutas desde donde se abren los archivos en el código para que apunten al directorio fuse_pokemon en la ruta correspondiente del filesystem nativo.

Montar el ejemplo en el directorio tmp (directorio **existente** en la ruta donde estoy ejecutando el ejemplo y **vacío**):

 `./fuse_example tmp`  
 
 Ejecución en modo debug:
 
 `./fuse_example tmp -d` 
