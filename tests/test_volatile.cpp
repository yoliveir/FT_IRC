#include <iostream>
#include <signal.h>

bool servidor_activo = true;

void	sigHandler(int signal)
{
	(void) signal;
	servidor_activo = false;
}
void bucle_principal() {
	while (servidor_activo) {
	}
}

int	main(void)
{
	signal(SIGINT, sigHandler);
	bucle_principal();
	return (0);
}