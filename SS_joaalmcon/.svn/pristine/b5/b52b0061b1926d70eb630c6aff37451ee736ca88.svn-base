#include <stdio.h>

void upper_string(char[]);

char cad[40] = "cadena Ejemplo ASCII";

int main()

{

	printf("\nCadena original: %s\n", cad);

	upper_string(cad);

	printf("\nCadena resultado: %s\n", cad);

	printf("\nPor favor, pulse una tecla para terminar ...");
	getchar();
	
	return 0;

}

// Copiado de http://www.programmingsimplified.com/c/program/c-program-change-case

void upper_string(char s[]) {

	int c = 0;

	while (s[c] != '\0') {

		if (s[c] >= 'a' && s[c] <= 'z') {

			s[c] = s[c] - 32;

		}

		c++;

	}

}