[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/iUf1ycbw)
# Tarea 1 2023-2

Repositorio para el código base de la Tarea 1 del segundo semestre del 2023

Enlace a Tests de la Tarea:
[https://drive.google.com/drive/folders/1pob_8wDD6W57fhC58EnNExNfSLtDldow?usp=sharing](https://drive.google.com/drive/folders/1pob_8wDD6W57fhC58EnNExNfSLtDldow?usp=sharing)

Repositorio de Talleres y Capsulas útiles:
[https://github.com/IIC2133-PUC/Talleres](https://github.com/IIC2133-PUC/Talleres)

## Ejecución

Para compilar

```bash
make clean && make
```

Ejecutar parte BST

```bash
./bstRey input.txt output.txt
```

Ejecutar parte Quadtree

```bash
./hadaCompress imgs/egg_king.png out.png filter 5
```

## Librerias requridas

Debes instalar `libpng-dev` en caso que no lo tengas instalado. (Make avisara si no lo tienes instalado)

### WSL

```bash
sudo apt install libpng-dev
```

### macOS (Apple Silicon M1, M2)

Para ejecutar esta tarea en Mac con Apple Silicon, se debe utilizar un entorno virtualizado. Para reducir las complicaciones que pueden surgir de usar `edd-docker` desarrollamos dos nuevas herramientas que simplifican el proceso:

- [edd-runner](https://github.com/IIC2133-PUC/edd-runner)
- [edd-dev-container](https://github.com/IIC2133-PUC/edd-dev-container)

### macOS (Intel)

```bash
brew install libpng
brew install zlib
```

## Referencias

En node.c de BstRey cite código de ChatGPT, este fue adaptado entre las líneas 117 y 146 del código.
Para el QuadTree, me base en https://en.wikipedia.org/wiki/Quadtree para entender más sobre el árbol, siguiendo el pseudocódigo. 
