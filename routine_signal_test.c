#include <signal.h>
#include <stdio.h>

int main() {
	sigset_t mask;
	sigemptyset(&mask);
	printf("mask == %lu\n", *(unsigned long*)&mask);
	printf("SIGCHLD == %d\n", SIGCHLD);
	sigaddset(&mask, SIGCHLD);
	printf("mask == %lu\n", *(unsigned long *)&mask);
}
