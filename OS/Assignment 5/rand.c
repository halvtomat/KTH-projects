#include <math.h>

#define MAX 4000
#define MIN 8

int request() {

    /* k is log(MAX/MIN) */
    double k = log(((double) MAX)/MIN);

    /* r is [0..k] */
    double r = ((double)( rand() % (int)(k*10000))) / 10000;

    /* size is [0.. MAX] */
    int size = (int)((double)MAX / exp(r));

    return size;
}