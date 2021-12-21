#define _CRT_SECURE_NO_WARNINGS
#include "proyecto.h"

HANDLE BloqueaHastaQueSoloHaya1() {

	HANDLE hEmpieza;
	DWORD res = 0xff;

	hEmpieza = CreateMutex(NULL, false, "NombreObjetoSinc");
	CheckError(NULL == hEmpieza, "No se pudo crear objeto de sincronizaci�n", 1);

	while (res != WAIT_OBJECT_0) {
		res = WaitForSingleObject(hEmpieza, 1000);
		if (WAIT_TIMEOUT == res)
		{
			// LLeva mucho tiempo, hay que hacer algo...
			printf("\nEsperando a que termine el programa en ejecuci�n...\n");
			continue; // Salta el resto del while
		}
		if (WAIT_ABANDONED == res) {
			// Se cerr� el mutex
			printf("\nSe cerr� el mutex..\n");
			hEmpieza = NULL; // no es un handle v�lido
			break;	// sale del while
		}
		CheckError(res != WAIT_OBJECT_0, "No funciono la espera", -1);
	}
	return hEmpieza;
}

int main(int argc, char* argv[]) {
	int i = 0;
	setlocale(LC_ALL, "Spanish");	// Indica que debe usar espa�ol como idioma por defecto

	HANDLE h = BloqueaHastaQueSoloHaya1();
	printf("\nEntra en proceso....\n");
	for (i = 0; i < 20; i++) {
		printf("Ciclo %d\n", i);
		Sleep(1000);
	}

	//Desbloquea...
	ReleaseMutex(h);
	CloseHandle(h);
	printf("\nPulse tecla RETORNO para terminar\n");
	getchar();
	return 0;
}

