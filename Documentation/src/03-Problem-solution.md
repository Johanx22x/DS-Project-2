# Solución del problema

Teniendo en cuenta que debe ser posible crear, modificar y eliminar elementos 
de tipo vertice, arco y persona, se utilizaron clases donde se especificaron 
los atributos correspondientes a cada elemento, en conjunto con los metodos 
que ayudan a manejar inserciones, busquedas y eleminados de listas que poseen 
estos elementos, esto es de gran ayuda ya que se proporciona un entorno 
facil de utilizar y escalable para las futuras funcionalidades del programa.

Por otra parte, en vez de crear un menu donde se almacenan las opciones del 
programa, se decició utilizar una idea más modular, en este caso, utilizar 
comandos que se toman como elementos externos, los cuales se compilan a 
una libreria dinamica, la cual es posteriormente cargada por el programa. 
Esto ofrece el beneficio de tener un codigo más distribuido y limpio, 
de esta forma es mucho más facil trabajar en equipo.

Para crear, modificar y borrar se implementó un comando especifico para 
cada una de estas acciones, en donde se comprueban errores del usuario, 
de tipos y de datos, ofreciendo un sistema robusto. 

En cuanto a las consultas, estas son generadas posterior a iniciar la simulación 
de la caminata, esto debido a que es mucho más sencillo mostrar la 
información correspondiente a esta una vez generados los datos 
que de la simulación.

Por otra parte, las consultas requiren de datos variados, por lo cual 
para las consultas 5, 6 y 7 se utiliza una variable que supervisa si 
la simulación ya fue efectuada, de lo contrario el comando no mostrará 
ningún dato, en cuanto a las otras consultas, estas sí permiten 
utilizar su comando respectivo antes de ejecutar la simulación debido 
a que estas no dependen de ello.

El programa tambien requiere tener grafos previamente cargados, esto 
supone un problema, dado que es dificil tener una visión clara de que 
grafo está actualmente cargado y que elementos tiene, así que adicional 
a los requerimientos del sistema, se optó por almacenar los grafos en 
archivos binarios, de esta forma se puede identificar un grafo por su nombre, 
ser cargado, modificado, utilizado y luego nuevamente almacenado. Esto 
proporciona un sistema muy útil en cuanto a flexibilidad se refiere.

Adicionalmente, el programa permite generar un archivo PNG del grafo 
actualmente cargado en el programa, lo cual es sumamente útil para 
corroborar las salidas, tiempos de ejecución, y resultados proporcionados 
por el programa, se decidió implementar la opción del manejo de 
archivos y la generación de imagenes para proporcionar una experiencia más 
amena e interactiva al usuario.

Por otro lado, la forma en la que se desplazan las personas puede ser de 
4 tipos diferentes, aleatoria, adyacente, de un punto a otro y de un punto a 
otro atravezando todos los nodos, esta ultima opción siendo la más compleja de 
todas, debido a que fue posible calcular las rutas más cortas entre nodos, pero, 
no se pudo implementar completamente el sistema para que estos atraviesen todos los 
nodos del grafo, por lo cual estas personas se encuentran parcialmente inactivas durante 
el recorrido por los nodos. Además, en el caso del random se utiliza una función la 
cual retorna números en un rango de 1 a 50, esto es usado a la hora de crear un nuevo 
arco o al cargar los ya existentes en archivos, ninguno posee una medida fija, siendo 
totalmente aleatorio la medida que este arco tomará al ser cargado dentro del sistema.

Cabe destacar, que para las personas que se desplazan a traves de todos los nodos, se implementó 
el algoritmo de busqueda de rutas de Floyd, pero no se logró interpretar de forma correcta 
las rutas, por lo cual las personas con este tipo de movimiento se encuentran deshabilitadas.

Para los algoritmos de calculos de ruta y demás se utilizaron conceptos previamente 
analizados durante las clases, de modo que las consultas y las personas que requieren 
de la ruta más corta entre un determinado punto y otro se completo de manera exitosa, 
gracias a los conceptos analizados durante clases.

A continuación se definirá una solución más especifica para las consultas y reportes:

## Consultas:

### Consulta 1

En esta consulta se require apreciar el comportamiento de cada persona durante el 
recorrido, por lo cual cuando el usuario inicia la simulación, existen ya mensajes 
que se muestran exactamente cuando la persona realiza ciertas acciones, tales como 
si el usuario llega a un vertice, si el usuario se encuentra dirijiendose, entre otros 
avisos.

### Consulta 2

Para mostrar cual es la persona que logró encontrar más amigos se utiliza un ciclo que 
recorre a todas las personas buscando aquella que tiene más amigos, al finalizar el ciclo 
se obtiene la persona con más amigos dentro de una variable, posterior a esto se muestra 
la información respectiva de esta persona.

### Consulta 3

Para mostrar la persona que logró terminar de primero la caminata se utiliza una variable de 
un solo uso protegida por una condición, al finalizar la simulación se muestra la persona 
almacenada en esta variable.

### Consulta 4

Este caso es similar al anterior, solamente que la variable no está protegida, por lo cual 
la ultima persona que se almacena en esta variable es la ultima persona en finalizar la 
caminata.

## Reportes

### Reporte 1

Para imprimir el grafo en amplitud se utiliza una aplicación similar a la vista durante clases, 
de esta forma solamente se recorren los vertices y sus arcos.

### Reporte 2

Al igual que el reporte anterior se utiliza un algoritmo basado en el analizado durante la clase, 
por lo cual se logra completar este reporte y mostrar el grafo en profundidad desde el vertice que 
especifica el usuario.

### Reporte 3

Para mostrar a todas las personas almacenadas en la lista del programa simplemente se 
recorre y se muestran los datos respectivos al nombre, modo de desplazamiento y los puntos 
donde iniciar y termina su recorrido.

### Reporte 4

Para mostrar las rutas cortas de todas las personas se implementa uno de los algoritmos vistos en clase, 
con la excepción de que en vez de utilizar un string para almacenar la ruta, se utiliza una cola, de esta 
forma durante la ejecución de la simulación se determina a donde debe ir la persona gracias a esta cola, 
lo que sucede al ejecutar el reporte 4 es que se llama a la misma función que se encarga de esto e 
instantaneamente se muestra la ruta corta al usuario.

### Reporte 5

Para este reporte, como se mencionó anteriormente, el usuario debe de haber ejecutado el programa, 
para que de esta forma el usuario pueda obtener la información relacionada con los amigos que logró 
obtener cada persona, en este caso lo único que se hace es recorrer la sublista de amigos que posee la 
persona que el usuario determinó.

### Reporte 6

En el caso de este reporte, igualmente se requiere correr previamente la simulación, y contrario al reporte 
anterior, se determiná si la persona no encontró amigos, entonces se utiliza el método size() que ofrece 
la estructura dinamica para determinar si la persona no tiene amigos.

### Reporte 7

Para calcular este reporte y su resultado se requiere de varias fases, primero que nada las personas con 
tipo de movimiento directo o a través de todos los nodos, durante el calculo de su ruta, se determina 
si estos tienen camino accesible de su punto inicial a su punto final, por lo cual la clase persona tiene 
un atributo llamado hasPath que determina si la persona tiene una ruta a seguir, para los que poseen el 
tipo de movimiento aleatorio y adyacente, unicamente no tendrán una ruta la cual seguir si se encuentran 
en un vertice aislado del resto del grafo.

Cabe destacar que durante la ejecución de la simulación se tiene en cuenta varias condiciones y casos 
posibles que pueden ocurrir, por lo cual diferentes entradas claramente proporcionan distintos resultados 
una vez efectuada la simulación.

Adicionalmente, se puede apreciar tanto en [@fig:one] como en [@fig:two] dos de los grafos que se encuentran 
disposibles para utilizar en el programa, estas figuras fueron generadas por el propio programa, 
por lo cual se puede obtener cualquier imagen de un grafo que se encuentre en el programa, solamente 
debe de utilizarse el comando draw-graph para ello.

![[Grafo por defecto 1](https://weibeld.net/assets/icons/markdown.png)](images/grafo1.png){#fig:one}

![[Grafo por defecto 2](https://weibeld.net/assets/icons/markdown.png)](images/grafo2.png){#fig:two}
