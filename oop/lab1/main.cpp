#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;
float solve (float a, float b, char c){
    switch (c){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
    }
}
float getResult(char *s){
    float result = 0;
    if (strlen(s)<5){
        result = solve (s[0]-'0', s[2]-'0', s[1]);
    } else{
        if (s[3]=='*'||s[3]=='/'){
            result = solve(s[2]-'0', s[4]-'0', s[3]);
            result = solve(s[0]-'0', result, s[1]);
        } else{
            result = solve(s[0]-'0', s[2]-'0', s[1]);
            result = solve(result, s[4]-'0', s[3]);
        }
    }
    return result;
}
int main(){
    char filename[256], s[256];
    ifstream fin;
    ofstream fout;
    cout << "path?" << endl;
    cin >> filename;
    fin.open(filename);
    fin >> s;
    fin.close();
    fout.open(filename, std::ios::app);
    fout << "=" << getResult (s) <<endl;
    fout.close ();
    return 0;
}
