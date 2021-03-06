#include "proyecto.h"
// poner aqu? todos los archivos de includes adicionales necesarios

int main(int argc, char *argv[])
{
	int tecla;	// permite leer las teclas que pulsa el usuario en las ventanas openCV
	char * nombreVentana;

	// comprueba que el usuario ha puesto el ancho y alto de la imagen en l?nea de comandos
	CheckError(argc != 3, "Debe haber al menos 2 argumentos (alto y ancho de la imagen)", 1);

	setlocale(LC_ALL, "Spanish"); // Previo

	// Para la imagen original usamos un patr?n conocido
	//IplImage * imgOriginal = GeneraBMP24cv(atoi(argv[1]), atoi(argv[2]), Patron_Verde_BandaVertical0_255);	//Cambiamos patron_10 por 
																											//Patron_BN_BandaVertical0_255
	IplImage* imgOriginal = cvLoadImage("fondo.jpg");																		//para ejercicio 6.4
	do
	{
		// Muestra la imagen original en una ventana OpenCv hasta que el usuario pulsa una tecla
		nombreVentana = ImagenAVentana(imgOriginal, (char*)"Original", (char*)"Pulsa una tecla\npara continuar...", false, &tecla);
	} while (tecla == -1);

	printf("Cerrando primera ventana..."); // <-- descomentar para ejercicio 6.2 
	//cvDestroyWindow(nombreVentana);	// cierra la primera ventana
	// crea imagen de resultado
	IplImage * imgResultado = cvCreateImage(CvSize(imgOriginal->width, imgOriginal->height),
		imgOriginal->depth, imgOriginal->nChannels);											//nChannel y depth estan intercambiados dando
																					//error por el tama?o de la imagen creada

	double retrasoAcumulado = 0.0; // permite calcular la velocidad de proceso de las im?genes
	int nroImagenes = 0;
	do
	{
		char mensaje[200];
		MideRetraso(0);	//<-- Solo medimos el tiempo de proceso de la imagen. Desde aqu?
		ProcesaImagen(imgOriginal, imgResultado);
		//Sleep(100);
		retrasoAcumulado += MideRetraso(0);	// --> hasta aqu?
		nroImagenes++;
		// Construimos el mensaje
		snprintf(mensaje, sizeof(mensaje),														//ERROR detectado %s en vez de %d para el 
			"procesando %d imagenes en %3.3f segs \n (%3.3f imgs/s) \n Pulsa ENTER para terminar",	//oarametro nroImagenes
			nroImagenes, retrasoAcumulado, nroImagenes / retrasoAcumulado);
		// Muestra el resultado
		ImagenAVentana(imgResultado, (char*)"RESULTADO:", mensaje, true, &tecla);
	} while (tecla != 13);	// salimos cuando el usuario pulsa la tecla Retorno

	return 0;
}
