#include "technical.h"
#include "structures.h"
#include <stdlib.h>

void Pause() {
    printf("Чтобы продолжить, нажмите Enter\n");
    do getchar();
    while(getchar()!='\n');
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
        struct refbook *pointer_2;
        while(pointer)
        {
            pointer_2=pointer;
            pointer=pointer->next;
            pointer_2->next=NULL;
            free(pointer_2);
            pointer_2=NULL;
        };
    }
    return pointer;
}

void CloseFile(struct autoshow *&pautoshow, FILE *&in) {
    system("clear");
    if(!OpenCheck(in)) return;
    fclose(in);
    in=NULL;                 //это необходимо, чтобы после открытия и закрытия файла, после еще одного закрытия не было ошибки (программа вылетала)
    while(pautoshow->next)   //закрытие файла
    {
        pautoshow=pautoshow->next;
        free(pautoshow->previous);
        pautoshow->previous=NULL;
    };
    pautoshow->next=NULL;
    free(pautoshow);
    pautoshow=NULL;
    printf("Файл закрыт\n");
    return;
}
