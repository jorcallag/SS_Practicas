#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "joaalmcon-P03-Static.h"
#include "joaalmcon-P03-Dynamic.h"

//extern "C" void VarGlobaLib_joaalmcon79(char *);
//extern "C" char FuncionLib_joaalmcon79[];



static void play(const char* file_name, const char* nombre_ventana);

int varGlobal;

void StepDerecha(CvPoint punto);

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "Spanish"); // hace que printf "entienda" tildes, ?, etc.

	printf("\nPulse tecla ESC para cerrar la ventana\n");

	// el archivo .mp4 est? en _pub/_comm/eje del repositorio p?blico

	play("P01Eje1.mp4", "Ventana 1");

	printf("\nPulse tecla RETORNO para terminar\n");

	getchar();

	return 0;

}

void StepDerecha(CvPoint punto) {
	punto.x = punto.x + 1;
}



static void play(const char* file_name, const char* nombre_ventana)

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

		//Firma_joaalmcon_Dynamic(oldframe);
		
		//Firma_joaalmcon_Static(oldframe);

		// Prueba de uso de una DLL sin biblioteca de importaci?n

		{

			HMODULE HLibreriaDll; // Handle. Lo veremos en el tema siguiente.

			// Puntero a funci?n. Comparar la definici?n con la definici?n de Firma_nusuario en el archivo .h

			void (*pFuncion)(CvArr*);

			HLibreriaDll = LoadLibrary("joaalmcon-P03-Dynamic.dll"); // ?Carga? la dll donde est? la func.

			if (HLibreriaDll != NULL)

			{
				//usamos dumpbin /EXPORTS D:\Desktop\SSRoot\joaalmcon\P03\joaalmcon-SolP03\Debug\joaalmcon-P03-Dynamic.dll
				//y obtenemos el nombre de la funcion con su correspondiente decoraci?n
				pFuncion = (void (*)(CvArr*))GetProcAddress(HLibreriaDll,

					"?Firma_joaalmcon_Dynamic@@YAXPAX@Z");

				if (pFuncion != NULL) // Usar el dato/funci?n

					(*pFuncion)(oldframe);

				FreeLibrary(HLibreriaDll); // Libera la librer?a

			}

		}

		cvShowImage(nombre_ventana, oldframe); // Ense?a la imagen antigua

		newframe = cvQueryFrame(g_capture); // Carga la actual

		nowF = cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC);

		key = cvWaitKey((double)nowF - oldF);  //Tomamos ms de newframe - oldframe

		altura = altura + 1;
		anchura = anchura + 2;

		oldF = nowF;

		// Aqu? podemos decodificar la tecla
	} // end of: while(newframe && (key != 27 ) ) {

// Cerrar archivo de video


	cvReleaseCapture(&g_capture);

	cvDestroyWindow(nombre_ventana);
}