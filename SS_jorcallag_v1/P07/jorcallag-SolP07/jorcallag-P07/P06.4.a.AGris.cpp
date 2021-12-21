#include "proyecto.h"
// poner aquí todos los archivos de includes adicionales necesarios

#define NRO_HILOS 1

typedef struct {
	HANDLE h;
	DWORD id;

	IplImage* imgO;
	IplImage* imgR;
	int nroHilo;
	int totalHilos;
} di_aGris_t, * pdi_aGris_t;

pdi_aGris_t pInfoHilos[NRO_HILOS];

extern double amplitudDistorsion;

void AGris(IplImage * img, IplImage * imgSal)
{
	DWORD y, x;

	for (y = 0; y < img->height; y++)
	{
		// Procesa pixels dentro de cada scanline
		for (x = 0; x < img->width; x++)
		{

			unsigned char * ppix, *ppox;

			// Calcula la dirección del pixel actual
			//imageData inicio imagen
			//y*widthStep inicio la fila y, desde la imagen
			//x*nChannels inicio del pixel desde la fila
			ppix = (unsigned char *)img->imageData + y * img->widthStep + x * img->nChannels;
			ppox = (unsigned char *)imgSal->imageData + y * imgSal->widthStep + x * imgSal->nChannels;

			// Aquí se transforma el color de cada pixel para conseguir los tonos grises
			// Aplica la formula que aparece en el ejercicio:
			/*... Una forma de hacerlo es sustituyendo los valores R, G y B de cada píxel
			por la media ponderada de la luminosidad de los colores del píxel,
			que se calcula como ...
			*/
			double a = 0.3 * (amplitudDistorsion/2);	//Recicla la variable global amplitudDistorsion para cambiar los colores de los pixeles.
			double b = 0.55 * (amplitudDistorsion/2);	//El numero que le pasemos en el miniMenu, mientras mas grende sea, mas iluminacion tendrá la imagen
			double c = 0.15 * (amplitudDistorsion/2);
			//ppox[0] = (0.3*ppix[2] + 0.55*ppix[1] + 0.15*ppix[0]); //Rojo  
			ppox[0] = (a *ppix[2] + b *ppix[1] + c *ppix[0]); //Rojo  
			ppox[2] = ppox[1] = ppox[0];//verde/AZUL
		}
	}
}

void AGris_2x(IplImage* imgO, IplImage* imgR) { //Se ha copiado las funciones de ejemplo de TrasMalla_2x y TrasMalla_h

	//Creo 2 hilos
	for (size_t i = 0; i < NRO_HILOS; i++) {
		pInfoHilos[i] = new di_aGris_t; // reserva memoria
		pInfoHilos[i]->imgO = imgO;
		pInfoHilos[i]->imgR = imgR;
		pInfoHilos[i]->nroHilo = i;
		pInfoHilos[i]->totalHilos = NRO_HILOS; // relleno info para el hilo

		pInfoHilos[i]->h = CreateThread(NULL, 0, AGris_h, pInfoHilos[i], 0, &pInfoHilos[i]->id);
		CheckError(NULL == pInfoHilos[i]->h, "ERROR al crear el hilo TrasMalla_h", 1);
	}

	//Espero a que terminen
	for (size_t i = 0; i < NRO_HILOS; i++) {
		DWORD res = WaitForSingleObject(pInfoHilos[i]->h, INFINITE);
		CheckError(WAIT_OBJECT_0 != res, "ERROR al bloquear esperando fin de hilo", 1);
		delete pInfoHilos[i];
	}
}

DWORD WINAPI AGris_h(LPVOID parametroVoid) { 

	IplImage* imgO, * imgR;
	pdi_aGris_t p = (pdi_aGris_t)parametroVoid;
	imgO = p->imgO;
	imgR = p->imgR;

	//En esta funcion se ha sustituido el funcionamiento correspondiente de TrasMalla por el de AGris
	DWORD y, x;

	for (y = p->nroHilo; y < imgO->height; y += p->totalHilos)
	{
		// Procesa pixels dentro de cada scanline
		for (x = 0; x < imgO->width; x++)
		{

			unsigned char* ppix, * ppox;

			// Calcula la dirección del pixel actual
			//imageData inicio imagen
			//y*widthStep inicio la fila y, desde la imagen
			//x*nChannels inicio del pixel desde la fila
			ppix = (unsigned char*)imgO->imageData + y * imgO->widthStep + x * imgO->nChannels;
			ppox = (unsigned char*)imgR->imageData + y * imgR->widthStep + x * imgR->nChannels;

			// Aquí se transforma el color de cada pixel para conseguir los tonos grises
			// Aplica la formula que aparece en el ejercicio:
			/*... Una forma de hacerlo es sustituyendo los valores R, G y B de cada píxel
			por la media ponderada de la luminosidad de los colores del píxel,
			que se calcula como ...
			*/
			double a = 0.3 * (amplitudDistorsion / 2);	//Recicla la variable global amplitudDistorsion para cambiar los colores de los pixeles.
			double b = 0.55 * (amplitudDistorsion / 2);	//El numero que le pasemos en el miniMenu, mientras mas grende sea, mas iluminacion tendrá la imagen
			double c = 0.15 * (amplitudDistorsion / 2);
			//ppox[0] = (0.3*ppix[2] + 0.55*ppix[1] + 0.15*ppix[0]); //Rojo  
			ppox[0] = (a * ppix[2] + b * ppix[1] + c * ppix[0]); //Rojo  
			ppox[2] = ppox[1] = ppox[0];//verde/AZUL
		}
	}
	return 0;
}

void AGris_Nx(IplImage* imgO, IplImage* imgR)
{
	pdi_aGris_t pdi[NRO_HILOS];

	for (int i = 0; i < NRO_HILOS; i++) {
		pdi[i] = new di_aGris_t;

		pdi[i]->imgO = imgO;
		pdi[i]->imgR = imgR;
		pdi[i]->nroHilo = i;
		pdi[i]->totalHilos = 2;
		pdi[i]->h = CreateThread(0, 0, AGris_h, pdi[i], 0, 0);
		pdi[i]->totalHilos = NRO_HILOS;

		pdi[i]->h = CreateThread(0, 0, AGris_h, pdi[i], 0, 0);
		CheckError(pdi[i]->h == NULL, "No se pudo crear el hilo", 1);
	}

	for (int i = 0; i < NRO_HILOS; i++) {
		WaitForSingleObject(pdi[i]->h, INFINITE);
	}

}





