#include "stdutil.h"
void memset(void *dest, uint32_t value, uint32_t count){
    char *temp = (char*)dest;
    for(;count != 0; count--){
        *temp++ = value;
    }
}