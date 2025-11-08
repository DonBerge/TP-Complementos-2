---
title: "Your Desired Document Title"
author: "Your Name"
date: "November 7, 2025"
---
# Trabajo práctico 1
Integrantes: Agustín Fernández Bergé y Ramiro Gatto

## Estructura del proyecto
En la carpeta `src` se encuentran todas las implementaciones de rope más archivos auxiliares utilizados por las implementaciones, en particular:
- `ropeEnteros.cpp`: Es la implementación del rope pedido en la Parte 1, item a.
- `ropeEnterosLazy.cpp`: Es la implementación del rope pedido en la Parte 2, item a.
- `ropeGenerico.cpp`: Es la implementación del rope pedido en la Parte 1, item c.
- `ropeGenericoLazy.cpp`: Es la implementación del rope pedido en la Parte 2, item c.

En la carpeta `tests` se encuentran los casos de prueba usados para probar las implementaciones de arriba, cada test contiene un archivo `tester.cpp` que utiliza una implementación de rope para resolver un problema particular(el cual esta descrito en el mismo archivo `tester.cpp`). Los archivos de extensión `N.in` representan un caso de prueba particular y los archivos `N.out` su solución correspondiente.

En particular:
- `tests/ropeGenerico/Suma`: Contiene los casos de prueba para resolver el problema de suma de enteros en rango, pedido en la Parte 1, item d.
- `tests/ropeGenericoLazy/MaximoYSuma`: Contiene los casos de prueba para resolver el problema de actualización de suma en intervalo y consulta de máximo en un intervalo, pedido en la Parte 2, item d.

## Como correr los tests
El comando
```
make test
```
compilara cada archivo `tester.cpp` y ejecutara el ejecutable resultante con cada caso de prueba `N.in`, registrando la salida en un archivo `N.actual_out`. Si los archivos `N.actual_out` y `N.out` coinciden se mostrara un mensaje en pantalla indicando que el test es valido y se creara u archivo `N.check`. Este archivo es usado para no correr dos veces un test que ya fue valido.

El comando
```
make clean
```
borrara todos los archivos `*.actual_out`, `*.check` y `tester`. Se puede usar el comando para correr los tests nuevamente si es necesario ejecutarlos devuelta o si se hizo un cambio en las implementaciones de Rope.

### Ejemplo
```
make test_all
make[1]: se entra en el directorio '/home/XXX/XXX'
OK      tests/ropeEnteros/1
OK      tests/ropeEnteros/2
OK      tests/ropeEnteros/3
OK      tests/ropeEnteros/4
OK      tests/ropeEnteros/5
OK      tests/ropeEnteros/6
OK      tests/ropeEnteros/7
OK      tests/ropeEnterosLazy/1
OK      tests/ropeEnterosLazy/2
.... Más tests ....
```