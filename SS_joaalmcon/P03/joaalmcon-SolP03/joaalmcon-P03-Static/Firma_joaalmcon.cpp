#include <stdio.h>
#include <windows.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "joaalmcon-P03-Static.h"


static char msg[100], buffer[100];
static int i = 0;

void Firma_joaalmcon_Static(CvArr * imagen) {
	
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1, 1);
	snprintf(msg, sizeof(msg), "Ejecutada Firma_nusuario #%d veces\n", i++);
	cvPutText(imagen, msg, cvPoint(100, 100), &font, cvScalarAll(1000));

	OutputDebugString(msg);
	
	
}