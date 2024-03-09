## DOCUMENTO DE DISEÑO T0 IIC2133

- Nombre Alumno: Tomás Tapia
- Email Alumno: tomastapia@uc.cl

### Análisis de enunciado

#### Estructuras:
- El enunciado nos muestra dos ejercitos DCChueck y Farquaad, los cuales tienen IDs únicos siendo 0 y 1 respectivamente. Estos tendrán una cantidad definida de escuadrones (Puede ser un arreglo).
- Los escuadrones tienen una cantidad variable de guerreros y tienen IDs únicos, poseen Guerreros. 
- Los Guerreros están en facciones (atributo), que puede ir desde 0 a 2. 

#### PARTE A:
- En el caso ENLISTAR, hay que guardar guerreros en un ejército.
- En el caso EQUIPAR, hay que guardar (solamente si hay espacio), un artefacto (número) en el arsenal.
- En el caso CONTEO-CAMPAL, hay que imprimir la cantidad de guerreros por ejercito divididos en facciones, sumando todos los existentes.

#### PARTE B:
- En el caso ORDEN-EJERCITO, hay que imprimir en orden los escuadrones con mayor cantidad de guerreros.
- En el caso DESERTAR, hay que borrar a un guerrero.
- En el caso ATACA, el cabezilla del escuadron con mayor valor de ataque base, atacará con su mejor arma del arsenal al cabezilla del escuadron enemigo con menor número de guerreros.

#### PARTE C:
- En el caso de TRAICIONAR, un guerrero abandona su escuadron para irse al con mayor número de miembros del ejército contrario.
- En el caso de ALTA-TRAICION, es similar a TRAICIONAR pero abandona una cantidad mayor o igual a 1 de guerreros (hasta el final del escuadron).


### Planificación de la solución

#### Estructuras:
- Los ejércitos seran arreglos de puntero a punteros, con largo definido utilizando calloc.
- En el arreglo de cada ejército, que tiene un puntero a un struct de Escuadrones que posee una lista ligada de Guerreros.
- El struct Guerrero tiene como atributos: ID, Vida, Daño Base, Arsenal (Es un arreglo que parte vacío), Largo Arsenal y Facción.

#### PARTE A:
- Al crear una instancia del struct Guerrero, este se debe insertar en el último guerrero del struct Escuadron, además si no exite un primer guerrero se debe almacenar ahí también.
- En este caso hay que recorrer el arreglo del arsenal que tiene un guerrero. Como el arsenal se crea con calloc, si hay un espacio libre (igual a 0), se almacena ahí el artefacto.
- En esta etapa, con contadores se recorren las listas ligadas de escuadrones de cada ejército.

#### PARTE B:
- El ejército se pasa a una matriz que será ordenada utilizando el algoritmo MergeSort. Este algoritmo consta de dos funciones para su correcto funcionamiento. La primera, merge, recibe 4 parámetros, los cuales son el arreglo que representa una matriz, el índice izquierdo de la submatriz, el del medio y el derecho. Estos índices se utilizan para crear submatrices (I y D) con los índices n1 y n2. Luego, se realiza una copia de los elementos pertenecientes a la matriz original en las submatrices. Siguiendo con el algoritmo, se crean los índices i, j y k para lograr una comparación entre los elementos en I y D, para ir insertandolos de manera ordenada en el arreglo original. Luego si sobran elementos en I o D se insertan en el mismo orden en el arreglo original.
Antes de empezar con la función merge, debemos llamar recursivamente a la función mergeSort para ir creando de izquierda a derecha mitades del arreglo dividido. Para finalmente llamar a merge, para unir todo en orden. 

- Para eliminar a un guerrero hay que buscar al guerrero anterior y que su siguiente guerrero sea el siguiente del eliminado, liberando la memoria del eliminado finalmente.
- En ATACA se debe recorrer los guerreros de cada lista ligada de los escuadrones, utilizando contadores se logra determinar lo pedido.

#### PARTE C:
- TRAICIONAR es muy similar a eliminar, solamente que en este caso no se libera esa memoria y se inserta al final de la lista ligada correspondiente (escuadron).
- ALTA-TRAICION es parecido a TRAICIONAR, solamente que hay que mover al guerrero seleccionado hasta el último guerrero del escuadrón, dejar como último guerrero del escuadrón original al anterior del seleccionado.

### Justificación

- Los ejércitos se guardan en una variable que contiene un arreglo de puntero a punteros para los escuadrones porque no varía su largo.
- Los guerreros en un escuadron están en una lista ligada al ser una cantidad variable. 
- El Arsenal es un arreglo ya que tiene largo definido.
- Utilicé el algoritmo MergeSort al no tener problemas con el uso de memoria, preferí priorizar el tiempo teniendo un peor de los casos O(n log(n)). 