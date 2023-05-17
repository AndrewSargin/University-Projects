#include <stdio.h>
#ifndef MENU_H
#define MENU_H

void MainMenu(struct refbook*, struct refbook*, struct refbook*, struct autoshow*, struct autoshow*, FILE *, FILE *);
void MenuFile(struct autoshow*&, struct autoshow*&, FILE *&);
void MenuEdit(struct refbook*&, struct refbook*&, struct refbook*&, struct autoshow*&, struct autoshow*&, FILE *&, FILE *&);
void MenuRefBook(struct refbook*&, struct refbook*&, struct refbook*&, FILE *&);
void ChooseRefBook(struct refbook *&, struct refbook *&, FILE *&, const char *&);

#endif // MENU_H
