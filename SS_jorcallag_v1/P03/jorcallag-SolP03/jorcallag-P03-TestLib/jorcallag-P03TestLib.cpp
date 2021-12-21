//1. Prototipo: fichero .h
	//Dir donde esta el .h y el nombre
			//C:\Users\Jorlu\Desktop\WS\SS\jorcallag\P03\jorcallag-SolP03\jorcallag-P03-Static
			//$(SolutionDir)

#include "jorcallag-P03-Static\jorcallag-P03-Static.h"
#include "jorcallag-P03-Dynamic\jorcallag-P03-Dynamic.h"

//2. Hacer accesible la biblioteca donde esta Firma_jorcallag
	//Dir donde esta .lib y el nombre
		//C:\Users\Jorlu\Desktop\WS\SS\jorcallag\P03\jorcallag-SolP03\Debug\
		// --> $(OutDir)
		//jorcallag-P03-Static.lib


//extern "C" void VarGlobaLib_jorcallag40(char*);
//extern "C" char FuncionLib_jorcallag40[];

static void play(const char*, const char*);

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "Spanish");

	//VarGlobaLib_jorcallag40((char*) "Texto que se le pasa a la funcion");
	//printf("La variable global: %s\n", FuncionLib_jorcallag40);

	play((char*)"P01Eje1.mp4", (char*)"Ventana 1");	// el archivo .mp4 está en _pub/_comm/eje del repositorio público

	printf("\nPulse la tecla RETORNO para terminar\n");
	getchar();
	return 0;

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

			//Ejercicio 3.11
			//Firma_jorcallag_Static(oldframe);

			//Ejercicio 4.3
			//Firma_jorcallag_Dynamic(oldframe);

			// Prueba de uso de una DLL sin biblioteca de importación
			{
				HMODULE HLibreriaDll;				// Handle. Lo veremos en el tema siguiente.
													// Puntero a función. Comparar la definición con la definición de Firma_nusuario en el archivo .h
				void (*pFuncion)(CvArr*);

				HLibreriaDll = LoadLibrary("jorcallag-P03-Dynamic.dll"); // “Carga” la dll donde está la func.
				if (HLibreriaDll != NULL)
				{
					pFuncion = (void (*)(CvArr*))GetProcAddress(HLibreriaDll, "?Firma_jorcallag_Dynamic@@YAXPAX@Z");
					if (pFuncion != NULL)			// Usar el dato/función
						(*pFuncion)(oldframe);
					FreeLibrary(HLibreriaDll);		// Libera la librería
				}
			}

			//snprintf(buffer, 20, "%s ", "Hola");
			//snprintf(buffer, 20, "%lf ", cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC) / 1000);
			snprintf(buffer, 20, "%s, %lf ", "jorcallag", cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_MSEC) / 1000);
			cvPutText(oldframe, buffer, org, &font, cvScalar(255.0));
			org.x = (org.x + 5) % 500;
			org.y = (org.x + 5) % 500;
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