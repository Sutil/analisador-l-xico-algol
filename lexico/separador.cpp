//
// Created by sutil on 16/12/16.
//

#include <vector>
#include "separador.h"

std::vector<char> descartaveis = {' ', '\n', '\t'};
std::vector<char> naoDescartaveis = {':', ';', '+','-','*','/', '(', ')', '[', ']' , '`', '\'', ','};
std::vector<char> separadorComSequencia = {':','=','!'};



bool isSeparadorDescartavel(char caraceter) {
    for(int i = 0; i< descartaveis.size() ; i++)
        if(caraceter == descartaveis[i])
            return true;
    return false;
}

bool isSeparadorNaoDescartavel(char caracter){
    for(int i = 0; i < naoDescartaveis.size() ; i++)
        if(naoDescartaveis[i] == caracter)
            return true;
    return false;
}

bool isSeparadorComSequencia(char caracter){
    for(int i = 0; i < separadorComSequencia.size() ; i++)
        if(separadorComSequencia[i] == caracter)
            return true;
    return false;
}

bool isSeparador(char cararcter){
    return isSeparadorComSequencia(cararcter)||
           isSeparadorDescartavel(cararcter) ||
           isSeparadorNaoDescartavel(cararcter);
}