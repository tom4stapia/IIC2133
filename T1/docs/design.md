# DOCUMENTO DE DISEÑO T0 IIC2133

- Nombre Alumno: Tomás Tapia Pavez
- Email Alumno: tomastapia@uc.cl

## Análisis de enunciado

### Parte 1:
En esta parte hay que aplicar la estructura de árbol (BST). En las operaciones tenemos que implementar mecanismos de busqueda en profundidad, también de encontrar la altura de un valor en el árbol, ordenarlo con complejidad O(n), ordenar por nivel e invertirlo.

### Parte 2:
En esta parte hay que aplicar la estructura de QuadTree, se deben lograr realizar calculos de manera eficiente tales como desviación estándar y media. Para luego ir adaptando la imagen según ciertos parámetros. En compress hay que realizar busqueda binaria.

## Planificación de la solución

### Parte 1:
En todas las operaciones hay que tener en cuenta si el árbol está invertido o no. Al momento de buscar el PATH se revisan los hijos de los nodos comenzando desde el root del árbol para ver que camino tomar, si es que no se encontró al momento de llegar a un nodo sin hijos se marca la "X". El mecanismo de Deep value, se logra con una función recursiva que aumenta el nivel a medida que se buscan los nodos similarmente a la operación PATH. En ORDER, para revisar que los nodos esten en orden con complejidad O(n) es necesario recorrer cada nodo exactamente una vez, para no tener una complejidad mayor, esto se puede obtener con una función recursiva que recorra los hijos izquierdos primero y luego los derechos (depende si está invertido). DEEP-ORDER es aplicar el algoritmo BFS, en donde se va recorriendo cada nodo desde root, y agregandolos a un arreglo con sus respectivos hijos, formando así un orden por nivel. Finalmente INVERT es cambiar las posiciones de los nodos hijos desde root, recursivamente.

### Parte 2:
Para construir de buena manera el árbol, se debe realizar un struct de los nodos de este que posea la referencia a sus 4 hijos en el caso de tener (tendrá siempre y cuando el ancho de la imagen sea mayor a 1 pixel). Luego, debe tener los atributos de media y desviación estándar que deben ser calculados desde los nodos de más abajo (hojas) para arriba, siendo eficiente en el cálculo. La busqueda binaria es eficiente porque conocemos el rango de alpha (0 a 128), al no ser tan amplio es preciso y rápido el algoritmo.

## Justificación

### Parte 1:
PATH: los hijos de los nodos tienen un orden específico, es decir, si está a la izquierda es porque el value es menor y a la derecha es mayor (si es que no está invertido), es por esto que se recorre el árbol discriminando por el valor que posee cada nodo e hijos de este mismo. En DEEP es el mismo caso que PATH, pero se agrega el nivel a la función. ORDER tiene complejidad O(n) ya que al aplicar la función recursiva, el peor de los casos es que tenemos un árbol desequilibrado pareciendose a una lista ligada. DEEP-ORDER se necesita BFS ya que recorre los nodos por nivel no por profundidad. INVERT es simplemente cambiar los hijos de los nodos de posición obteniendo como resultado el árbol invertido.

### Parte 2:
El cálculo desde las hojas es eficiente porque ya conocemos la media anterior, entonces solo debemos agregarle un dato más sin tener que recorrer el árbol completo cada vez que se haga una recursión en el filtro alpha.  

## Referencias (Del documento de diseño)

<!-- Enlace para bonus https://bonus.iic2133.org/redeem?code=5sp6k30bgq5nfb6  -->