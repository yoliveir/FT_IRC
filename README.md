# FT_IRC
El Proyecto IRC con el Grupo A.

vamo a empezar: a 

**YURI:**
{
	Cree las clases de cada comando, cambie el "ACommand" para que todos utilicen la misma interfaz de "exec".
	En "CommandManager" voy crear la Logica de cada comando para que solo tengan que llamar a una clase. EJ:"manager.Pass(Server, Client, Args).
	Ahora tenemos al "CommandManager" que recibe el nombre del comando (como PASS o JOIN), busca la clase y llama exec, asi el Server no necesita un 			switch 	gigante con todos los comandos y cada uno tiene su propia logica en cada clase.
}
