#include "proyecto.h"
// poner aquí todos los archivos de includes adicionales necesarios

double amplitudDistorsion = 2.0;
int anchoColumnas = 100;

DWORD WINAPI miniMenu(_In_ LPVOID lpParameter);
HANDLE hHiloPrincipal;

int main(int argc, char *argv[])
{
	int tecla;	// permite leer las teclas que pulsa el usuario en las ventanas openCV
	char * nombreVentana;

	// comprueba que el usuario ha puesto el ancho y alto de la imagen en línea de comandos
	CheckError(argc != 2, "Debe haber al menos 1 argumento (nombre del archivo de la imagen)", 1);

	setlocale(LC_ALL, "Spanish"); // Previo
	CvCapture* g_capture = NULL; //Para gestionar la captura de video
	g_capture = cvCreateFileCapture(argv[1]); // Abre el archivo de video
	// Para la imagen original usamos un patrón conocido
		
	CheckError(NULL == g_capture ,"\n\nERROR: No se pudo abrir el archivo de video \n\n", 1);
	
	IplImage* imgOriginal = cvQueryFrame(g_capture); //Lee el frame del archivo
	
	
	if (imgOriginal == NULL) {
		return 0;
	}
	IplImage * imgResultado = cvCreateImage(CvSize(imgOriginal->width, imgOriginal->height),
		imgOriginal->depth, imgOriginal->nChannels);											//nChannel y depth estan intercambiados dando
																					//error por el tamaño de la imagen creada

	double retrasoAcumulado = 0.0; // permite calcular la velocidad de proceso de las imágenes
	int nroImagenes = 0;
	
	hHiloPrincipal = GetCurrentThread();
	DuplicateHandle(GetCurrentProcess(),hHiloPrincipal, GetCurrentProcess(), &hHiloPrincipal, 0, FALSE, DUPLICATE_SAME_ACCESS);
	HANDLE hminiMenu = CreateThread(NULL, 0, miniMenu, 0, 0, NULL);
	CheckError(NULL == hminiMenu, "No se pudo crear el hilo de miniMenu", 1);
	do
	{
		char mensaje[200];
		MideRetraso(0);	//<-- Solo medimos el tiempo de proceso de la imagen. Desde aquí
		
		//TrasMalla(imgOriginal, imgResultado, 0.0, 0.0);
		//TrasMalla_2x(imgOriginal, imgResultado);
		//InvierteColumnas(imgOriginal, imgResultado);
		InvierteColumnas_2x(imgOriginal, imgResultado);
		//Sleep(100);
		retrasoAcumulado += MideRetraso(0);	// --> hasta aquí
		nroImagenes++;

		snprintf(mensaje, sizeof(mensaje),														//ERROR detectado %s en vez de %d para el 
			"procesando %d imagenes en %3.3f segs \n (%3.3f imgs/s) \n Pulsa ENTER para terminar",	//oarametro nroImagenes
			nroImagenes, retrasoAcumulado, nroImagenes / retrasoAcumulado);
		
		ImagenAVentana(imgResultado, (char*)"RESULTADO:", mensaje, true, &tecla);
		
		IplImage* imgOriginal = cvQueryFrame(g_capture);

	} while (tecla != '\r' && imgOriginal != NULL);	// salimos cuando el usuario pulsa la tecla Retorno

	return 0;
}

DWORD WINAPI miniMenu(_In_ LPVOID lpParameter) {

	bool flag = true;
	int nroCampos, cmd = 0;

	while (TRUE) {

		char ent[20] = "Ninguno";

		system("CLS"); // Ejecuta el comando CLS (clear screen) en el shell

		printf("Ultimo comando: %d\nY ahora?\n\n", cmd);

		printf("0 - Salir\n<0 - Parar/Continuar\n>0 - Modificar amplitud distorsion\n¿Nuevo comando?\n");

		nroCampos = scanf("%d", &cmd); // Ojo, esto fall cuando no le pasamos una entrada correcta // Ver cómo se corrige en clase usando gets_s y sscanf

		if (nroCampos != 1) {

			// Corrección:

			while ('\n' != getchar());// vacía el buffer de entrada.

			// Si scanf tiene un error al convertir la entrada, no la "consume"

			Beep(1000, 500); // Avisa que ha habido un error

			continue;

		}

		if (cmd == 0)

			ExitProcess(0); // Termina el programa

		else if (cmd > 0 && cmd < 641)

			amplitudDistorsion = cmd;
			//anchoColumnas = cmd;

		else if (cmd < 0) {
			if (flag) {
				flag = false;
				SuspendThread(hHiloPrincipal);
			}else{
				ResumeThread(hHiloPrincipal);
				flag = true;
			
			}
		}

	}
}