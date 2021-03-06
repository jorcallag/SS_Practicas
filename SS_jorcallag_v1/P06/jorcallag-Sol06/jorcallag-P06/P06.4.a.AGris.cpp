//MAL MONTAJE ARREGLADO
#include "proyecto.h"
// poner aqu? todos los archivos de includes adicionales necesarios

void AGris(IplImage * img, IplImage * imgSal)
{
	DWORD y, x;

	for (y = 0; y < img->height; y++)
	{
		// Procesa pixels dentro de cada scanline
		for (x = 0; x < img->width; x++)
		{

			unsigned char * ppix, *ppox;

			// Calcula la direcci?n del pixel actual
			//imageData inicio imagen
			//y*widthStep inicio la fila y, desde la imagen
			//x*nChannels inicio del pixel desde la fila
			ppix = (unsigned char *)img->imageData + y * img->widthStep + x * img->nChannels;
			ppox = (unsigned char *)imgSal->imageData + y * imgSal->widthStep + x * imgSal->nChannels;

			// Aqu? se transforma el color de cada pixel para conseguir los tonos grises
			// Aplica la formula que aparece en el ejercicio:
			/*... Una forma de hacerlo es sustituyendo los valores R, G y B de cada p?xel
			por la media ponderada de la luminosidad de los colores del p?xel,
			que se calcula como ...
			*/
			ppox[0] = (0.3*ppix[2] + 0.55*ppix[1] + 0.15*ppix[0]); //Rojo     <----------------------------EXCEPTION
			ppox[2] = ppox[1] = ppox[0];//verde/AZUL
		}
	}
}





