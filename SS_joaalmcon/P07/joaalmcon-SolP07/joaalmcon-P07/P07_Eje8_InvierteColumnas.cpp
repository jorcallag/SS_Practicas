#include "proyecto.h"
#define NRO_HILOS 8

typedef struct {
	IplImage* imgO;
	IplImage* imgD;
	int nroHilos;
	int totalHilos;

	HANDLE h;
	DWORD id;

} di_InvierteColumnas_t, * pdi_InvierteColumnas_t;

extern int anchoColumnas;

pdi_InvierteColumnas_t threadInfo[NRO_HILOS];

DWORD WINAPI InvierteColumnas(LPVOID punteroGenerico)
//void InvierteColumnas(IplImage * imgO, IplImage * imgD)
{
	BOOL alterar;
	pdi_InvierteColumnas_t pdi = (pdi_InvierteColumnas_t)punteroGenerico;
	IplImage* imgO = pdi->imgO;
	IplImage* imgD = pdi->imgD;

	// Recorre filas y columnas de la matriz de píxeles. 
	for (int y = pdi->nroHilos; y < imgO->height; y += pdi->totalHilos) { // Recorre scanlines y reparte a cada hilo

		for (int x = 0; x < imgO->width; x++) {
			// Invierte el valor de X en el pixel de destino
			unsigned char * pO = (unsigned char *)&imgO->imageData[y*imgO->widthStep + x * imgO->nChannels];
			unsigned char * pD = (unsigned char *)&imgD->imageData[y*imgD->widthStep + (imgO->width - x - 1)*imgD->nChannels];
			// Copia pixel de origen a pixel de destino.
			memcpy(pD, pO, anchoColumnas);		//ERROR: Cambio ImgSize por anchoColumnas = 100
												//Si ponemos en el "4" invertimos totalmente la imagen.(Por que tenemos del 1 al 3 RGB colors)
															
		}  // Fin proceso de columnas
	}  // Fin proceso de filas
	return 0;
}

void InvierteColumnas_2x(IplImage* imgO, IplImage* imgD)
{
	for (size_t i = 0; i < NRO_HILOS; i++)
	{
		threadInfo[i] = new di_InvierteColumnas_t; //crear bloque de datos en memoria.
		threadInfo[i]->imgO = imgO;
		threadInfo[i]->imgD = imgD;
		threadInfo[i]->totalHilos = NRO_HILOS;
		threadInfo[i]->nroHilos = i;
		threadInfo[i]->h = CreateThread(NULL, 0, InvierteColumnas, threadInfo[i], 0, &threadInfo[i]->id);
		//InvierteColumnas(imgO, imgD);
	}

	for (size_t i = 0; i < NRO_HILOS; i++)
	{
		DWORD res = WaitForSingleObject(threadInfo[i] -> h, INFINITE);
		CheckError(WAIT_OBJECT_0 != res, "Error esperando a que el hilo se termine", 1);
		delete threadInfo[i];
	}
}







