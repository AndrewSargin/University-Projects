#include <stdio.h>
#ifndef TECHNICAL_H
#define TECHNICAL_H

void Pause();
int OpenCheck(FILE *);
struct refbook* RefbookMemoryFree(struct refbook*);
void CloseFile(struct autoshow*&, FILE *&);

#endif // TECHNICAL_H
