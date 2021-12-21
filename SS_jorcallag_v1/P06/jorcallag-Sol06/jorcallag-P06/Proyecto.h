//MAL MONTAJE ARREGLADO
//.h com�n a todo el proyecto

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

#include <windows.h>

#include "opencv/cv.h"
#include "opencv/highgui.h"

// este tambien est� en $(AAComm)inc
#include "enumPatrones.h"

#include "jorcallag-LibSS.h"

char * ImagenAVentana(IplImage *, char *, char *, bool, int *);
IplImage * GeneraBMP24cv(DWORD maxX, DWORD maxY, DWORD tipodepatron);

// Ejemplo de uso de par�metros opcionales en C++. 
// Si no se ponen, el compilador les da autom�ticamente el valor que
// aparece en la inicializaci�n
void ProcesaImagen(IplImage *, IplImage *, double=0.0, double=0.0);
void AGris(IplImage* img, IplImage* imgSal);
