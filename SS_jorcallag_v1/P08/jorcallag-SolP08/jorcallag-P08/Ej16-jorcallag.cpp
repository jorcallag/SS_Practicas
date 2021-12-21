#include "proyecto.h"

#define N 2

typedef struct diReproductor_t {
    HANDLE ht;
    DWORD id;
    int nroHilo;
    char nArchivo[100];
    char nVentana[100];
} diReproductor_t, * pdiReproductor_t;

HANDLE ev;
/*
int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "Spanish");
    CheckError(argc != 2, "Debe llamar al programa pasandole el nombre del archivo!", 1);

    ev = CreateEvent(NULL, TRUE, false, NULL);
    CheckError(ev == NULL, "No se pudo crear el evento", 1);

    pdiReproductor_t tablaPdis[N];
    pdiReproductor_t pdi;

    for (int i = 0; i < N; i++) {
        pdi = new diReproductor_t;
        pdi->nroHilo = i;
        memcpy(pdi->nArchivo, argv[1], sizeof(pdi->nArchivo));
        snprintf(pdi->nVentana, sizeof(pdi->nVentana), "%d: %s", i, argv[1]);
        pdi->ht = CreateThread(NULL, 0, Reproduce_16, pdi, 0, &pdi->id);
        CheckError(NULL == pdi->ht, "No se ha podido crear el hilo!", 2);
        tablaPdis[i] = pdi;
    }

    for (int i = 0; i < N; i++) {
        CheckError(WAIT_OBJECT_0 != WaitForSingleObject(pdi->ht, INFINITE), "No se puede bloquear el hilo en espera!", 3);
        delete pdi;
    }

    return 0;
}*/
/*
DWORD WINAPI Reproduce_16(LPVOID par)
{
    int tecla;
    double retrasoAcumulado = 0.0;
    int nroImagenes = 0;

    pdiReproductor_t pdi = (pdiReproductor_t)par;
    CvCapture* g_capture = cvCreateFileCapture(pdi->nArchivo);

    CheckError(WAIT_OBJECT_0 != WaitForSingleObject(ev, INFINITE), "No se puede bloquear el hilo en espera!", 3);

    int i = 0;
    printf("\nEntro en proceso, soy el hilo nº %i.\n", pdi->nroHilo);

    for (i = 0; i < 5; i++) {
        printf("Ciclo %d del hilo nº %i\n", i, pdi->nroHilo);
        Sleep(1000);
    }

    printf("Fin del hilo %i, esperando...\n", pdi->nroHilo);

    DWORD res = WaitForSingleObject(ev, 0);
    if (WAIT_OBJECT_0 == res) 
        break;

    Sleep(30000);

    return 0;
}
*/

