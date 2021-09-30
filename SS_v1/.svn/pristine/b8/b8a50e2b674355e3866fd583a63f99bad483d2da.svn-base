//.h común a todo el proyecto
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include <cmath>

#include "opencv/cv.h"
#include "opencv/highgui.h"

// este tambien está en $(AAComm)inc
#include "enumPatrones.h"

#include "jorcallag-LibSS.h"

char * ImagenAVentana(IplImage *, char *, char *, bool, int *);
IplImage * GeneraBMP24cv(DWORD maxX, DWORD maxY, DWORD tipodepatron);
void TrasMalla(IplImage* imgO, IplImage* imgR, double sinUso1, double sinUso2);
void TrasMalla_2x(IplImage* imgO, IplImage* imgR);
DWORD WINAPI TrasMalla_h(LPVOID par);
void AGris_2x(IplImage* imgO, IplImage* imgR);
DWORD WINAPI AGris_h(LPVOID parametroVoid);
void AGris_Nx(IplImage* imgO, IplImage* imgR);
void ProcesaImagen(IplImage *, IplImage *, double=0.0, double=0.0);
void AGris(IplImage* img, IplImage* imgSal);
void miniMenu();
DWORD WINAPI Reproduce(LPVOID par);
DWORD WINAPI Reproduce_12(LPVOID par);
void miniMenu_12();
DWORD WINAPI Reproduce_8(LPVOID par);
void miniMenu_8();
DWORD WINAPI Reproduce_16(LPVOID par);

