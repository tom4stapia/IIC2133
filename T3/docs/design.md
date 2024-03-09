# DOCUMENTO DE DISEÑO T3 IIC2133

- Nombre Alumno: Tomás Tapia Pavez
- Email Alumno: tomastapia@uc.cl

## Análisis de enunciado
Para el primer problema, debemos utilizar programación dinámica, ya que al realizar una fiesta en un pueblo hay que avanzar dos más para realizar otra, de esta forma se encontrará la mayor cantidad de oro posible.

En el segundo problema, hay que darle una funcionalidad multiple al algoritmo DFS, ya que al retirar una articulación se deben formar 2 o más componentes conexas. La funcionalidad múltiple va por encontrar la articulación mientras se calcula la cantidad de componentes que generaría retirar esa articulación.

En el último problema, se debe encontrar una forma de construir un MST con el objetivo de minimizar el máximo de aristas salientes de algún nodo.

## Planificación de la solución
Para el primer problema, mediante programación dinámica utilizaré una función recursiva, con memoria de lo ya calculado para que no tome una complejidad exponencial. De esta forma debemos buscar el maximo entre (maximo_oro(pueblos, pueblo - 1, soluciones), maximo_oro(pueblos, pueblo - 3, soluciones) + pueblos[pueblo]). De esta manera recorriendo para atras, llegaremos a la solución óptima.

Para el segundo problema, utilizaré un algoritmo que no es el más óptimo en términos de complejidad. Tomando cada nodo y asumiendo que sale del grafo buscare si genera mas de dos componentes, encontrando de esta manera si es una articulación y cuantas genera.

Para el último problema, implementaré el algoritmo de kruskal visto en clases. Para ordenar la lista implementare mergeSort. Ya ordenada las aristas según los costos voy recorriendo la lista buscando los menores hasta conseguir V - 1 aristas, buscando los nodos a unir con la función find para luego unirlos. Generando así un valor, no necesariamente óptimo, pero cercano a este.

## Justificación
Para el primer problema la programación dinámica es el camino a seguir porque es una técnica muy eficiente para resolver problemas de optimización, buscando subproblemas a resolver y no siendo redundante en algunas posibles soluciones.

Para el segundo problema, el uso de DFS es lo más indicado porque necesito recorrer un grafo entero buscando las articulaciones y a la vez las componentes conexas que genera.

Por último, el algoritmo de Kruskal es el indicado para resolver este problema. Ordenando las aristas por costo y luego ir recorriendolas en orden asegura que se construya el árbol de expansión mínima de una manera eficiente.

## Referencias (Del documento de diseño)
Para el último problema me base en https://www.geeksforgeeks.org/merge-sort/ para realizar el orden de las aristas para tener una menor complejidad al ordenar.
