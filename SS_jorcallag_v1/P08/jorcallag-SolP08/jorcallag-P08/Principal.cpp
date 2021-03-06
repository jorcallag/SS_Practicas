#include "proyecto.h"
#define NRO_HILOS 1 
#define TAM_CAD 200

typedef struct {
	HANDLE h;
	DWORD id;

	int nroHilo;
	int totalHilos;
	char tituloVentana[TAM_CAD];
	char nombreArchivo[TAM_CAD];
	HANDLE evFin;
	HANDLE evSem;
} di_reproduce_t, *pdi_reproduce_t;

double cuenta = 0.0;
HANDLE evCuenta;
pdi_reproduce_t infoThread[NRO_HILOS];

/*
int main(int argc, char *argv[]) //Comentado para que funcione el ejercicio 8.8
{

	CheckError(argc != 2, "Debe haber al menos 2 argumentos (alto y ancho de la imagen)", 1);
	setlocale(LC_ALL, "Spanish");
	
	//8.11
	evCuenta = CreateEvent(NULL, FALSE, TRUE, NULL);
	CheckError(evCuenta == NULL, "No se puedo crear el evento de cuenta", 1);

	//lanzar los hilos de reproduccion
	for (size_t i = 0; i < NRO_HILOS; i++)
	{
		pdi_reproduce_t p = new di_reproduce_t;
		p->nroHilo = i;
		p->totalHilos = NRO_HILOS;
		snprintf(p->tituloVentana, sizeof(p->tituloVentana), "Venana %d", i);
		strncpy(p->nombreArchivo, "P01Eje1.mp4", sizeof(p->nombreArchivo));

		//Creacion de objeto de sincronizacion

		//Eventos
		//p->evFin = CreateEvent(NULL, TRUE, false, NULL);
		//CheckError(p->evFin == NULL, "No se pudo crear el evento", 1);

		//Semaforos
		p->evSem = CreateSemaphore(NULL, 0, 1, NULL); 
		CheckError(p->evSem == NULL, "No se pudo crear el semaforo", 1);

		p->h = CreateThread(NULL, 0, Reproduce, p, 0, &p->id);
		CheckError(NULL == p->h, "ERROR al crear el hilo", 1);
		// guardar el valor de p?
		infoThread[i] = p;
	}

	//8.11
	while (TRUE)
	{
		WaitForSingleObject(evCuenta, INFINITE);
		printf("%.2f\n", cuenta);
		//ResetEvent(evCuenta);
	}
	//miniMenu();

	return 0;
}
*/

DWORD WINAPI Reproduce(LPVOID par)
{
	pdi_reproduce_t pdi = (pdi_reproduce_t)par;

	int tecla;
	IplImage* imgOriginal;

	CvCapture* g_capture = cvCreateFileCapture(pdi-> nombreArchivo);
	CheckError(NULL == g_capture, "ERROR: No se pudo abrir el archivo de video\n\n", 1);
	imgOriginal = cvQueryFrame(g_capture);
	CheckError(NULL == imgOriginal, "ERROR: No se pudo leer el primer frame\n\n", 2);

	double retrasoAcumulado = 0.0;
	int nroImagenes = 0;
	int segundos = 0;

	do
	{
		char mensaje[200];
		imgOriginal = cvQueryFrame(g_capture);
		if (imgOriginal == NULL) break;
		double ahora = cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC) / 1000;
		if (retrasoAcumulado < ahora) Sleep((DWORD)((ahora - retrasoAcumulado) * 1000));
		retrasoAcumulado = ahora;
		nroImagenes++;
		snprintf(mensaje, sizeof(mensaje),
			"jorcallag %.2f segs\nPulsa ENTER para terminar",
			ahora);
		cuenta = ahora;
		if ((int)ahora != segundos) SetEvent(evCuenta);
		segundos = (int)ahora;
		ImagenAVentana(imgOriginal, pdi-> tituloVentana, mensaje, true, &tecla);

		//Activar o desactivar objeto de sincronizacion

		//Eventos
		//DWORD res = WaitForSingleObject(pdi->evFin, 0);
		//if (WAIT_OBJECT_0 == res) break;

		//Semaforos
		DWORD res = WaitForSingleObject(pdi->evSem, 0);
		if (WAIT_OBJECT_0 == res) break;
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
		printf("<0 - Salir\n<0 - %d Cerrar ventana i\n?Nuevo comando?\n", NRO_HILOS-1);
		nroCampos = scanf("%d", &cmd); // Ojo, esto fall cuando no le pasamos una entrada correcta // Ver c?mo se corrige en clase usando gets_s y sscanf
		if (nroCampos != 1) 
		{
			while ('\n' != getchar());
			Beep(1000, 500);
			continue;
		}
		if (cmd < 0)
		{
			ExitProcess(0); // Termina el programa
		}
		else if (cmd >= 0 && cmd < NRO_HILOS)
		{
			//TerminateThread(infoThread[cmd]-> h, 0);

			//Indicar accion de objeto de sincronizacion

			//Eventos
			//CheckError(FALSE==SetEvent(infoThread[cmd]-> evFin), "No se pudo activar evento de terminacion", 1);
			//WaitForSingleObject(infoThread[cmd]->h, INFINITE);

			//Semaforos
			CheckError(FALSE == ReleaseSemaphore(infoThread[cmd]->evSem, 1, NULL), "No se pudo activar semaforo de terminacion", 1);
			WaitForSingleObject(infoThread[cmd]->h, INFINITE);
		}
	}
}