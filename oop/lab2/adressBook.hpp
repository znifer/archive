#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
struct adress{
    char country[20];
    char city[20];
    char street[20];
    unsigned building;
    unsigned apart;
    void readAdress();
    void printAdress();
};

struct fullName{
    char name[20];
    char surname[20];
    char patr[20];
    void readName();
    void printName();
};

struct phoneNumber{
    char hNumber[20];
    char wNumber[20];
    void readNumber();
    void printNumber();
};

struct adressField{
    adress a;
    fullName n;
    phoneNumber p;
    void printData ();
    void readData ();
};

void initData (adressField*, int);
int searchBySurname(adressField*, int, char*);
int removeAdress(adressField*, int, int);
void saveChanges(adressField*, int);
