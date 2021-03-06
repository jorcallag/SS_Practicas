#include "proyecto.h"
// poner aqu? todos los archivos de includes adicionales necesarios

void miniMenu();
DWORD WINAPI reproduce_h(LPVOID lpParameter);

HANDLE hReproduce;

//Comentado para que ejecute Ejercicio 7.2
/*int main(int argc, char *argv[])
{
	int tecla;	// permite leer las teclas que pulsa el usuario en las ventanas openCV
	char * nombreVentana;

	// comprueba que el usuario ha puesto el ancho y alto de la imagen en l?nea de comandos
	CheckError(argc != 3, "Debe haber al menos 2 argumentos (alto y ancho de la imagen)", 1);

	setlocale(LC_ALL, "Spanish"); // Previo

	// Para la imagen original usamos un patr?n conocido
	IplImage * imgOriginal = GeneraBMP24cv(atoi(argv[1]), atoi(argv[2]), Patron_10);
	do
	{
		// Muestra la imagen original en una ventana OpenCv hasta que el usuario pulsa una tecla
		nombreVentana = ImagenAVentana(imgOriginal, "Original", "Pulsa una tecla\npara continuar...", false, &tecla);
	} while (tecla == -1);

	//printf("Cerrando primera ventana..."); // <-- descomentar para ejercicio 6.2 
	cvDestroyWindow(nombreVentana);	// cierra la primera ventana
	// crea imagen de resultado
	IplImage* imgResultado = cvCreateImage(CvSize(imgOriginal->width, imgOriginal->height),
		imgOriginal->depth, imgOriginal->nChannels);

	double retrasoAcumulado = 0.0; // permite calcular la velocidad de proceso de las im?genes
	int nroImagenes = 0;
	do
	{
		char mensaje[200];
		MideRetraso(0);	//<-- Solo medimos el tiempo de proceso de la imagen. Desde aqu?
		//ProcesaImagen(imgOriginal, imgResultado);
		//AGris(imgOriginal, imgResultado); //<-- Ejercicio 6.8
		TrasMalla(imgOriginal, imgResultado, 0.0, 0.0); //<-- Ejercicio 7.1
		//Sleep(100);
		retrasoAcumulado += MideRetraso(0);	// --> hasta aqu?
		nroImagenes++;
		// Construimos el mensaje
		snprintf(mensaje, sizeof(mensaje),
			"procesando %d imagenes en %.2f segs\n(%.2f imgs/s)\nPulsa ENTER para terminar",
			nroImagenes, retrasoAcumulado, nroImagenes / retrasoAcumulado);
		// Muestra el resultado
		ImagenAVentana(imgResultado, "RESULTADO:", mensaje, true, &tecla);
	} while (tecla != 13);	// salimos cuando el usuario pulsa la tecla Retorno

	return 0;
}*/

// Ejercicio 7.2 //Comentado para que ejecute P07_Eje5_jorcallag //Descomentar para ejercicio 7.7 //Comentado para que ejecute P07_Eje8_jorcallag
/*int main(int argc, char *argv[])
{

	setlocale(LC_ALL, "Spanish"); // Previo
	CheckError(argc != 2, "Debe haber al menos 1 argumentos (nombre archivo de la imagen)", 1);
	
	
	//miniMenu(); //<-- Ejercicio 7.4
	//1- Lanzar hilo con miniMenu
	//2- Lanzo hilo antes de llamar a miniMenu <---
	
	//Crear el hilo
	
	hReproduce = CreateThread(NULL, 0, reproduce_h, argv[1], 0, NULL);
	CheckError(NULL == hReproduce, "\n\n\ERROR al crear el hilo de reproduccionn\n", 1);

	miniMenu();

	return 0;
}*/

// Ejercicio 7.4
extern double amplitudDistorsion;
void miniMenu() {
	
	int nroCampos, cmd = 0;
	while (TRUE) {
		char ent[20] = "Ninguno";

		system("CLS"); // Ejecuta el comando CLS (clear screen) en el shell
		printf("Ultimo comando: %d\nY ahora?\n\n", cmd);
		printf("0 - Salir\n<0 - Parar/Continuar\n>0 - Modificar amplitud distorsion\n?Nuevo comando?\n");

		nroCampos = scanf("%d", &cmd); // Ojo, esto fall cuando no le pasamos una entrada correcta // Ver c?mo se corrige en clase usando gets_s y sscanf
		if (nroCampos != 1) {
			// Correcci?n:
			while ('\n' != getchar());// vac?a el buffer de entrada.
			// Si scanf tiene un error al convertir la entrada, no la "consume"

			Beep(1000, 500); // Avisa que ha habido un error
			continue;
		}
		if (cmd == 0)
			ExitProcess(0); // Termina el programa
		else if (cmd > 0 && cmd < 100)
			amplitudDistorsion = cmd;
		else if (cmd < 0) {
			// Suspender o rearrancar el hilo
		}
	}
}

DWORD WINAPI reproduce_h(LPVOID lpParameter) {

	int tecla;

	IplImage* imgOriginal;
	CvCapture* g_capture = cvCreateFileCapture((char *) lpParameter); //Abre el archivo de video
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
		MideRetraso(0);	//<-- Solo medimos el tiempo de proceso de la imagen. Desde aqu?
		//ProcesaImagen(imgOriginal, imgResultado);
		//AGris(imgOriginal, imgResultado);
		//TrasMalla(imgOriginal, imgResultado, 0.0, 0.0); //<-- Ejercicio 7.1
		TrasMalla_2x(imgOriginal, imgResultado); //<-- Ejercicio 7.7
		//Sleep(100);
		retrasoAcumulado += MideRetraso(0);	// --> hasta aqu?
		nroImagenes++;
		// Construimos el mensaje
		snprintf(mensaje, sizeof(mensaje),
			"procesando %d imagenes en %.2f segs\n(%.2f imgs/s)\nPulsa ENTER para terminar",
			nroImagenes, retrasoAcumulado, nroImagenes / retrasoAcumulado);
		// Muestra el resultado
		ImagenAVentana(imgResultado, "RESULTADO:", mensaje, true, &tecla);
		imgOriginal = cvQueryFrame(g_capture); // Lee frame del archivo
	} while (tecla != '\r' && NULL != imgOriginal);

	return 0;
}
