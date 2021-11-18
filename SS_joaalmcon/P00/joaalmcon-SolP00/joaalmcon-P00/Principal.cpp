#include <stdio.h>
#include <conio.h>
#include <locale.h>

int main(int argc, char* argv[], char* envp[])
{
	setlocale(LC_ALL, "Spanish");
	printf("\nArgumentos del programa");
	for (int j = 0; j < argc; j++) {
		printf("%s\n", argv[j]);
	}
	printf("\nVariables del entorno del sistema");
	for (int i = 0; envp[i] != 0; i++){
		printf("%s\n", envp[i]);	
	}

	printf("\nPor favor, pulse una tecla para terminar ...");
	_getch();
	return 0;
}