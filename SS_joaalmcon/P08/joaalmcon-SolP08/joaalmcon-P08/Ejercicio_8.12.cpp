
#include "Proyecto.h"

DWORD WINAPI Reproduce(_In_ LPVOID lpParameter);

void miniMenu();

#define NRO_VENTANAS 2
#define TAM_CAD 200


typedef struct
{
	HANDLE h;
	DWORD id;
	int nroHilos;
	int totalHilos;
	char nombreArchivo[TAM_CAD];
	char nombreVentana[TAM_CAD];
	double segundos;

	HANDLE evFin;


} di_reproduce_t, * pdi_reproduce_t;

pdi_reproduce_t infoHilos[NRO_VENTANAS];

double mSecsTotal = 0.0;


HANDLE evCuenta;

int main(int argc, char* argv[])
{	
	
	CheckError(argc != 2, "Debe haber al menos 2 argumento (alto y ancho de la imagen)", 1);
	setlocale(LC_ALL, "Spanish");

	evCuenta = CreateEvent(NULL, FALSE, TRUE, NULL);
	CheckError(NULL == evCuenta, "No se pudo crear el evento de cuenta", 1);


	for (size_t i = 0; i < NRO_VENTANAS; i++)
	{
		pdi_reproduce_t p = new di_reproduce_t;
		p->nroHilos = i;
		p->totalHilos = NRO_VENTANAS;
		

		strncpy(p->nombreArchivo, argv[1], sizeof(p->nombreArchivo));
		snprintf(p->nombreVentana, sizeof(p->nombreVentana) , "Ventana %d", i);
		p->evFin = CreateEvent(NULL, TRUE, FALSE, NULL);
		CheckError(NULL == p->evFin, "No se pudo crear el evento de terminación", 1);
		
		p->h = CreateThread(NULL, 0, Reproduce, p, 0, NULL);
		CheckError(NULL == p->h, "Error al crear el hilo de reproducción", 1);
		infoHilos[i] = p;
		
	}
	

	while (TRUE)
	{
		DWORD res1 = WaitForSingleObject(evCuenta, INFINITE);
		CheckError(0 != res1, "Error al bloquear mostrar cuenta", 1);
		printf("%4.f\n", mSecsTotal*1000);

	}
	//miniMenu();
	return 0;
}

DWORD WINAPI Reproduce(_In_ LPVOID lpParameter) {

	pdi_reproduce_t pdi = (pdi_reproduce_t)lpParameter;
	int tecla;	// permite leer las teclas que pulsa el usuario en las ventanas openCV
	char* nombreVentana;

	// comprueba que el usuario ha puesto el ancho y alto de la imagen en línea de comandos

	setlocale(LC_ALL, "Spanish"); 

	IplImage* imgOriginal;

	CvCapture* g_capture = cvCreateFileCapture(pdi->nombreArchivo);

	// Para la imagen original usamos un patrón conocido

	CheckError(NULL == g_capture, "\n\nERROR: No se pudo abrir el archivo de video \n\n", 1);

	imgOriginal = cvQueryFrame(g_capture); //Lee el frame del archivo

	CheckError(NULL == imgOriginal, "\n\nERROR: No se pudo leer el primer frame \n\n", 1);

								
	double retrasoAcumulado = 0.0; // permite calcular la velocidad de proceso de las imágenes
	int nroImagenes = 0;
	
	do
	{
		char mensaje[200];

		imgOriginal = cvQueryFrame(g_capture);

		if (imgOriginal == NULL)
			break;
		double ahora = cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC) / 1000;
		pdi->segundos = ahora;

		mSecsTotal = pdi->segundos + pdi->totalHilos;
				
		if (mSecsTotal*1000 == 5000) 
			SetEvent(evCuenta);
			

		if (retrasoAcumulado < ahora)

			Sleep((DWORD)((ahora - retrasoAcumulado) * 1000));
		retrasoAcumulado = ahora;
		nroImagenes++;
		// Construimos el mensaje
		snprintf(mensaje, sizeof(mensaje), "Joaalmcon - %3.3f segs \nPulsa ENTER para terminar", ahora);

		ImagenAVentana(imgOriginal, pdi->nombreVentana, mensaje, true, &tecla);
		DWORD res =	WaitForSingleObject(pdi->evFin, 0);
		if (WAIT_OBJECT_0 == res)
			break;

	} while (tecla != '\r');
	cvReleaseCapture(&g_capture);
	return 0;
}


void miniMenu() {

	int nroCampos, cmd = 0;

	while (TRUE) {

		char ent[20] = "Ninguno";

		system("CLS"); // Ejecuta el comando CLS (clear screen) en el shell

		printf("Ultimo comando: %d\nY ahora?\n\n", cmd);

		printf("<0 - Salir\n0 - %d - Cerrar ventana i\n¿Nuevo comando?\n", NRO_VENTANAS-1);

		nroCampos = scanf("%d", &cmd); // Ojo, esto fall cuando no le pasamos una entrada correcta // Ver cómo se corrige en clase usando gets_s y sscanf

		if (nroCampos != 1) {

			// Corrección:

			while ('\n' != getchar());// vacía el buffer de entrada.

			// Si scanf tiene un error al convertir la entrada, no la "consume"

			Beep(1000, 500); // Avisa que ha habido un error

			continue;

		}

		if (cmd < 0)

			ExitProcess(0); // Termina el programa

		else if (cmd >= 0 && cmd < NRO_VENTANAS) {
			SetEvent(infoHilos[cmd]->evFin);

			WaitForSingleObject(infoHilos[cmd]->h, INFINITE);

			CheckError(NULL == infoHilos[cmd]->h, "No se pudo crear el evento de terminación", 1);
		}

	}

}

