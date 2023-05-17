#include "editfile.h"
#include "structures.h"
#include "technical.h"
#include "IO.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void AddEntries(struct refbook *&pmade, struct refbook *&pmodel, struct refbook *&pclass, struct autoshow *&pautoshow, struct autoshow *&pendautoshow, FILE *in, FILE *&refbook) {
    struct autoshow *pscana, *pmemauto;
    int i=1, n, id, ManId, ModelId, Power, Volume, BodyTypeId;
    long Price;
    char EngNum[15], BodyNum[20], Class[5], OutputText[100];
    system("clear");
    if(!OpenCheck(in)) return;
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

    pmemauto=(struct autoshow*)malloc(sizeof(struct autoshow));
    pmemauto->next=0;    //очищение указателя на следующего от garbage value
    if(!pautoshow)   //если файл пуст
    {
        pautoshow=pmemauto;
        pautoshow->id=-1;
    }
    else
    {
        pendautoshow->next=pmemauto;
        pmemauto->previous=pendautoshow;
    };

    while(i)
    {
        n=2;
        printf("Введите id записи: ");
        scanf("%d%*c", &id);
            for(pscana=pautoshow; pscana->next!=0 && pscana->id!=id; pscana=pscana->next);
            if(pscana->id==id)
            {
                printf("Запись с таким id уже существует, введите другой\n");
                n=1;
            };
        switch(n)
        {
        case 1: break;
        case 2: i=0; break;
        };
    };

    printf("Введите номер двигателя:");
    EngNum[0]='\0';   //позволит получить значение длины пустой строки, т.к. не garbage value
    while(1)
    {
        fgets(EngNum, 15, stdin);
    if(strcmp(EngNum, "\n")==0)
        printf("Поля необходимо заполнить");
    else break;
    }
    EngNum[strlen(EngNum)-1]='\0';

    BodyNum[0]='\0';   //позволит получить значение длины пустой строки, т.к. не garbage value
    printf("Введите номер кузова: ");
    while(1)
    {
        fgets(BodyNum, 20, stdin);
    if(strcmp(BodyNum, "\n")==0)
        printf("Поля необходимо заполнить");
    else break;
    }
    BodyNum[strlen(BodyNum)-1]='\0';

    strncpy(OutputText, "id производителя", 100);
    ManId=ScanfNumericNoId(pmade, OutputText);
    OutputText[0]='\0';

    strncpy(OutputText, "id названия/марки автомобиля", 100);
    ModelId=ScanfNumericNoId(pmodel, OutputText);
    OutputText[0]='\0';

    printf("Введите мощность двигателя: ");
    scanf("%d%*c", &Power);
    printf("Введите объем двигателя: ");
    scanf("%d%*c", &Volume);

    printf("Введите класс автомобиля: ");
    Class[0]='\0';   //позволит получить значение длины пустой строки, т.к. не garbage value
    while(1)
    {
        fgets(Class, 5, stdin);
    if(strcmp(Class, "\n")==0)
        printf("Поля необходимо заполнить");
    else break;
    }
    Class[strlen(Class)-1]='\0';

    strncpy(OutputText, "id типа кузова", 100);
    BodyTypeId=ScanfNumericNoId(pclass, OutputText);
    OutputText[0]='\0';

    printf("Введите стоимость автомобиля: ");
    scanf("%ld%*c", &Price);

    pendautoshow=pmemauto;
    pmemauto->id=id;
    strncpy(pmemauto->EngineNumber, EngNum, 15);
    strncpy(pmemauto->BodyNubmer, BodyNum, 10);
    pmemauto->ManufacturerId=ManId;
    pmemauto->ModelId=ModelId;
    pmemauto->Power=Power;
    pmemauto->EngineVolume=Volume;
    strncpy(pmemauto->Class, Class, 5);
    pmemauto->BodyType=BodyTypeId;
    pmemauto->Price=Price;
}

void DeleteEntries(struct autoshow *&pautoshow, struct autoshow *& pendautoshow, FILE *in) {
    struct autoshow *pscan;
    int n;
    system("clear");
    if(!OpenCheck(in)) return;  //Проверка на то, что файл открыт
    if(pautoshow==NULL) //проверка на то, что список сформирован
    {
        printf("В файле нет записей\n");
        Pause();
        return;
    };
    printf("Введите id записи, которую нужно удалить: ");
    scanf("%d", &n);
    for(pscan=pautoshow; pscan->id!=n && pscan->next; pscan=pscan->next);
    if (pscan->id!=n)
    {
        printf("В файле нет записи с введенным id\n");
        Pause();
        return;
    };
    if(pscan->previous)
        pscan->previous->next=pscan->next;
    else pautoshow=pautoshow->next;
    if(pscan->next)
        pscan->next->previous=pscan->previous;
    else pendautoshow=pendautoshow->previous;
    free(pscan);
}

void EditExistingEntry(struct refbook *&pmade, struct refbook *&pmodel, struct refbook *&pclass, struct autoshow *&pautoshow, FILE *in, FILE *&refbook) {
    struct autoshow *pscana;
    int i=1, n, id, ManId, ModelId, Power, Volume, BodyTypeId;
    long Price;
    char EngNum[10], BodyNum[20], Class[5], OutputText[100];
    system("clear");
    if(!OpenCheck(in)) return;
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
    while(i)
    {
        n=2;
        printf("Введите id записи: ");
        scanf("%d%*c", &id);
            for(pscana=pautoshow; pscana->next!=0 && pscana->id!=id; pscana=pscana->next);
            if(pscana->id!=id)
            {
                printf("В файле нет записи с таким id\n");
                n=1;
            };
        switch(n)
        {
        case 1: break;
        case 2: i=0; break;
        };
    };

    printf("Введите номер двигателя:");
    EngNum[0]='\0';   //позволит получить значение длины пустой строки, т.к. не garbage value
    while(1)
    {
        fgets(EngNum, 10, stdin);
    if(strcmp(EngNum, "\n")==0)
        printf("Поля необходимо заполнить");
    else break;
    }
    EngNum[strlen(EngNum)-1]='\0';

    BodyNum[0]='\0';   //позволит получить значение длины пустой строки, т.к. не garbage value
    printf("Введите номер кузова: ");
    while(1)
    {
        fgets(BodyNum, 20, stdin);
    if(strcmp(BodyNum, "\n")==0)
        printf("Поля необходимо заполнить");
    else break;
    }
    BodyNum[strlen(BodyNum)-1]='\0';

    strncpy(OutputText, "id производителя", 100);
    ManId=ScanfNumericNoId(pmade, OutputText);
    OutputText[0]='\0';

    strncpy(OutputText, "id названия/марки автомобиля", 100);
    ModelId=ScanfNumericNoId(pmodel, OutputText);
    OutputText[0]='\0';

    printf("Введите мощность двигателя: ");
    scanf("%d%*c", &Power);
    printf("Введите объем двигателя: ");
    scanf("%d%*c", &Volume);

    printf("Введите класс автомобиля: ");
    Class[0]='\0';   //позволит получить значение длины пустой строки, т.к. не garbage value
    while(1)
    {
        fgets(Class, 5, stdin);
    if(strcmp(Class, "\n")==0)
        printf("Поля необходимо заполнить");
    else break;
    }
    Class[strlen(Class)-1]='\0';

    strncpy(OutputText, "id типа кузова", 100);
    BodyTypeId=ScanfNumericNoId(pclass, OutputText);
    OutputText[0]='\0';

    printf("Введите стоимость автомобиля: ");
    scanf("%ld%*c", &Price);

    pscana->id=id;
    strncpy(pscana->EngineNumber, EngNum, 15);
    strncpy(pscana->BodyNubmer, BodyNum, 10);
    pscana->ManufacturerId=ManId;
    pscana->ModelId=ModelId;
    pscana->Power=Power;
    pscana->EngineVolume=Volume;
    strncpy(pscana->Class, Class, 5);
    pscana->BodyType=BodyTypeId;
    pscana->Price=Price;
}

void EditEntryRefBook(struct refbook *pOpenedRefbook, FILE *refbook) {
    struct refbook *pscan;
    int id;
    char data[40], OutputText[100];
    system("clear");
    if(!OpenCheck(refbook)) return;
    if(!pOpenedRefbook)
    {
        printf("В справочнике нет записей\n");
        Pause();
        return;
    }
    strncpy(OutputText, "id записи", 100);
    id=ScanfNumericNoId(pOpenedRefbook, OutputText);
    ScanfLiteral(pOpenedRefbook, data);
    for(pscan=pOpenedRefbook; pscan->id!=id; pscan=pscan->next);
    strncpy(pscan->RefData, data, 40);
    Pause();
    return;
}
void AddEntryRefBook(struct refbook *&pOpenedrefbook, struct refbook *&pendrefbook, FILE *refbook) {

    struct refbook *pmemrefbook;
    int id;
    char data[40], OutputText[100];
    system("clear");
    if(!OpenCheck(refbook)) return;

    pmemrefbook=(struct refbook*)malloc(sizeof(struct refbook));
    pmemrefbook->next=0;    //очищение указателя на следующего от garbage value
    if(!pOpenedrefbook)   //если справочник пуст
        pOpenedrefbook=pmemrefbook;
    else
    {
        pendrefbook->next=pmemrefbook;
        pmemrefbook->previous=pendrefbook;
    };
    pendrefbook=pmemrefbook;

    strncpy(OutputText, "id записи", 100);
    id=ScanfNumericId(pOpenedrefbook, OutputText);
    ScanfLiteral(pOpenedrefbook, data);

    pendrefbook->id=id;
    strncpy(pendrefbook->RefData, data, 40);
    Pause();
    return;
}
void DeleteEntryRefBook(struct refbook *&pOpenedRefbook, struct refbook *&pendrefbook, FILE *refbook) {
    struct refbook *pscan;
    int n;
    system("clear");
    if(!OpenCheck(refbook)) return;
    if(pOpenedRefbook==NULL) //проверка на то, что список сформирован
    {
        printf("В файле нет записей\n");
        Pause();
        return;
    };
    printf("Введите id записи, которую нужно удалить: ");
    scanf("%d", &n);
    for(pscan=pOpenedRefbook; pscan->id!=n && pscan->next; pscan=pscan->next);
    if (pscan->id!=n)
    {
        printf("В файле нет записи с введенным id\n");
        Pause();
        return;
    };
    if(pscan->previous)
        pscan->previous->next=pscan->next;
    else pOpenedRefbook=pOpenedRefbook->next;
    if(pscan->next)
        pscan->next->previous=pscan->previous;
    else pendrefbook=pendrefbook->previous;
    free(pscan);
}
