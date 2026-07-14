# FT_IRC
El Proyecto IRC con el Grupo A.

vamo a empezar: a 

**YURI:**
{
	Cree las clases de cada comando, cambie el "ACommand" para que todos utilicen la misma interfaz de "exec".
	En "CommandManager" voy crear la Logica de cada comando para que solo tengan que llamar a una clase. EJ:"manager.Pass(Server, User, Args).
	Ahora tenemos al "CommandManager" que recibe el nombre del comando (como PASS o JOIN), busca la clase y llama exec, asi el Server no necesita un 			switch 	gigante con todos los comandos y cada uno tiene su propia logica en cada clase.
	.
	**Añandi Channel(cpp y hpp) y cambie un poco a Server para añandir a create server y una busqueda de Users.**
}

**PAOLO y YOLANDA:**
{
	Hemos hecho el parseo inicial del mensaje, separando en argumentos que se guardan en un vector, mediante un split
	de la linea hasta que se encuentra el caracter ':', y luego el último argumento todo lo que haya tras este ':' (incluido).
	Y hemos añadido en User un map estático para la función getUser a partir del fd.
}

**YOLANDA:**
{
	He arreglado el problema que daba el mapa de usuarios dentro de User, lo malo es que requiere memoria dinámica, lo bueno es que ya lo he gestionado para que se libere todo bien (creo). Mañana habría que revisar el parseo y eliminar el salto de línea final de los comandos además de comprobar que termine por \r\n en vez de solo \n.
}