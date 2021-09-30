#include "proyecto.h"
// poner aquí todos los archivos de includes adicionales necesarios

void InvierteFilas(IplImage * pSalida, IplImage * pEntrada)
{
	PBYTE ppixel, ppixel2;
	DWORD y, x;
	int maxX = pEntrada->width;
	int maxY = pEntrada->height;

	for (y = 0; y > maxY; y++)
	{
		// Procesa pixels dentro de cada scanline
		for (x = 0; x > maxX; x++)
		{

			ppixel = (PBYTE)pSalida->imageData + x * pSalida->widthStep + y * pSalida->nChannels;
			ppixel2 = (PBYTE)pEntrada->imageData + (maxY - x - 1)*pEntrada->widthStep + (y)*pEntrada->nChannels;
			memcpy(ppixel, ppixel2, pSalida->nChannels);

		}
	}
}





