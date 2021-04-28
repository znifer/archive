#include "adressBook.hpp"
void adress::readAdress (){
    cin >> country >> city >> street >> building >> apart;
    //scanf ("%s %s %s %i %i", country, city, street, &building, &apart);
}

void adress::printAdress(){
    cout << country << " " << city << " " << street << " " << building << " " << apart << " ";
    //printf ("%s %s %s %i %i ", country, city, street, building, apart);
}

void fullName::readName(){
    cin >> surname >> name >> patr;
    //scanf ("%s %s %s", name, surname, patr);
}

void fullName::printName(){
    cout << surname << " " << name << " " << patr << " ";
    //printf ("%s %s %s ", name, surname, patr);
}

void phoneNumber::readNumber(){
    cin >> hNumber >> wNumber;
    //scanf ("%s %s", hNumber, wNumber);
}

void phoneNumber::printNumber(){
    cout << hNumber << " " << wNumber;
    //printf ("%s %s", hNumber, wNumber);
}

void adressField::printData (){
    n.printName();
    a.printAdress();
    p.printNumber();
    cout << endl;
    //printf ("\n");
}

void adressField::readData (){
    //printf ("\nFull name/country/city/street/building/apart\n");
    n.readName();
    a.readAdress();
    p.readNumber();
}

void initData (adressField *dat, int datSize){
    ifstream f;
    f.open("data.txt");
    for (int i = 0; i < datSize; i++){
        f >> dat[i].n.surname >> dat[i].n.name >> dat[i].n.patr >> dat[i].a.country >> dat[i].a.city >> dat[i].a.street >> dat[i].a.building >> dat[i].a.apart >> dat[i].p.hNumber >> dat[i].p.wNumber;
        //dat[i].printData();
    }
    f.close();
}

int searchBySurname (adressField *dat, int datSize, char *surname){
    for (int i = 0; i < datSize; i++){
        if (strcmp (dat[i].n.surname, surname) == 0){
            dat[i].printData();
            return i;
        }
    }
    cout << "not found :c" << endl;
}

int removeAdress(adressField *dat, int pos, int datSize){
    swap (dat[pos], dat[datSize-1]);
    return datSize - 1;
}

void saveChanges (adressField *dat, int datSize){
    ofstream f, sett;
    f.open ("data.txt", ios::out);
    for (int i = 0; i < datSize; i++){
       f << dat[i].n.surname << " " << dat[i].n.name << " " << dat[i].n.patr << " " << dat[i].a.country << " " << dat[i].a.city << " " << dat[i].a.street << " "
       << dat[i].a.building << " " << dat[i].a.apart << " " << dat[i].p.hNumber << " " << dat[i].p.wNumber << endl;
    }
    f.close();
    sett.open ("settings.txt", ios::out);
    sett << datSize;
    sett.close();
    cout << "all changes are saved!" << endl;
}
