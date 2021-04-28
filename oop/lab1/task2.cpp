#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
void readFileContent (char *filename){
    ofstream f;
    f.open(filename, std::ios::binary);
}

void writeFileContent (char *filename){
    ifstream f;
    f.open(filename, std::ios::binary);
}

void createFile (char *filename){
    ifstream f;
    f.open(filename, std::ios::binary);
    f.close ();
}

int main(){
    char filename[256], s[256];
    strcpy (filename, "a.dat");
    createFile(filename);
    //fstream f;
    //f.open(filename, std::ios::binary);


    return 0;
}
