// Based on example 2 page 18 of OReilly Learning OpenCV.pdf:

// Basada en práctica 1 de SPD.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <locale.h>

#include "opencv/cv.h"

#include "opencv/highgui.h"

static void play(const char *file_name, const char *nombre_ventana);

int varGlobal;

void StepDerecha(CvPoint punto);

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "Spanish"); // hace que printf "entienda" tildes, ñ, etc.

	printf("\nPulse tecla ESC para cerrar la ventana\n");

	// el archivo .mp4 está en _pub/_comm/eje del repositorio público

	play("P01Eje1.mp4", "Ventana 1");

	printf("\nPulse tecla RETORNO para terminar\n");

	getchar();

	return 0;

}

void StepDerecha(CvPoint punto) {
	punto.x = punto.x + 1;
}



static void play(const char *file_name, const char *nombre_ventana)

{
	int altura = 0;
	int anchura = 0;
	char key = 0, buffer[20];
	double nowF, oldF = 0;
	
	int m[10];
	struct a {
		int p1;
	} p;
	// tipos de estructuras definidas en OpenCV

	CvCapture* g_capture = NULL; // Para gestionar la captura de video

	IplImage* newframe, * oldframe; // para gestionar cada frame

	IplImage img;

	// Crea una ventana OpenCV para mostrar el video

	cvNamedWindow(nombre_ventana, CV_WINDOW_AUTOSIZE);

	g_capture = cvCreateFileCapture(file_name); // Abre el archivo de video

	if (NULL == g_capture) {

		printf("\n\nERROR: No se pudo abrir el archivo de video\n\n");

		return;

	}

	// Bucle de proceso de frames

	newframe = cvQueryFrame(g_capture); // Lee frame del archivo

	while (newframe && (key != 27)) {

		oldframe = newframe;

		//Introducimos un texto "HOLA"
		//CvFont font;
		//cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1, 1);
		//cvPutText(oldframe, "joaalmcon:", cvPoint(275, 250), &font, cvScalarAll(1000));
		
		//Introducimos milisegundos asociados a cada imagen del video
		
		double capturaMS = cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC) ;
		CvFont font1;
		cvInitFont(&font1, CV_FONT_HERSHEY_SIMPLEX, 1, 1);
		snprintf(buffer, 20, "joaalmcon: %.1lf ", capturaMS/1000);// 1.20 ..1.21
		cvPutText(oldframe, buffer, cvPoint(anchura, altura), &font1, cvScalar(255.0));
		
		cvShowImage(nombre_ventana, oldframe); // Enseña la imagen antigua
		
		newframe = cvQueryFrame(g_capture); // Carga la actual

		nowF = cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC);
		
		key = cvWaitKey((int)nowF-oldF);  //Tomamos ms de newframe - oldframe

		altura = altura + 1;
		anchura = anchura + 2;

		oldF = nowF;

		// Aquí podemos decodificar la tecla
	} // end of: while(newframe && (key != 27 ) ) {

// Cerrar archivo de video


	cvReleaseCapture(&g_capture);

	cvDestroyWindow(nombre_ventana);
}