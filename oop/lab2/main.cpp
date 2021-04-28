#include "adressBook.hpp"
#include <locale.h>


int main(){
    system("chcp 1251");
    int mode, pos, datSize, datMaxSize;
    ifstream fset;
    fset.open ("settings.txt");
    fset >> datSize;
    datMaxSize = datSize * 2;
    fset.close();
    adressField *dat;
    dat = (adressField*)malloc(datMaxSize*sizeof(adressField));
    printf ("what to do? [H]elp\n");
    initData (dat, datSize);
    while (mode != '0'){
        mode = getchar();
        mode = tolower(mode);
        switch (mode){
            case 's':
                cout << "input surname:" << endl;
                char surname[20];
                cin >> surname;
                searchBySurname(dat, datSize, surname);
            break;
            case 'a':
                if (datSize+1 > datMaxSize){
                    datMaxSize *= 2;
                    dat = (adressField*) realloc (dat, datMaxSize * sizeof(adressField));
                }
                dat[datSize].readData();
                datSize++;
            break;
            case 'p':
                for (int i = 0; i < datSize; i++){
                    dat[i].printData();
                }
            break;
            case 'r':
                cout << "which contact should be removed?" << endl;
                cin >> pos;
                if (pos-1 > datSize){
                    cout << "unable to remove!" << endl;
                }
                datSize = removeAdress(dat, pos-1, datSize);
            break;
            case '0':
                saveChanges(dat, datSize);
                return 0;
            case 'h': printf ("Available commands: [S]earch, [A]dd, [P]rint all contacts, [R]emove. 0 to stop\n");
            break;
        }
    }
    return 0;
}
