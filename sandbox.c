#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    printf("%ld\n", sizeof(char*));
    printf("%ld\n", sizeof(int*));
    printf("%ld\n", sizeof(size_t*));
    return 0;
}