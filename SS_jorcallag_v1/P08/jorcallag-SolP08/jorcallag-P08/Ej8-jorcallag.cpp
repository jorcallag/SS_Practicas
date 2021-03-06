#include "proyecto.h"
#define NRO_HILOS 2
#define TAM_CAD 200

typedef struct {
	HANDLE h;
	DWORD id;

	int nroHilo;
	int totalHilos;
	char tituloVentana[TAM_CAD];
	char nombreArchivo[TAM_CAD];
	double sec;
	HANDLE evMut;
} di_reproduce_t_12, * pdi_reproduce_t_12;

double mSecsTotal_8 = 0.0;
pdi_reproduce_t_12 infoThread_8[NRO_HILOS];

/*int main(int argc, char* argv[]) //Comentado para que funcione ejercicio 8.12
{
	double aux = 0.0;

	CheckError(argc != 2, "Debe haber al menos 2 argumentos (alto y ancho de la imagen)", 1);
	setlocale(LC_ALL, "Spanish");

	for (size_t i = 0; i < NRO_HILOS; i++)
	{
		pdi_reproduce_t_12 p = new di_reproduce_t_12;
		p->nroHilo = i;
		p->totalHilos = NRO_HILOS;
		snprintf(p->tituloVentana, sizeof(p->tituloVentana), "Ventana %d", i);
		strncpy(p->nombreArchivo, "P01Eje1.mp4", sizeof(p->nombreArchivo));

		p->evMut = CreateMutex(NULL, 1, NULL);
		CheckError(p->evMut == NULL, "No se pudo crear el mutex", 1);

		p->h = CreateThread(NULL, 0, Reproduce_8, p, 0, &p->id);
		CheckError(NULL == p->h, "ERROR al crear el hilo", 1);
		infoThread_8[i] = p;

	}

	while (TRUE)
	{
		for (size_t i = 0; i < NRO_HILOS; i++)
		{
			aux = aux + infoThread_8[i]->sec;
		}
		mSecsTotal_8 = aux;
		aux = 0.0;
		printf("%.2f\n", mSecsTotal_8);
		Sleep(1000);
	}
	//miniMenu();

	return 0;
}*/

DWORD WINAPI Reproduce_8(LPVOID par)
{
	pdi_reproduce_t_12 pdi = (pdi_reproduce_t_12)par;

	int tecla;
	IplImage* imgOriginal;

	CvCapture* g_capture = cvCreateFileCapture(pdi->nombreArchivo);
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
		segundos = (int)ahora;
		pdi-> sec = ahora*1000;

		ImagenAVentana(imgOriginal, pdi->tituloVentana, mensaje, true, &tecla);

		DWORD res = WaitForSingleObject(pdi->evMut, 0);
		if (WAIT_OBJECT_0 == res) break;

	} while (tecla != '\r');
	cvReleaseCapture(&g_capture);
	return 0;
}

void miniMenu_8() {

	int nroCampos, cmd = 0;

	while (TRUE) {
		char ent[20] = "Ninguno";
		system("CLS");
		printf("Ultimo comando: %d\nY ahora?\n\n", cmd);
		printf("<0 - Salir\n<0 - %d Cerrar ventana i\n?Nuevo comando?\n", NRO_HILOS - 1);
		nroCampos = scanf("%d", &cmd);
		if (nroCampos != 1)
		{
			while ('\n' != getchar());
			Beep(1000, 500);
			continue;
		}
		if (cmd < 0)
		{
			ExitProcess(0);
		}
		else if (cmd >= 0 && cmd < NRO_HILOS)
		{
			CheckError(FALSE == ReleaseMutex(infoThread_8[cmd]->evMut), "No se pudo activar mutex de terminacion", 1);
			WaitForSingleObject(infoThread_8[cmd]->h, INFINITE);
		}
	}
}