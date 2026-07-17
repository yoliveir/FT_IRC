#include "signal.hpp"

volatile unsigned int	g_signal = 0;

void	signalHandler(int signal)
{
	g_signal = signal;
}