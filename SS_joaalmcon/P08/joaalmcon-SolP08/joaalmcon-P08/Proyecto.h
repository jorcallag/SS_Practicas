//.h común a todo el proyecto
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <windows.h>

#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "joaalmcon-LibSS.h"

char * ImagenAVentana(IplImage *, char *, char *, bool, int *);

