//
// Created by sutil on 16/12/16.
//

#include "definidorToken.h"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

vector<string> BRACKETS = {"begin", "end", "(", ")", "[", "]", "`", "'"};
vector<string> TIPOS = {"own", "boolean", "integer","real", "array", "switch", "procedure"};
vector<string> SIMBOLOS = {":=", "+"};
vector<string> RELATIONAL_OPERATORS = {">", ">=", "==", "<", "<="};
vector<string> SPECIFICATORS = {"string", "label", "value"};

string NUM = "NUM";
string TIPO = "declarator";
string ID = "ID";
string SIMBOLO = "SIMBOLO";
string RELATIONAL_OPERATOR = "RELATIONAL_OPERATOR";
string SPECIFICATOR = "specificator";

bool isBracket(string valor){
    for(int i = 0; i < BRACKETS.size(); i++)
        if(BRACKETS[i].compare(valor) == 0)
            return true;

    return false;
}

bool isSpecificator(string valor){
    for(int i = 0; i < SPECIFICATORS.size(); i++)
        if(SPECIFICATORS[i].compare(valor) == 0)
            return true;

    return false;
}

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

bool isOperadorRelacional(string valor){
    for(int i = 0; i < RELATIONAL_OPERATORS.size(); i++)
        if(RELATIONAL_OPERATORS[i].compare(valor) == 0)
            return true;

    return false;
}

string getTipoToken(string valor){
    if(isNumero(valor))
        return NUM;

    if(isBracket(valor))
        return "bracket";

    if(isTipo(valor))
        return TIPO;

    if(isSpecificator(valor))
        return SPECIFICATOR;

    if(isOperadorRelacional(valor))
        return RELATIONAL_OPERATOR;

    if(isIdentificador(valor))
        return ID;

    if(isSimbolo(valor))
        return SIMBOLO;

    return "NADA";
}