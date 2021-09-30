#include "jorcallag-P03-Static.h"

static char msg[100];
static int i = 0;

void Firma_jorcallag_Static(void * imagen){

    snprintf(msg, sizeof(msg), "Ejecutada Firma_jorcallag #%d veces\n", i++);
    OutputDebugString(msg);

}
