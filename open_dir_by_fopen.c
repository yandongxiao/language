#include <stdio.h>

int main() {
    FILE *file = fopen("/home", "r");

    if(file == NULL)
        printf("can open dir\n");
    else
        printf("opening a dir\n");
}
