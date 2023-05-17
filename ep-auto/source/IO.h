#include <stdio.h>
#ifndef IO_H
#define IO_H

void OpenFile(struct autoshow*&, struct autoshow*&, FILE *&in);
void SaveFile(struct autoshow*);
void PrintDoc(struct refbook*&, struct refbook*&, struct refbook*&, struct autoshow*&, FILE *, FILE *&);
void ExportToTxt(struct refbook*&, struct refbook*&, struct refbook*&, struct autoshow*&, FILE *, FILE *&);
void PrintRefBook(struct refbook*, FILE*);
void OpenRefbook(struct refbook*&, struct refbook*&, FILE *&, const char *&);
struct refbook* RefbookRead(struct refbook*, FILE *);
void RefbookSave(struct refbook*&, FILE *&, const char *&);
void About();
int ScanfNumericNoId(struct refbook*, char *);
int ScanfNumericId(struct refbook*, char *);
char *ScanfLiteral(struct refbook*, char *);

#endif // IO_H
