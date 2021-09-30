//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Based on example 2 page 18 of OReilly Learning OpenCV.pdf:
// Basada en práctica 1 de SPD.
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <locale.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

static void play(const char*, const char*);

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "Spanish");					// hace que printf "entienda" tildes, ñ, etc. 
	printf("\nPulse tecla ESC para cerrar la ventana\n");
	play((char*)"P01Eje1.mp4", (char*)"Ventana 1");	// el archivo .mp4 está en _pub/_comm/eje del repositorio público
	printf("\nPulse tecla RETORNO para terminar\n");
	getchar();
	return 0;
}

//2.8
void StepDerecha(CvPoint* punto) {
	punto->x++;
}

static void play(const char* file_name, const char* nombre_ventana)
{
	char key = 0;

	// tipos de estructuras definidas en OpenCV
	CvCapture* g_capture = NULL;					// Para gestionar la captura de video
	IplImage* newframe, * oldframe;					// para gestionar cada frame
	IplImage img;

	// Crea una ventana OpenCV para mostrar el video
	cvNamedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture(file_name);		// Abre el archivo de video
	if (NULL == g_capture) {
		printf("\n\nERROR: No se pudo abrir el archivo de video\n\n");
		return;
	}
	else
	{
		double anterior = 0.0;
		CvFont font;
		double hScale = 1.0;
		double vScale = 1.0;
		int lineWidth = 1;
		CvPoint org;
		double antes = 0, gap, ahora;
		char buffer[20];
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, hScale, vScale, 0, lineWidth);
		// Bucle de proceso de frames
		newframe = cvQueryFrame(g_capture);			// Lee frame del archivo
		while (newframe && (key != 27)) {
			oldframe = newframe;
			//snprintf(buffer, 20, "%s ", "Hola");
			//snprintf(buffer, 20, "%lf ", cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC) / 1000);
			snprintf(buffer, 20, "%s, %lf ", "jorcallag", cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC) / 1000);
			cvPutText(oldframe, buffer, org, &font, cvScalar(255.0));
			org.x = (org.x + 5) %500;
			org.y = (org.x + 5) %500;
			cvShowImage(nombre_ventana, oldframe);	// Enseña la imagen antigua
			newframe = cvQueryFrame(g_capture);		// Carga la actual
			ahora = cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC);
			gap = ahora - antes;
			antes = ahora;							// Lee la posición de tiempo del frame
			key = cvWaitKey((int)gap);				// Espera que se pulse una tecla con un timeout de 42 ms(aprox,velocidad normal)
			
		} 
		cvReleaseCapture(&g_capture);				// Cerrar archivo de video
	}
	cvDestroyWindow(nombre_ventana);
}