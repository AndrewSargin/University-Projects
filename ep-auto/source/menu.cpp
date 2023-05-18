#include <stdlib.h>
#include "menu.h"
#include "IO.h"
#include "editfile.h"
#include "technical.h"
#include "structures.h"

void MainMenu(struct refbook *pmade, struct refbook *pmodel, struct refbook *pclass, struct autoshow *pautoshow, struct autoshow *pendautoshow, FILE *in, FILE *refbook)
{
    char n[10];
    while(1)
    {
        system("clear");
        printf("ГЛАВНОЕ МЕНЮ\n"
               "1.Файл\n"
               "2.Редактировать документ\n"
               "3.Вывести на экран документ\n"
               "4.Экспорт документа в файл txt\n"
               "5.Справочник\n"
               "6.О программе\n"
               "7.Выход\n\n"
               "Введите номер пункта: ");
        scanf("%s", n);
        switch(*n)
        {
        case '1': MenuFile(pautoshow, pendautoshow, in); break;
        case '2': MenuEdit(pmade, pmodel, pclass, pautoshow, pendautoshow, in, refbook); break;
        case '3': PrintDoc(pmade, pmodel, pclass, pautoshow, in, refbook); break;
        case '4': ExportToTxt(pmade, pmodel, pclass, pautoshow, in, refbook); break;
        case '5': MenuRefBook(pmade, pmodel, pclass, refbook); break;
        case '6': About(); break;
        case '7': {
            if(in)
            {
                printf("Открыт файл. Вы хотите сохранить изменения?\n"
                       "1.Да\n"
                       "2.Нет\n\n"
                       "Введите номер пункта: ");
                scanf("%s", n);
                switch(*n)
                {
                case '1': SaveFile(pautoshow); break;
                case '2': break;
                };
                CloseFile(pautoshow, in);
            };
        }; return;
        };
    };
}

void MenuFile(struct autoshow *&pautoshow, struct autoshow *&pendautoshow, FILE *&in) {
    char n[10];
    while(1)
    {
        system("clear");
        printf("ФАЙЛ\n"
               "1.Открыть\n"
               "2.Сохранить\n"
               "3.Закрыть\n"
               "4.Назад\n\n"
               "Введите номер пункта: ");
        scanf("%s", n);
        switch(*n)
        {
        case '1': OpenFile(pautoshow, pendautoshow, in); break;
        case '2': SaveFile(pautoshow); break;
        case '3': {
            CloseFile(pautoshow, in);
            Pause();
        }; break;
        case '4': return;
        };
    };
}

void MenuEdit(struct refbook *&pmade, struct refbook *&pmodel, struct refbook *&pclass, struct autoshow *&pautoshow, struct autoshow *&pendautoshow, FILE *&in, FILE *&refbook) {
    char n[10];
    while(1)
    {
        system("clear");
        printf("МЕНЮ РЕДАКТИРОВАТЬ\n"
               "1.Добавить запись\n"
               "2.Удалить запись\n"
               "3.Редактировать существующую запись\n"
               "4.Назад\n\n"
               "Введите номер пункта: ");
        scanf("%s", n);
        switch(*n)
        {
        case '1': AddEntries(pmade, pmodel, pclass, pautoshow, pendautoshow, in, refbook); break;
        case '2': DeleteEntries(pautoshow, pendautoshow, in); break;
        case '3': EditExistingEntry(pmade, pmodel, pclass, pautoshow, in, refbook); break;
        case '4': {
            if(pmodel)
                pmodel=RefbookMemoryFree(pmodel);
            if(pmade)
                pmade=RefbookMemoryFree(pmade);
            if(pclass)
                pclass=RefbookMemoryFree(pclass);
        }; return;
        };
    };
}

void MenuRefBook(struct refbook*& pmade, struct refbook*& pmodel, struct refbook*& pclass, FILE *&refbook) {
    char n[10];
    system("clear");
    struct refbook *pOpenedRefbook=0, *pendrefbook=0;
    const char *RefbookPath;
    if(pmade)
        pmade=RefbookMemoryFree(pmade);
    if(pmodel)
        pmodel=RefbookMemoryFree(pmodel);
    if(pclass)
        pclass=RefbookMemoryFree(pclass);
    while(1)
    {
        system("clear");
        printf("МЕНЮ СПРАВОЧНИК\n"
               "1.Выбрать справочник\n"
               "2.Вывести на экран\n"
               "3.Редактировать запись в справочнике\n"
               "4.Добавить запись в справочник\n"
               "5.Удалить запись\n"
               "6.Назад\n\n"
               "Введите номер пункта: ");
        scanf("%s", n);
        switch(*n)
        {
        case '1': ChooseRefBook(pOpenedRefbook, pendrefbook, refbook, RefbookPath); break;
        case '2': PrintRefBook(pOpenedRefbook, refbook); break;
        case '3': EditEntryRefBook(pOpenedRefbook, refbook); break;
        case '4': AddEntryRefBook(pOpenedRefbook, pendrefbook, refbook); break;
        case '5': DeleteEntryRefBook(pOpenedRefbook, pendrefbook, refbook); break;
        case '6': RefbookSave(pOpenedRefbook, refbook, RefbookPath); return;
        }
    };
}

void ChooseRefBook(struct refbook *&pOpenedRefbook, struct refbook *&pendrefbook, FILE *&refbook, const char *&RefbookPath) {
    char n[10];
    while(1)
    {
        system("clear");
        printf("Выберите справочник:\n"
               "1.made.db (Производитель)\n"
               "2.model.db (Название\\марка)\n"
               "3.class.db (Тип кузова)\n"
               "4.Назад\n\n"
               "Введите номер пункта: ");
        scanf("%s", n);
        switch(*n)
        {
        case '1':
        {
            RefbookSave(pOpenedRefbook, refbook, RefbookPath);  //сохранение изменений, если был открыт какой-то справочник
            RefbookPath="../ep-auto/DB/made.db";
            OpenRefbook(pOpenedRefbook, pendrefbook, refbook, RefbookPath);
        }; break;
        case '2':
        {
            RefbookSave(pOpenedRefbook, refbook, RefbookPath);  //сохранение изменений, если был открыт какой-то справочник
            RefbookPath="../ep-auto/DB/model.db";
            OpenRefbook(pOpenedRefbook, pendrefbook, refbook, RefbookPath);
        }; break;
        case '3':
        {
            RefbookSave(pOpenedRefbook, refbook, RefbookPath);  //сохранение изменений, если был открыт какой-то справочник
            RefbookPath="../ep-auto/DB/class.db";
            OpenRefbook(pOpenedRefbook, pendrefbook, refbook, RefbookPath);
        }; break;
        case '4': return;
        };
    };
}
