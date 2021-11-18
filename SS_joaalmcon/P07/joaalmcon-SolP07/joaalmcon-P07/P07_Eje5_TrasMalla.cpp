#include "proyecto.h"
#define NRO_HILOS 4
//Solo tenemos que cambiar el nº de hilos (1 a 20) , por ejemplo usamos 8

//definimos el tipo 
typedef struct {
	IplImage* imgO;
	IplImage* imgR;
	int nroHilos;
	int totalHilos;

	HANDLE h;
	DWORD id;

} di_TrasMalla_t, *pdi_TrasMalla_t;


// comprueba que los límites de una coordenada x o y no pasen de los valores máximo y mínimo
static int CompruebaLimitesXoY(double valor, int limite)
{
	if (valor >= limite)
		valor = limite - 1;
	else
		if (valor < 0)
			valor = 0;
	return (int)valor;
}

//añadimos extern para tomar el valor de la clase Principal
extern double amplitudDistorsion;

//Añadimos la informacion de los hilos al puntero definido
pdi_TrasMalla_t threadInfo[NRO_HILOS];

// Crea un efecto de malla sobre la imagen
DWORD WINAPI TrasMalla(LPVOID punteroGenerico)
//void TrasMalla(IplImage* imgO, IplImage* imgR, double sinUso1, double sinUso2)
{
	pdi_TrasMalla_t pdi = (pdi_TrasMalla_t)punteroGenerico;
	IplImage* imgO = pdi->imgO;
	IplImage* imgR = pdi->imgR;

	int bytesXpixel = imgO->nChannels;
	for (int y = pdi->nroHilos; y < imgO->height; y+=pdi->totalHilos) { // Recorre scanlines
		for (int x = 0; x < imgO->width; x++) {
			/* Calcula pixeles de origen y de destino,
					imageData apunta al inicio de la imagen.
						   y* widthStep  es la distancia hasta el inicio del scanline y
						   x* nChannels es la distancia desde el inicio del scanline
								hasta la columna x.
			*/
			// Dirección del pixel de origen
			unsigned char* pO = (unsigned char*)&imgO->imageData[y * imgO->widthStep + x * bytesXpixel];
			// Dirección del pixel de destino
			// Cambia x e y en destino para distorsionar la imagen
			int dy = CompruebaLimitesXoY(y + amplitudDistorsion * sin(x), imgO->height);
			int dx = CompruebaLimitesXoY(x + amplitudDistorsion * cos(y), imgO->width);

			unsigned char* pD = (unsigned char*)&imgR->imageData[dy * imgR->widthStep + dx * bytesXpixel];
			*(PRGBTRIPLE)pD = *(PRGBTRIPLE)pO;
		}
	}
	return 0;
}

//Realizamos una nueva funcion que invoque a la anterior con los datos que le pasamos por parametro.

void TrasMalla_2x(IplImage * imgO, IplImage * imgR)
{
	for (size_t i = 0; i < NRO_HILOS; i++)
	{
		threadInfo[i] = new di_TrasMalla_t; //crear bloque de datos en memoria.
		threadInfo[i]->imgO = imgO;
		threadInfo[i]->imgR = imgR;
		threadInfo[i]->totalHilos = NRO_HILOS;
		threadInfo[i]->nroHilos = i;
		threadInfo[i]->h = CreateThread(NULL, 0, TrasMalla, threadInfo[i], 0, &threadInfo[i]->id);
		//TrasMalla(imgO, imgR, 0.0, 0.0);
	}

	for (size_t i = 0; i < NRO_HILOS; i++)
	{
		DWORD res = WaitForSingleObject(threadInfo[i]-> h, INFINITE);
		CheckError(WAIT_OBJECT_0 != res, "Error esperando a que el hilo se termine", 1);
		delete threadInfo[i];
	}
}
