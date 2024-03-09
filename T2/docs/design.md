# DOCUMENTO DE DISEÑO T0 IIC2133

- Nombre Alumno: Tomás Tapia Pavez
- Email Alumno: tomastapia@uc.cl

## Análisis de enunciado
La primera parte del enunciado nos pide resolver un puzzle, en donde cada pieza (tile) tiene una letra de anclaje por cada lado. Por lo tanto, hay que encontrar la mejor forma de resolver un puzzle.

La segunda parte consiste en ir almacenando de forma eficiente escuadrones (cadenas de letras), para realizar consultas sobre la cantidad de los ya ingresados.

## Planificación de la solución
Para la primera parte debemos utilizar backtracking. El resolver un puzzle se puede asimilar a la solución de un laberinto (pseudocódigo en diapositiva clases). Debemos crear una función que verifique si una pieza encaja según el camino que se siga, es decir, hay que elegir un patrón (arriba, izquierda, derecha, abajo). Luego la función recursiva va probando posibles soluciones. Hay un pequeño problema, cuando el camino se encierra hay que iterar hasta la última tile que tenga un espacio vació para que lo revise. 

Para la segunda parte, al utilizar tablas de Hash, debemos definir una función que entregue un index para encontrar lo almacenado en nuestra tabla de Hash. Al recibir variados inputs, con largos variables también y además en desorden, fijaremos como largo de la tabla en 100 y se crearan funciones para darle un valor númerico a las cadenas de texto para que el desorden no sea un problema. En caso de coincidir largo de la cadena y la suma de las letras, se agrega una nueva llave que es la suma de las letras más repetidas. Generando así una eficiente forma de evitar problemas con las colisiones.

## Justificación
La justificación para utilizar backtracking se basa en su capacidad para manejar la complejidad de la resolución del puzzle, teniendo en cuenta diferentes caminos y condiciones de encierro. Además de la naturaleza de exploración necesaria para encontrar la mejor solución, sin pasar alguna por alto.

Las tablas de hash son una buena opción para este problema debido a su capacidad para realizar inserciones y búsquedas en tiempo constante, en promedio. El enfoque de utilizar una tabla con un tamaño fijo de 100 se justifica en parte por la cantidad variada de inputs y en parte por la necesidad de mantener un equilibrio entre el tamaño de la tabla y la eficiencia en el manejo de colisiones. 

Para evitar problemas de colisiones, se menciona la suma de las letras y la longitud de la cadena como factores para determinar la posición en la tabla. Esto se justifica en la necesidad de distribuir las cadenas de manera uniforme en la tabla y prevenir colisiones frecuentes. El agregar una nueva clave basada en la suma de letras más repetidas sirve para evitar conflictos en la tabla y garantizar un rendimiento eficiente y correcto en las operaciones de inserción y consulta.


## Referencias (Del documento de diseño)
La estructura de Tablas de Hash viene de los Talleres. 
https://github.com/IIC2133-PUC/Talleres/tree/master/hashing/hashtable/src/hashing
<!-- Enlace para bonus https://bonus.iic2133.org/redeem?code=eh32ixan1b8onef  -->
