//
// Created by sutil on 16/12/16.
//

#include "definidorToken.h"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

vector<string> TIPOS = {"int", "char"};
vector<string> SIMBOLOS = {":=", "+"};

string NUM = "NUM";
string TIPO = "TIPO";
string ID = "ID";
string SIMBOLO = "SIMBOLO";

bool isTipo(string valor){
    for(int i = 0; i < TIPOS.size(); i++)
        if(TIPOS[i].compare(valor) == 0)
            return true;

    return false;
}

bool isNumero(string valor) {
    regex regex_num("[0-9]+");

    return regex_match(valor, regex_num);
}

bool isIdentificador(string valor){
    regex regex_id("[a-z]+");

    return regex_match(valor, regex_id);
}

bool isSimbolo(string valor){
    for(int i = 0; i<SIMBOLOS.size();i++)
        if(SIMBOLOS[i].compare(valor) == 0)
            return true;
    return false;
}

string getTipoToken(string valor){
    if(isNumero(valor))
        return NUM;

    if(isTipo(valor))
        return TIPO;

    if(isIdentificador(valor))
        return ID;

    if(isSimbolo(valor))
        return SIMBOLO;

    return "NADA";
}