#include "Coder.h"
#include "Decoder.h"
#include "CommunicationChannel.h"

#include "optimal_code.hpp"

#include <iostream>
#include <fstream>
using namespace std;
int main(){
    ifstream input_file;
    ofstream result;
    result.open("result.txt");
    string file_name;
    bool file_flag=false;

    while(!file_flag){
        cout<<"������ ��� 䠩��: ";
        cin>> file_name;
        input_file.open(file_name,std::ifstream::in);
        if(input_file.is_open()){
            file_flag=true;
        }
        else{
            cout<<"���ࠢ��쭮� ��� 䠩��. ������ ����."<<endl;
        };
    };

    //�⥭�� ��������� 
    //���� ���� (1 ��� 2)
    string temp_str;
    getline(input_file,temp_str);
    int file_type = stoi(temp_str.substr(0,1));
    if(file_type == 1){
        result<<2<<" ���� �������.";
    }else if(file_type == 2){
        result<<1<<" ���� �������.";
    };
    result<<endl;
    //ࠧ��� ��䠢��.
    getline(input_file,temp_str);
    int alphabet_size = stoi(temp_str.substr(0,1));
    result<<temp_str<<endl;
    //ࠧ��� ����� ��� ����஢����.
    getline(input_file,temp_str);
    int block_size = stoi(temp_str.substr(0,1));
    result<<temp_str<<endl;
    //ᯮᮡ ����஢����.
    getline(input_file,temp_str);
    int optimal_code_mode = stoi(temp_str.substr(0,1));
    result<<temp_str<<endl;
    //r ��� ���� ��������.
    getline(input_file,temp_str);
    int r_Hamming = stoi(temp_str.substr(0,1));
    result<<temp_str<<endl;
    //�⥭�� ��䠢�� � ᮧ����� ���筮�� ��䠢��
    Alphabet current_alphabet(alphabet_size);
    current_alphabet.file_read(input_file,result);
    Alphabet block_alphabet = current_alphabet.build_nsized_Alphabet(block_size);
    //����஥��� ��⨬��쭮�� ����
    block_alphabet.build_code_arr(optimal_code_mode);
    //�ய�� ��ப� � ���᭥����.
    getline(input_file,temp_str);
    //�⥭�� ������஢������ ��� ��室���� ᮮ�饭��.
    string message;
    getline(input_file,message);
    //1 - ��ࢠ� ���� ࣧ (����஢����)
    //2 - ���� ���� ࣧ (������஢����)
    Coder coder(r_Hamming);
    Decoder decoder(r_Hamming);
    string result_message;
    switch (file_type){
    case 1:{
        result_message = block_alphabet.encode_text(message);
        coder.setMessage(result_message);
        result_message=coder.getCode();
        CommunicationChannel chan(r_Hamming,result_message);
        result_message = chan.addErrors();
        cout<<"����஢���� �ᯥ譮 �����襭�."<<endl;
        result<<"������஢����� ᮮ�饭��: "<<endl;
        break;}
    case 2:{
        decoder.setCodeMessage(message);
        result_message=decoder.getCode();
        result_message = block_alphabet.decode_text(result_message);
        cout<<"������஢���� �ᯥ譮 �����襭�."<<endl;
        result<<"��室��� �ࠧ�: "<<endl;
        break;}
    }
    result<<result_message;
};