
#include <Windows.h>
#include "joaalmcon-LibSS.h"


double MideRetraso(LPCTSTR pMensaje) {
	static BOOL primera = TRUE;
	static LARGE_INTEGER cuenta, c_ini, c_fin, frecuencia;
	BOOL resFrec, resCont;
	double segs = 0.5;
	char mensaje[200] = "";
	
	if(primera){

		primera = FALSE;
		segs = 0.0;
		resFrec = QueryPerformanceFrequency(&frecuencia);
		CheckError(resFrec == FALSE, "Error al obtener la frecuencia, intentelo de nuevo.", 1);
		resCont = QueryPerformanceCounter(&c_ini);
		CheckError(resCont == FALSE, "Error al ejecutar el contador", 1);

	}else {

		QueryPerformanceCounter(&c_fin);
		cuenta.QuadPart =  c_fin.QuadPart - c_ini.QuadPart;
		c_ini = c_fin;
		segs = (double)cuenta.QuadPart / frecuencia.QuadPart;

		snprintf(mensaje, 200, "%s%.3f segs.", pMensaje, segs);
		OutputDebugString(mensaje);
	}
		
	return segs;

}