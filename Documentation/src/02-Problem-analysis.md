# Análisis del problema

El presente sistema requiere de distintas funcionalidades que le permitan 
procesar y simular los datos referentes a los nodos, arcos y personas que 
se encuentran en el programa, principalmente que las estructuras puedan 
ser añadidas, modificadas y eliminadas. Por otro lado, require que 
estos datos interactuen entre si para simular caminatas de parte de las 
personas entre los nodos y los arcos, adicionalmente, cuando dos o más 
personas se encuentran en el mismo nodo estas deben de generar una 
relación de amistad. El programa debe ser capaz de manejar todos estos 
procesos de manera robusta y sin perdidas para el usuario.

Otra de las principales caracteristicas del programa es la de generar 
reportes y realizar consultas de parte del usuario, esto para tener 
control de los cambios que se generan posterior a realizar determinadas 
acciones dentro del programa.

Dentro del programa se deben de crear estructuras dinamicas para almacenar 
los datos, ademas de eso, se debe de manejar la informacion por punteros e 
intermediarios que permitan asociar los arcos a sus respectivos nodos, 
teniendo en cuenta tambien que cada persona debe de tener una lista de 
amigos.

Tomando en cuenta que los nodos representan lugares que se pueden visitar 
dentro de la simulacion, y los arcos las rutas por las cuales las personas 
viajan de un punto a otro, se debe de generar una solución para que 
el sistema tomando la distancia entre cada nodo, o sea, el peso de cada arco 
dentro del sistema, logré calcular el tiempo que dura una persona en viajar de 
un punto a otro, y de la misma forma, cuantas personas conoce en su llegada a 
un nodo antes de partir nuevamente hacia el siguiente nodo en su ruta.

El analisis respectivo a las consultas y reportes es relativo a la ejecución y 
los datos introducidos al programa, por lo cual se detallará su analisis y 
solución posteriormente.
