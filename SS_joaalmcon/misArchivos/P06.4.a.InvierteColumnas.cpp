#include "proyecto.h"
// poner aqu? todos los archivos de includes adicionales necesarios

void InvierteColumnas(IplImage * imgO, IplImage * imgD)
{
	BOOL alterar;
	int anchoColumnas = 100;

	// Recorre filas y columnas de la matriz de p?xeles. 
	for (int y = 0; y < imgO->height; y ++) { // Recorre scanlines y reparte a cada hilo

		for (int x = 0; x < imgO->width; x++) {
			// Invierte el valor de X en el pixel de destino
			unsigned char * pO = (unsigned char *)&imgO->imageData[y*imgO->widthStep + x * imgO->nChannels];
			unsigned char * pD = (unsigned char *)&imgD->imageData[y*imgD->widthStep + (imgO->width - x - 1)*imgD->nChannels];
			// Copia pixel de origen a pixel de destino.
			memcpy(pD, pO, imgD->imageSize);

		}  // Fin proceso de columnas
	}  // Fin proceso de filas
}





