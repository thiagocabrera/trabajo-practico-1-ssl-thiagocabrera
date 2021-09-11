UTN – Regional Buenos Aires  
Sintaxis y Semántica de los Lenguajes
Curso K 2006
 
 	 
Trabajo Práctico N°1
Tema: Reconocimiento de palabras con autómatas


Nombre y Apellido: THIAGO MARTIN CABRERA LAVEZZI
Email institucional: tcabreralavezzi@frba.utn.edu.ar
Legajo: 175.868-8
Profesora: Ing. ROXANA L. LEITUZ
Fecha Presentación:  11/09/2021
Calificación:
Punto 1:

Terminales:

Los terminales que utilizamos son 6:
D: conjunto que contiene los decimales del 1 al 9.
Oct: conjunto que contiene los decimales del 1 al 7.
H: conjunto que contiene las letras de la ‘a’ la ‘f’ en minúscula y mayúscula.
S: conjunto que contiene al ‘+’ y al ‘-’.
x: la letra ‘x’.
0: el número 0.

Autómata:


Tabla de transiciones:



D
S
0
Oct
H
x
0-
1
2
3
1
7
7
1+
1
7
1
1
7
7
2
1
7
7
1
7
7
3+
7
7
4
4
7
5
4+
7
7
4
4
7
7
5
6
7
6
6
6
7
6+
6
7
6
6
6
7
7(rechazo)
7
7
7
7
7
7


Estrategia:

La cadena a analizar podemos pensarla como un conjunto de tokens separados por el carácter `&`. Teniendo esta información, utilizamos el strtok para iterar sobre la cadena, analizando cada token por separado.
Cada vez que al recorrer uno de estos tokens se llega al final, se aumentan los contadores, teniendo en cuenta el estado final: si es 1 o 3, quiere decir que el número es decimal, si es 4 octal. si es 6 hexadecimal y si no es ninguno de estos es un error léxico.
Si quisiéramos hacer un análisis completamente mediante autómatas, es decir sin utilizar la función strtok, sería tan simple como agregar una transición desde todos los estados finales al estado 0 con el carácter `&`.
El 0 decimal y el 0 octal.
En la resolución del problema nos surgió un desafío: ¿cómo diferenciamos a un cero decimal y a un cero octal? No podemos decir que es el mismo, ya que el 0 hexadecimal es diferente.
En base a esta preocupación decidimos tomar la palabra “0” como el cero decimal y la “00” como el cero octal. Para eso tuvimos que hacer del estado 3 un estado final, y agregar la transición por ‘0’ hasta 4.
Detección de errores.
Para la detección de errores, todo token que no termine en un estado final presenta un error léxico.

Punto 2:

Antes de comenzar a explicar el algoritmo, debemos mencionar que no se nos ocurrió una manera de conectar el análisis de este ejercicio con el autómata anterior, ya que este último también reconoce palabras en octal y en hexadecimal, por lo que nos reconocería tipos de palabras que no queremos reconocer en este ejercicio.

Autómata:

Tabla de transiciones:



D
0
+
-
*
0-
1
3
2
2
4
1+
1
1
0
0
0
2
1
4
4
4
4
3+
4
4
0
0
0
4(rechazo)
4
4
4
4
4


Estrategia:

Las diferentes funciones de los ‘+’ y ‘-’.
Para empezar a explicar el algoritmo, primero destacaremos que el autómata utilizado es capaz de diferenciar la utilización de los ‘+’ y los ‘-’. Estos caracteres pueden tener dos funciones en este ejercicio: de signado y de operación. Es decir, un ‘-’ no tiene la misma función en la cadena “-4” o “5+-4” que en las cadenas “5-4” y “5-+4”. Si sabemos en qué estado estamos parados, podemos deducir la función del operador. En este autómata, con saber que el estado actual es el 0 es suficiente para decir que la función es de operación. Es esto mismo lo que hace que este algoritmo reconozca cadenas como “5--4” como una operación, por lo que haría 5--4=5+4=9, que no es lo que sucede en el lenguaje de programación C, ya que este interpreta las palabras “--” y “++” como decremento e incremento de variables respectivamente.
Precedencia del ‘*’.
Otro tema importante a tratar en la resolución de este ejercicio es la precedencia de operaciones, ya que, como todos sabemos, la multiplicación se realiza siempre antes que la suma y la resta. Para esto decidimos meter en arrays muy grandes los términos y las operaciones a medida que son detectados. Si algún término presenta una multiplicación, se lleva a otra función donde loopeamos dentro de ese término multiplicando números entre sí hasta que el mismo termine o la cadena en sí. Las operaciones guardadas son solamente las que operan entre términos (es decir, ‘+’ y ‘-’).
Cálculo del resultado.
Al final de la lectura de la cadena, se recorre el array de operaciones, utilizando cada una para operar al primer elemento del array de términos con el siguiente al index de la operación en su respectivo array, y se guarda en la primera posición del array de términos. Al final del ejercicio, el resultado será este primer elemento, como se puede ver a continuación.

Si quisiéramos calcular el resultado en tiempo de lectura, podríamos utilizar una variable flag que nos indique si la operación actual es suma o resta, para que cuando se termina de leer el término, opere con el anterior. Ambas soluciones funcionan.
Detección de errores.
Para la detección de errores, fuimos capaces de diferenciar errores léxicos de errores de caracteres no pertenecientes al alfabeto. Para el primer tipo, si el estado ‘e’ es el estado de rechazo (comprobado en tiempo de lectura) entonces hay un error léxico. Para el segundo, si la columna correspondiente al carácter es la columna 5, quiere decir que el carácter no es ninguno de los aceptados. En ambos casos mandamos un mensaje a la consola especificando el tipo de error y la posición en la cadena y directamente retornamos false, para así evitar seguir corriendo el programa innecesariamente.
