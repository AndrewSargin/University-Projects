#include "IO.h"
#include "technical.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void OpenFile(struct autoshow *&pautoshow, struct autoshow *&pendautoshow, FILE *&in) {
    struct autoshow *pprevline=0, *pmemauto;
    char DocumentLine[100];
    char *Stream;
    char separator[2]=";";
    system("clear");
    if(in!=NULL)
    {
        printf("Файл уже открыт\n");
        Pause();
        return;
    }
    if((in=fopen("../ep-auto/DB/autoshow.db", "r"))==NULL)
        printf("Файл \"autoshow.db\" не открыт\n");
    else
    {
        while(fgets(DocumentLine,100,in))
        {
            pmemauto=(struct autoshow*)malloc(sizeof(struct autoshow));
            Stream=strtok(DocumentLine, separator);
            pmemauto->id=atoi(Stream);
            Stream=strtok(NULL, separator);
            strncpy(pmemauto->EngineNumber, Stream, 15);
            Stream=strtok(NULL, separator);
            strncpy(pmemauto->BodyNubmer, Stream, 10);
            Stream=strtok(NULL, separator);
            pmemauto->ManufacturerId=atoi(Stream);
            Stream=strtok(NULL, separator);
            pmemauto->ModelId=atoi(Stream);
            Stream=strtok(NULL, separator);
            pmemauto->Power=atoi(Stream);
            Stream=strtok(NULL, separator);
            pmemauto->EngineVolume=atoi(Stream);
            Stream=strtok(NULL, separator);
            strncpy(pmemauto->Class, Stream, 5);
            Stream=strtok(NULL, separator);
            pmemauto->BodyType=atoi(Stream);
            Stream=strtok(NULL, separator);
            pmemauto->Price=atoi(Stream);
            pendautoshow=pmemauto;
            if(!pprevline)
            {
                pprevline=pmemauto;
                pautoshow=pmemauto;
            }
            else
            {
                pprevline->next=pmemauto;
                pmemauto->previous=pprevline;
                pprevline=pmemauto;
            };
            pprevline->next=NULL; //после переоткрывания указатель последнего
            //на следующего был на предыдущего, а не равен 0
        };
        printf("Файл \"autoshow.db\" готов к работе\n");
    };
    Pause();
    return;
}

void SaveFile(struct autoshow *pautoshow) {
    FILE *savedoc;
    struct autoshow *psaver;
    if((savedoc=fopen("../ep-auto/DB/autoshow.db", "w+"))==NULL)
    {
        system("clear");
        printf("Файл не открыт");
    }
    else
    {
        for(psaver=pautoshow; psaver!=0; psaver=psaver->next)
        {
            fprintf(savedoc, "%d;%s;%s;%d;%d;%d;%d;%s;%d;%ld;\n", psaver->id,
                psaver->EngineNumber, psaver->BodyNubmer,
                psaver->ManufacturerId, psaver->ModelId,
                psaver->Power, psaver->EngineVolume,
                psaver->Class, psaver->BodyType, psaver->Price);
        };
    fclose(savedoc);
    system("clear");
    printf("Файл сохранен\n");
    };
    Pause();
    return;
}

void PrintDoc(struct refbook *&pmade, struct refbook *&pmodel, struct refbook *&pclass, struct autoshow *&pautoshow, FILE *in, FILE *&refbook) {
    struct refbook *pointer;
    struct autoshow *pprint;
    char BodyType[40], Manufacturer[40], Model[40];
    system("clear");
    if(!OpenCheck(in)) return;
    if(!pautoshow)
    {
        printf("В файле нет записей\n");
        Pause();
        return;
    };

    if((refbook=fopen("../ep-auto/DB/made.db", "r"))==NULL)
    {
        printf("Файл \"made.db\" не открыт\n");
        Pause();
        return;
    }
    pmade=RefbookRead(pmade, refbook);
    if(!pmade)
    {
        printf("Справочник \"made.db\" пуст\n");
        Pause();
        return;
    }
    fclose(refbook);
    if((refbook=fopen("../ep-auto/DB/model.db", "r"))==NULL)
    {
        printf("Файл \"model.db\" не открыт\n");
        Pause();
        return;
    }
    pmodel=RefbookRead(pmodel, refbook);
    if(!pmodel)
    {
        printf("Справочник \"model.db\" пуст\n");
        Pause();
        return;
    }
    if((refbook=fopen("../ep-auto/DB/class.db", "r"))==NULL)
    {
        printf("Файл \"class.db\" не открыт\n");
        Pause();

        return;
    }
    pclass=RefbookRead(pclass, refbook);
    if(!pclass)
    {
        printf("Справочник \"class.db\" пуст\n");
        Pause();
        return;
    }
    fclose(refbook);
    refbook=NULL;

    for(pprint=pautoshow; pprint!=0; pprint=pprint->next)
    {
        for(pointer=pmade; pointer!=0 && pointer->id!=pprint->ManufacturerId; pointer=pointer->next);
        if(pointer->id!=pprint->ManufacturerId)
        {
            printf("В записи с id %d содержатся данные, которых нет в справочнике \"made.db\"\n", pprint->id);
            Pause();
            return;
        }
        strncpy(Manufacturer, pointer->RefData, 40);
        for(pointer=pmodel; pointer!=0 && pointer->id!=pprint->ModelId; pointer=pointer->next);
        if(pointer->id!=pprint->ModelId)
        {
            printf("В записи с id %d содержатся данные, которых нет в справочнике \"model.db\"\n", pprint->id);
            Pause();
            return;
        }
        strncpy(Model, pointer->RefData, 40);
        for(pointer=pclass; pointer!=0 && pointer->id!=pprint->BodyType; pointer=pointer->next);
        if(pointer->id!=pprint->BodyType)
        {
            printf("В записи с id %d содержатся данные, которых нет в справочнике \"class.db\"\n", pprint->id);
            Pause();
            return;
        }
        strncpy(BodyType, pointer->RefData, 40);

        printf("%d;%s;%s;%s;%s;%d;%d;%s;%s;%ld;\n", pprint->id,
        pprint->EngineNumber, pprint->BodyNubmer,
        Manufacturer, Model,
        pprint->Power, pprint->EngineVolume,
        pprint->Class, BodyType, pprint->Price);
    };
    RefbookMemoryFree(pmodel);
    pmodel=NULL;
    RefbookMemoryFree(pmade);
    pmade=NULL;
    RefbookMemoryFree(pclass);
    pclass=NULL;
    Pause();
}

void ExportToTxt(struct refbook *&pmade, struct refbook *&pmodel, struct refbook *&pclass, struct autoshow *&pautoshow, FILE *in, FILE *&refbook) {
    FILE *exportfile;
    struct refbook *pointer;
    struct autoshow *pprint;
    char BodyType[40], Manufacturer[40], Model[40];
    system("clear");
    if(!OpenCheck(in)) return;
    if(!pautoshow)
    {
        printf("В файле нет записей\n");
        Pause();
        return;
    };

    if((refbook=fopen("../ep-auto/DB/made.db", "r"))==NULL)
    {
        printf("Файл \"made.db\" не открыт\n");
        Pause();
        return;
    }
    pmade=RefbookRead(pmade, refbook);
    if(!pmade)
    {
        printf("Справочник \"made.db\" пуст\n");
        Pause();
        return;
    }
    fclose(refbook);
    if((refbook=fopen("../ep-auto/DB/model.db", "r"))==NULL)
    {
        printf("Файл \"model.db\" не открыт\n");
        Pause();
        return;
    }
    pmodel=RefbookRead(pmodel, refbook);
    if(!pmodel)
    {
        printf("Справочник \"model.db\" пуст\n");
        Pause();
        return;
    }
    if((refbook=fopen("../ep-auto/DB/class.db", "r"))==NULL)
    {
        printf("Файл \"class.db\" не открыт\n");
        Pause();
        return;
    }
    pclass=RefbookRead(pclass, refbook);
    if(!pclass)
    {
        printf("Справочник \"class.db\" пуст\n");
        Pause();
        return;
    }
    fclose(refbook);
    refbook=NULL;

    exportfile=fopen("../ep-auto/DB/autoshow.txt", "w+");

    for(pprint=pautoshow; pprint!=0; pprint=pprint->next)
    {

        for(pointer=pmade; pointer!=0 && pointer->id!=pprint->ManufacturerId; pointer=pointer->next);
        if(pointer->id!=pprint->ManufacturerId)
        {
            printf("В записи с id %d содержатся данные, которых нет в справочнике \"made.db\"\n", pprint->id);
            Pause();
            return;
        }
        strncpy(Manufacturer, pointer->RefData, 40);
        for(pointer=pmodel; pointer!=0 && pointer->id!=pprint->ModelId; pointer=pointer->next);
        if(pointer->id!=pprint->ModelId)
        {
            printf("В записи с id %d содержатся данные, которых нет в справочнике \"model.db\"\n", pprint->id);
            Pause();
            return;
        }
        strncpy(Model, pointer->RefData, 40);
        for(pointer=pclass; pointer!=0 && pointer->id!=pprint->BodyType; pointer=pointer->next);
        if(pointer->id!=pprint->BodyType)
        {
            printf("В записи с id %d содержатся данные, которых нет в справочнике \"class.db\"\n", pprint->id);
            Pause();
            return;
        }
        strncpy(BodyType, pointer->RefData, 40);

        fprintf(exportfile, "%d;%s;%s;%s;%s;%d;%d;%s;%s;%ld;\n", pprint->id,
        pprint->EngineNumber, pprint->BodyNubmer,
        Manufacturer, Model,
        pprint->Power, pprint->EngineVolume,
        pprint->Class, BodyType, pprint->Price);
    };
    fclose(exportfile);
    RefbookMemoryFree(pmodel);
    pmodel=NULL;
    RefbookMemoryFree(pmade);
    pmade=NULL;
    RefbookMemoryFree(pclass);
    pclass=NULL;
    Pause();
}

void PrintRefBook(struct refbook *pOpenedRefbook, FILE *refbook) {
    struct refbook *pointer;
    system("clear");
    if(!OpenCheck(refbook)) return;
    if(!pOpenedRefbook)
    {
        printf("В справочнике нет записей");
        Pause();
        return;
    }
    for(pointer=pOpenedRefbook; pointer!=0; pointer=pointer->next)
        printf("%d.%s\n", pointer->id, pointer->RefData);
    Pause();
    return;
}

void OpenRefbook(struct refbook *&pointer, struct refbook *&pendrefbook, FILE *&refbook, const char *&RefbookPath) {
    pointer=RefbookMemoryFree(pointer);    //освобождение памяти от прошлого открытого справочника
    system("clear");
    if((refbook=fopen(RefbookPath, "r"))==NULL)
    {
        printf("Справочник не открыт\n");
        Pause();
        return;
    }
    pointer=RefbookRead(pointer, refbook);
    for(pendrefbook=pointer; pendrefbook->next!=0; pendrefbook=pendrefbook->next);
    printf("Справочник готов к работе\n");
    Pause();
    return;
}

struct refbook* RefbookRead(struct refbook *pointer, FILE *refbook) {
    struct refbook *pmemrefbook, *pprevline=0;  //указатели на новую строку и конец списка
    char *Stream;   //переменная для разиения строки справочник
    char separator[2]=";";
    char RefBookLine[100];  //переменная для записи строки из справочника
    while(fgets(RefBookLine, 100, refbook)) //цикл считывает из файла по строке
    {
        pmemrefbook=(struct refbook*)malloc(sizeof(struct refbook));    //выделение памяти под строку списка
        if(pointer==NULL)  //если нет указателя на начало списка
            pointer=pmemrefbook;
        Stream=strtok(RefBookLine, separator);  //чтение id из файла
        pmemrefbook->id=atoi(Stream);   //запись id в поле id структуры
        Stream=strtok(NULL, separator); //чтение текста из файла
        strncpy(pmemrefbook->RefData, Stream, 40);  //запись текста в структуру
        if(pprevline)   //если существует предыдущая строка списка
            pprevline->next=pmemrefbook;    //ссылка с предыдущей строки на настоящую
        pmemrefbook->previous=pprevline;    //ссылка с настоящей строки на предыдущую
        pprevline=pmemrefbook;  //делаем предыдущую строку настоящей
    };
    return pointer;
}

void RefbookSave(struct refbook*& pointer, FILE *&refbook, const char *&RefbookPath) {
    int n;
    struct refbook *psave;
    if(refbook)
    {
        system("clear");
        printf("Уже есть открытый справочник.\n"
               "Вы хотите сохранить изменения?\n"
               "1.Да\n"
               "2.Нет\n"
               "Введите номер пункта:");
        while (1)
        {
        scanf("%d", &n);
        if(n==1 || n==2)
            break;
        };
        switch(n)
        {
        case 1:
        {
            refbook=fopen(RefbookPath, "w+");
            system("clear");
            if(pointer)
                for(psave=pointer; psave!=0; psave=psave->next)
                    fprintf(refbook, "%d;%s;\n", psave->id, psave->RefData);
            fclose(refbook);
            refbook=NULL;
            printf("Изменения сохранены\n");
            Pause();
            break;
        }
        case 2:
        {
            fclose(refbook);
            refbook=NULL;
            break;
        };
        }
    }
    return;
}

void About() {
    system("clear");
    char readmeline[500];
    FILE *readme;
    if((readme=fopen("../ep-auto/source/README.md", "r"))==NULL)
        printf("Файл \"README.md\" не открыт");
    else {
        while(fgets(readmeline, 500, readme))
        printf("%s", readmeline);
    };
    Pause();
    return;
}

int ScanfNumericNoId(struct refbook* pointer, char* Text) {
    struct refbook *pscanr;
    int i=1, Number, n;
    while(i)
    {
        n=2;
        printf("Введите %s: ", Text);
        scanf("%d%*c", &Number);
        for(pscanr=pointer; pscanr->next!=0 && pscanr->id!=Number; pscanr=pscanr->next);
        if(pscanr->id!=Number)
        {
            printf("В справочнике нет записи с таким id\n");
            n=1;
        };
        switch(n)
        {
        case 1: break;
        case 2: i=0; break;
        }
    };
    return Number;
}

int ScanfNumericId(struct refbook* pointer, char* Text) {
    struct refbook *pscanr;
    int i=1, Number, n;
    while(i)
    {
        n=2;
        printf("Введите %s: ", Text);
        scanf("%d%*c", &Number);
        for(pscanr=pointer; pscanr->next!=0 && pscanr->id!=Number; pscanr=pscanr->next);
        if(pscanr->id==Number)
        {
            printf("В справочнике уже есть запсиь с таким id\n");
            n=1;
        };
        switch(n)
        {
        case 1: break;
        case 2: i=0; break;
        }
    };
    return Number;
}

char* ScanfLiteral(struct refbook *pointer, char* data) {
    struct refbook *pscan;
    int i=1, n;
    while(i)
    {
        n=2;
        data[0]='\0';   //позволит получить значение длины пустой строки, т.к. не garbage value
        printf("Введите новое содержимое справочника: ");
        while(1)
        {
            fgets(data, 100, stdin);
        if(strcmp(data, "\n")==0)
            printf("Поля необходимо заполнить");
        else break;
        }
        data[strlen(data)-1]='\0';
        if(pointer)
        {
            for(pscan=pointer; pscan->next!=0 && strcmp(pscan->RefData, data)!=0; pscan=pscan->next);
            if(strcmp(pscan->RefData, data)==0)
            {
                printf("Такое содержимое уже существует, введите другое\n\n");
                n=1;
            };
        };
        switch(n)
        {
        case 1: break;
        case 2: i=0; break;
        };
    }
    return data;
}
