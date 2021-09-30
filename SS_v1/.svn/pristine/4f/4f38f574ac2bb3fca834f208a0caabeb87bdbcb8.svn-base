#include "proyecto.h"
// poner aquí todos los archivos de includes adicionales necesarios

#define NRO_HILOS 2

typedef struct {
	HANDLE h;
	DWORD id;

	IplImage* imgO;
	IplImage* imgR;
	int nroHilo;
	int totalHilos;
} di_trasMalla_t, *pdi_trasMalla_t;

//di_trasMalla_t infoHilos[NRO_HILOS];
pdi_trasMalla_t pInfoHilos[NRO_HILOS];

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

double amplitudDistorsion = 2.0;
// Crea un efecto de malla sobre la imagen
void TrasMalla(IplImage* imgO, IplImage* imgR, double sinUso1, double sinUso2)
{

	int bytesXpixel = imgO->nChannels;
	for (int y = 0; y < imgO->height; y++) { // Recorre scanlines
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
}

// Ejercicio 7.7
void TrasMalla_2x(IplImage* imgO, IplImage* imgR) {

	//Creo 2 hilos
	for (size_t i = 0; i < NRO_HILOS; i++) {
		pInfoHilos[i] = new di_trasMalla_t; // reserva memoria
		pInfoHilos[i]-> imgO = imgO;
		pInfoHilos[i]-> imgR = imgR;
		pInfoHilos[i]-> nroHilo = i;
		pInfoHilos[i]-> totalHilos = NRO_HILOS; // relleno info para el hilo

		pInfoHilos[i]-> h = CreateThread(NULL, 0, TrasMalla_h, pInfoHilos[i], 0, &pInfoHilos[i]-> id);
		CheckError(NULL == pInfoHilos[i]->h, "ERROR al crear el hilo TrasMalla_h", 1);
	}
	
	//Espero a que terminen
	for (size_t i = 0; i < NRO_HILOS; i++) {
		DWORD res = WaitForSingleObject(pInfoHilos[i]->h, INFINITE);
		CheckError(WAIT_OBJECT_0 != res, "ERROR al bloquear esperando fin de hilo", 1);
		delete pInfoHilos[i];
	}
}

DWORD WINAPI TrasMalla_h(LPVOID parametroVoid) {

	IplImage* imgO, * imgR;
	pdi_trasMalla_t p = (pdi_trasMalla_t) parametroVoid;
	imgO = p->imgO;
	imgR = p->imgR;

	int bytesXpixel = imgO->nChannels;
	for (int y = p->nroHilo; y < imgO->height; y+=p->totalHilos) { // Recorre scanlines
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
