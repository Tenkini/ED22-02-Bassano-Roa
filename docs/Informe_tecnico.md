![image](https://user-images.githubusercontent.com/89607474/175754481-5f6cb929-0db7-4a5e-b0c6-326b57eed208.png)

# Informe Técnico 
## Curso: Estructura de datos
### Detección de personas en secuencias de imágenes

**Alumnos:**

* Daniel Bassano (Diseñador y programador)
* Matías Roa (Líder, administrador y programador)

## 1. Introducción

El presente trabajo es un informe técnico del sistema de detección y Re identificación de personas en secuencias de imágenes o videos. Este diseño es una posible solución a los requerimientos que se exigen, para desarrollar el trabajo se ha dividido en 13 objetivos a realizar
Se dan a conocer en el presente informe un resumen del trabajo realizado, una descripción del problema, el objetivo general y los objetivos específicos ya nombrados anteriormente. También se da a conocer la solución propuesta tanto lógica y técnicamente (Código)
Se informa sobre las herramientas, proceso de instalación de estas para realizar el trabajo, diseño e implementación a realizar.
También se anexa una bitácora de los hitos desarrollados, los resultados esperados/obtenidos y una conclusión final.

### 1.1 Descripción del problema

Un trabajador de la empresa ACME, en específico el guardia de esta requiere de un sistema que no solo detecte a
las personas que pasan por el edificio, también que entregue datos, flujos, estimaciones de las personas que la cámara va detectando.

### 1.2 Objetivos

**Objetivo General**

1.  Desarrollar e implementar un algoritmo funcional que entregue datos facilitados por un detector de OpenCV, para cumplir con los requerimientos de la empresa ACME.

**Objetivos específicos**

1.	Objetivo 01: Lectura y compresión del problema.
2.	Objetivo 02: Investigar la instalación y uso del editor a utilizar (Visual Studio Code). 
3.	Objetivo 03: Investigar/Adaptación al lenguaje de programación C++ e  la librería OpenCv y todas las funcionalidades que entregan estas.  
4.	Objetivo 04: Implementar y desarrollar métodos de un nodo.
5.	Objetivo 05: Implementar y desarrollar métodos de una lista enlazada simple. 
6.	Objetivo 06: Unificar todo el código implementado y que cubra los requerimientos solicitados.
7.	Objetivo 07: Lectura y compresión del problema actualizado.
8.	Objetivo 08: Implementar lectura de frames del video.
9.	Objetivo 09: Implementar y desarrollar metodos de una lista enlazada simple.
10.	Objetivo 10: Investigar sobre el arbol KdTree.
11.	Objetivo 11: Implementar arbol KdTree.
12.	Objetivo 12: Modelar lógica con árbol KdTree.
13.	Objetivo 13: Unificar todo el código implementado y que cubra los requerimientos solicitados.

### 1.3 Solución propuesta

Diseñar e implementar con POO y la librería OpenCV en C++, un algoritmo que realice la detección de objetos, en este caso personas.
La lógica a implementar es implementar un Arbol binario de tipo KdTree, que vaya almacenando a las personas que van siendo
detectadas por su "centroide".

## 2. Materiales y métodos

El desarrollo de este Proyecto se lleva a cabo con orientación a objetos en C++ en el editor de código fuente Visual Studio Code, utilizando todas las herramientas que entrega C++ y la biblioteca de openCv, se implementara la lógica definida para llevar a cabo el algoritmo de solución.

### 2.1 Instalación

Instalación hecha en Windows 10.

Las librerías utilizadas para la instalación y ejecución del código son los siguientes:
-	OpenCV: proporciona las herramientas para la visión artificial.
-	Iostream: Biblioteca estándar de C++, para manejar los dispositivos de entrada y salida.

En el caso de OpenCV se descargó de [su página web](https://opencv.org/) y se instaló con el .exe provisionado, además se agregó su path en las variables
de ambiente del sistema para que nuestro IDE y compilador las pudiera acceder.

### 2.2 Diseño 

Los componentes y clases usados son los siguientes:
-	Cmake: Herramienta para construir y empaquetar software.
-	Clase Detector: Objeto que detecta personas con la librería OpenCV mediante la detección HOGDescriptor en modo Default
-	Clase Persona: Objeto del cual se instanciará una persona con los siguientes atributos: x e y inicio, x e y fin, x e y centro, dados por el objeto cv::Rect
-	Clase KdTreNode: Objeto el cual tendrá como atributo posiciones de una persona.
-	Clase KdTree: TDA que almacenara los nodos de las cordenadas de las personas.

![diagrama drawio (2)](https://user-images.githubusercontent.com/89607474/179432484-9d13a862-d202-4aa5-8a2e-3c99a9a3174b.png)

### 2.3 Implementación

Para detectar personas tenemos el código de Detector.cpp que contiene una función detect(), la cual genera rectángulos con un centroide y que los convierte en clase persona por cada rectángulo diferente detectado, retornando un vector lleno de clases Persona. La clase Persona, contiene las posiciones del rectángulo dados por la librería OpenCV, que detecta personas con la detección HOGDescriptor en el modo Default.

En el main.cpp donde se encuentra el main() se generan instancias de clase Persona retornadas en un vector, el cual recorremos e ingresamos las instancias a nuestra estructura de datos (en modo de Nodo que contiene las coordenadas de esta persona), en este caso en un KD-Tree. Una vez procesado el frame del video saltamos al siguiente y volvemos dentro del ciclo iterador del vector de Persona. Aquí se itera sobre cada persona en el frame se busca su nodo mas cercano en el KD-Tree, esto se logra comparando distancias y buscando la menor, recién ahi se asume que son la misma persona. Se ocupó como valor arbitrario para discernir entre personas el "2", después de haber testeado los diferentes frames del vídeo. La lógica ocupada fue en 4 diferentes casos:

1. Cuando KD-Tree este vacío, se agrega inmediatamente una persona.
2. Cuando la cantidad de personas en el frame son iguales a la cantidad de personas en el árbol, se asume que son las mismas personas y se actualizan sus posiciones.
3. Cuando la cantidad personas en el frame es mayor a la cantidad personas en el árbol, se dice que hay personas en el frame que no son encontradas en el árbol, por lo tanto, se ingresan personas cuando la distancia entre la persona del frame y la persona mas cercana del árbol sea mayor a 2, esto porque se asume que si estan a tal distancia es porque son personas diferentes y cuando la distancia es menor a 2 son la misma persona.
4. Cuando la cantidad de personas en el frame es menor a la cantidad de personas en el árbol, se dice que sobran personas en el árbol, ya que, personas desaparecieron en el frame, por lo tanto, cuando la distancia es mayor a 2 entre una persona en el frame y una persona en el árbol, se asume que son diferentes personas entonces se elimina la persona en el árbol y cuando son distancias menores se actualizan las posiciones de la persona.

Con respecto a los requerimientos pedidos, el contador de personas entrantes y salientes, se hizo con la lógica que cuando una persona dentro del árbol se actualiza es porque se esta moviendo. Por esto cuando esta persona cumple con 3 condicionales se cuenta su salida o entrada. Estos condicionales fueron:

1. Que la persona en el árbol no haya sido contada ya
2. Que el "vector" de la persona en el eje y sea positivo o negativo, para su salida o entrada respectivamente. Esto se logró con un atributo de la persona en el árbol el cual contenía su posición en el eje y al momento de ser agregada al árbol, la cual se constrata con la posición actual en y, dando asi indicios si la persona va de arriba a abajo o al contrario.
3. Que la persona cruze la mitad de la pantalla.

Se tiene claro que la lógica debió hacerse con una matriz y no con valores arbitrarios de distancia, pero debido a problemas varios no se pudo implementar con eficacia, además por errores de calibración y conocimiento del detector de personas, está logica no cumple como debiera ser (véase anexo).

## 3. Resultados obtenidos

En comparacion a la entrega anterior, los resultados de este proyecto en parte fueron  fructíferos, se implementaron los requerimientos ( no eficazmente) solicitados.
Debido a que al igual que la entrega anterior se presentaron los mismos impedimientos; la sintaxis de C++, errores específicos que llevaron tiempo en solucionarse, errores de build y compatibilidades. Además de falta de conocimientode calibracion y utilización de la detección de personas.

## 4. Conclusiones

Se puede decir que, en términos de soluciones, se logró medianamente el objetivo del taller.
Por el lado de aprendizaje de trabajo multi-herramientas y mas cercano a lo profesional, se comprendió el tiempo y la responsabilidad necesaria para lograr resultados esperados.

# Anexos

## Anexo A: Errores detección, VS Code y sintaxis C++

Los errores y atrasos encontrados fueron muchos, debido a la poca familiaridad de trabajar en un proyecto multi-herramientas, esto sumado a la poca práctica con C++ costó al proyecto de poder implementar un código depurado y presentable. Esto se puede apreciar en que pocas funciones se ocuparon para hacer mas legible el código en el main de código repetido. Además, los muchos errores espontanéos, los cuales ocurrian al compartir los proyectos que cada participante hizo, atrasando asi días completos al tener que solucionarnos.

La poca familiaridad con el detector costó que al momento de ejecutar el código no se cumpla como se debieran los requermientos. Por ejemplo, cuando tenemos que hay la misma cantidad de personas en el frame y la misma cantidad de personas en el árbol se asumen que son las mismas personas, de frame a frame, pero cuando el detector dejaba de marcar a 1 persona y marcaba a otra nueva, esto se consideraba dentro de la lógica que eran la misma persona, pero con posiciones muy diferentes, que hacía que se cumplieran los condicionales del conteo y sumara 1, ya sea a la entrada o salida.

Uno de los errores que se presento constantemente en el transcurso del proyecto fue el "KN1120" el cual por la experiencia adquerida al realizar el codeo y investigacion, este error puede presentarse por cualquier motivo, provocando que solucionarlo se vuelva complicado y bastante consumidor de tiempo.

También la complejidad de VS Code produjo que se fuese incapaz de actualizar la versión de C++ a 17, para poder ocupar por ejemplo, filesystem, esto támbien impedió implementar las cosas eficientemente y claras.

## Ejemplo de errores de detección

![Captura de pantalla 2022-07-17 220714](https://user-images.githubusercontent.com/89607474/179436355-77a71386-99a7-4049-8568-1b4e56d6f184.png)

![Captura de pantalla 2022-07-17 220738](https://user-images.githubusercontent.com/89607474/179436363-8af9d07a-4314-4e06-bf01-d81af277fa37.png)

## Referencias

1. Vídeos ayuda de lógica del taller del profesor, Dr. Juan Bekios-Calfa en su canal de youtube, BekiosLab
2. Foro de ayuda de soluciones, información y corrección de errores: https://stackoverflow.com
3. GitHub de árbol binario KD-Tree: https://github.com/KorayGocmen/kdTree
