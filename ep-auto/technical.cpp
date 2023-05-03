#include "technical.h"
#include "structures.h"
#include <iostream>

using namespace std;

void Pause() {
    printf("Чтобы продолжить, нажмите Enter");
    cin.ignore();
    cin.get();
}

int OpenCheck(FILE *pfile) {
    if(pfile==NULL)
    {
        printf("Файл был не был открыт во время вызова меню\n");
        Pause();
        return 0;
    }
return 1;
}

struct refbook* RefbookMemoryFree(struct refbook *pointer) {
    if(pointer)
    {
        while(pointer->next)
        {
            pointer=pointer->next;
            pointer->previous->next=NULL;
            free(pointer->previous);
            pointer->previous=NULL;
        };
        pointer->next=NULL;
        free(pointer);
        pointer=NULL;
    }
    return pointer;
}
