#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <psapi.h>
#include <conio.h>
#include <math.h>

#include "..\joaalmcon-LibSS\joaalmcon-LibSS.h"

double res;

int EscribeK(int NroKBytes, char* NombreArchivo);



#define TAM_BUFFER 30000 //Definimos un tamaño grande para el buffer, así no nos dará error
#define ARRAY_SIZE 1024	

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "Spanish"); // hace que printf "entienda" tildes, ñ, etc.
	
	//EJERCICIO 16
	int i;
	// Buffer length
	DWORD myDrives = 100, vDrives, nDrives;
	// Buffer for drive string storage
	char lpBuffer[100];


	nDrives = GetLogicalDriveStrings(myDrives, lpBuffer);
	vDrives = GetLogicalDrives();

	printf("Numero de drivers :%d \n", vDrives);

	//MessageBox(NULL, cadena, "Ejercicio 25", 0x00000000L);
	CheckError(GetLogicalDrives() == FALSE, "No se pudo obtener el numero de drivers", 1);

	printf("Nombre de los drivers : ");
	for (i = 0; i < 10; i++) {

		printf("%c", lpBuffer[i]);

	}
	printf("\n");


	//FIN EJERCICIO 16
	
	//EJERCICIO 14
	
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	int numCPU = sysinfo.dwNumberOfProcessors;

	printf("El numero de procesadores es: %d\n", numCPU); //Imprimimos en pantalla	

	//FIN EJERCICIO 14
	MideRetraso(0);
	EscribeK(1024 * 200, (char*)"D://Desktop//a.txt");
	Sleep(500);
	double res = MideRetraso("Retraso en segs despues de ejecutar EscribeK: ");
	printf("Velocidad de escritura del disco duro en MBytes por segundo: %.3f MB por seg.\n", ((1024 * 200) / pow(2, 10)) / res);
	//CheckError(argc != 3, "Usage: cp file1 file2\n"	"Esto se imprime y para", 1);
	//CheckError(!CopyFile(argv[1], argv[2], FALSE),"CopyFile Error", 1);
	//CheckError(FALSE, "No se imprime", 0);
	//CheckError(TRUE, "Esto se imprime y sigue...", 0);	
	//printf("Probando CheckError.Hasta aquí no llega");
	

	printf("\nPulse tecla RETORNO para terminar\n");

	getchar();



}


int EscribeK(int NroKBytes, char* NombreArchivo){

	static char Buffer[1024];

	int counter;
	FILE* ptr_myfile;
	ptr_myfile = fopen(NombreArchivo, "wb");

	if (!ptr_myfile){

		printf("Unable to open file!");
		return 1;

	}

	for (counter = 0; counter < NroKBytes; counter++)

    {
		fwrite(Buffer, sizeof(Buffer), 1, ptr_myfile);

	}
	fclose(ptr_myfile);

	return 0;

}