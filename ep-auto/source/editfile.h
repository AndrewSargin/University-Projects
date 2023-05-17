#include <stdio.h>
#ifndef EDITFILE_H
#define EDITFILE_H

void AddEntries(struct refbook*&, struct refbook*&, struct refbook*&, struct autoshow*&, struct autoshow*&, FILE *, FILE *&);
void DeleteEntries(struct autoshow*&, struct autoshow*&, FILE *);
void EditExistingEntry(struct refbook*&, struct refbook*&, struct refbook*&, struct autoshow*&, FILE *, FILE *&);
void EditEntryRefBook(struct refbook*, FILE *);
void AddEntryRefBook(struct refbook*&, struct refbook *&, FILE *);
void DeleteEntryRefBook(struct refbook*&, struct refbook*&, FILE *);

#endif // EDITFILE_H
