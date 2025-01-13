#include <csignal>
#include <string.h>

void	handleSigInt(int sig) {
	(void) sig;
}

void	handleSigQuit(int sig) {
	(void) sig;
}

void	handleSigPipe(int sig) {
	(void) sig;
}

void	signalHandler() {
	struct sigaction saInt;

	memset(&saInt, 0, sizeof(saInt));
	saInt.sa_handler = handleSigInt;
	sigaction(SIGINT, &saInt, NULL);

	struct sigaction saQuit;

	memset(&saInt, 0, sizeof(saQuit));
	saQuit.sa_handler = handleSigQuit;
	sigaction(SIGINT, &saQuit, NULL);

	struct sigaction saPipe;

	memset(&saPipe, 0, sizeof(saPipe));
	saPipe.sa_handler = handleSigPipe;
	sigaction(SIGINT, &saPipe, NULL);

}