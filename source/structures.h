#ifndef STRUCTURES_H
#define STRUCTURES_H

struct autoshow {
    int id;
    char EngineNumber[15];
    char BodyNubmer[20];
    int ManufacturerId;
    int ModelId;
    int Power;
    int EngineVolume;
    char Class[5];
    int BodyType;
    long Price;
    struct autoshow *next;
    struct autoshow *previous;
};

struct refbook {
    int id;
    char RefData[40];
    struct refbook *next;
    struct refbook *previous;
};

#endif // STRUCTURES_H
