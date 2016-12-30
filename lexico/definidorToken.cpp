//
// Created by sutil on 16/12/16.
//

#include "definidorToken.h"
#include <iostream>
#include <string>
#include <regex>
#include "../terminais.h"

using namespace std;

vector<string> BRACKETS = {"begin", "end", "(", ")", "[", "]", "`", "'"};
vector<string> TIPOS = {"own", "boolean", "integer","real", "array", "switch", "procedure"};

vector<string> RELATIONAL_OPERATORS = {">", ">=", "==", "<", "<="};
vector<string> SPECIFICATORS = {"string", "label", "value"};
vector<string> SEPARATORS = {",", ".", ":", ";", ":=", "_", "step", "until", "while", "comment"};
vector<string> SEQUENTIAL_OPERATORS = {"goto", "if", "then", "else", "for", "do"};
vector<string> ARITHMETIC_OPERATORS = {ARITHMETIOPERATOR_MAIS, ARITHMETIOPERATOR_MENOS, ARITHMETIOPERATOR_VEZES, ARITHMETIOPERATOR_DIVIDIR};

string NUM = "NUM";
string TIPO = "declarator";
string ID = "ID";
string SIMBOLO = "SIMBOLO";
string RELATIONAL_OPERATOR = "RELATIONAL_OPERATOR";
string SPECIFICATOR = "specificator";
string SEPARATOR = "separator";
string BRACKET = "bracket";
string SEQUENTIAL_OPERATOR = "sequential operator";
string ARITHMETIC_OPERATOR = "arithmetic operator";

bool estaEm(vector<string> lista, string valor){
    for(int i = 0; i < lista.size(); i++)
        if(lista[i].compare(valor) == 0)
            return true;

    return false;
}

bool isArithmetcOperator(string valor){
    return estaEm(ARITHMETIC_OPERATORS, valor);
}

bool isSequentialOperator(string valor){
    return estaEm(SEQUENTIAL_OPERATORS, valor);
}

bool isSeparator(string valor){
    return estaEm(SEPARATORS, valor);
}

bool isBracket(string valor){
    return estaEm(BRACKETS, valor);
}

bool isSpecificator(string valor){
    return estaEm(SPECIFICATORS, valor);
}

bool isTipo(string valor){
    return estaEm(TIPOS, valor);
}

bool isNumero(string valor) {
    regex regex_num("[0-9]+");

    return regex_match(valor, regex_num);
}

bool isIdentificador(string valor){
    regex regex_id("[a-z]+");

    return regex_match(valor, regex_id);
}

bool isOperadorRelacional(string valor){
    return estaEm(RELATIONAL_OPERATORS, valor);
}

string getTipoToken(string valor){
    if(isNumero(valor))
        return NUM;

    if(isSequentialOperator(valor))
        return SEQUENTIAL_OPERATOR;

    if(isSeparator(valor))
        return SEPARATOR;

    if(isBracket(valor))
        return BRACKET;

    if(isTipo(valor))
        return TIPO;

    if(isSpecificator(valor))
        return SPECIFICATOR;

    if(isOperadorRelacional(valor))
        return RELATIONAL_OPERATOR;

    if(isArithmetcOperator(valor))
        return ARITHMETIC_OPERATOR;

    if(isIdentificador(valor))
        return ID;

    return "NADA";
}