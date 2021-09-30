#include "proyecto.h"

void miniMenu_Eje5();
DWORD WINAPI reproduce_h_Eje5(LPVOID lpParameter);

HANDLE hReproduce_Eje5;

/*int main(int argc, char *argv[]) //Comentado para que ejecute P07_Eje8_jorcallag
{

	setlocale(LC_ALL, "Spanish"); 
	CheckError(argc != 2, "Debe haber al menos 1 argumentos (nombre archivo de la imagen)", 1);

	hReproduce_Eje5 = CreateThread(NULL, 0, reproduce_h_Eje5, argv[1], 0, NULL);
	CheckError(NULL == hReproduce_Eje5, "\n\n\ERROR al crear el hilo de reproduccionn\n", 1);

	miniMenu_Eje5();

	return 0;
}*/

extern double amplitudDistorsion;
void miniMenu_Eje5() {

	int nroCampos, cmd = 0;
	while (TRUE) {
		char ent[20] = "Ninguno";

		system("CLS");
		printf("Ultimo comando: %d\nY ahora?\n\n", cmd);
		printf("0 - Salir\n<0 - Parar/Continuar\n>0 - Modificar amplitud distorsion\n¿Nuevo comando?\n");

		nroCampos = scanf("%d", &cmd);
		if (nroCampos != 1) {
			// Corrección:
			while ('\n' != getchar());
			
			Beep(1000, 500);
			continue;
		}
		if (cmd == 0)
			ExitProcess(0); 
		else if (cmd > 0 && cmd < 100)
			amplitudDistorsion = cmd;
		else if (cmd < 0) {
			
		}
	}
}

DWORD WINAPI reproduce_h_Eje5(LPVOID lpParameter) {

	int tecla;

	IplImage* imgOriginal;
	CvCapture* g_capture = cvCreateFileCapture((char*)lpParameter); //Abre el archivo de video
	CheckError(NULL == g_capture, "\n\nERROR: No se pudo abrir el archivo de video\n\n", 1);
	imgOriginal = cvQueryFrame(g_capture); // Lee frame del archivo
	if (NULL == imgOriginal) return 0;

	IplImage* imgResultado = cvCreateImage(CvSize(imgOriginal->width, imgOriginal->height),
		imgOriginal->depth, imgOriginal->nChannels);

	double retrasoAcumulado = 0.0;
	int nroImagenes = 0;

	do
	{
		char mensaje[200];
		MideRetraso(0);
		//ProcesaImagen(imgOriginal, imgResultado);
		AGris(imgOriginal, imgResultado);
		//Sleep(100);
		retrasoAcumulado += MideRetraso(0);
		nroImagenes++;
		snprintf(mensaje, sizeof(mensaje),
			"procesando %d imagenes en %.2f segs\n(%.2f imgs/s)\nPulsa ENTER para terminar",
			nroImagenes, retrasoAcumulado, nroImagenes / retrasoAcumulado);
		ImagenAVentana(imgResultado, "RESULTADO:", mensaje, true, &tecla);
		imgOriginal = cvQueryFrame(g_capture); 
	} while (tecla != '\r' && NULL != imgOriginal);

	return 0;
}
