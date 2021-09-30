#include "jorcallag-LibSS\jorcallag-LibSS.h"

#define BUFSIZE MAX_PATH

int EscribeK(int NroKBytes, char* NombreArchivo);
 
int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "Spanish");

	//Ejercicio 18
	TCHAR Buffer[BUFSIZE];

	GetCurrentDirectory(BUFSIZE, Buffer);

	printf("El directorio de trabajo actual es: %s", Buffer);
	//Fin ejercicio 18

	//Ejercicio 20
	TCHAR RootPathName[200] = "C: \"";
	TCHAR VolumeNameBuffer[200];
	DWORD VolumeSerialNumber;
	DWORD MaximumComponentLength;
	DWORD FileSystemFlags;
	TCHAR FileSystemNameBuffer[200] = "";

	BOOL GetVolumeInformationA(
		RootPathName,
		VolumeNameBuffer,
		sizeof(VolumeNameBuffer),
		&VolumeSerialNumber,
		&MaximumComponentLength,
		&FileSystemFlags,
		FileSystemNameBuffer,
		sizeof(FileSystemNameBuffer)
	);

	printf("%s", RootPathName);
	//Fin ejercicio 20	

	//EscribeK(1024 * 200, (char*)"C://Users//Jorlu//Desktop//WS//SS//PruebaP5.txt");
	//double segs = MideRetraso("Retraso en segs despues de ejecutar EscribeK: ");
	//printf("Velocidad de escritura del disco duro: %f MB por seg.\n", (((float)1024 * 200) / pow(2, 10)) / segs);

	//CheckError(FALSE, "Primera llamada: no muestra nada", 0);
	//CheckError(TRUE, "Segunda llamada: muestra error y sigue", 0);
	//CheckError(TRUE, "Tercera llamada: muestra error y para", 1);

	printf("\nPulse la tecla RETORNO para terminar\n");
	getchar();
	return 0;

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
	for (counter = 0; counter < NroKBytes; counter++){
		fwrite(Buffer, sizeof(Buffer), 1, ptr_myfile);
	}
	fclose(ptr_myfile);
	return 0;

}
