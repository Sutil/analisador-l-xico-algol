//
// Created by lucas on 11/01/17.
//

#ifndef PROJETOU_GERADOR_H
#define PROJETOU_GERADOR_H

#include "../sintatico/AnalisadorSintaticoMain.h"
extern "C" {
    #include "../table/table.h"
    #include "../table/util.h"
    #include "../table/symbol.h"
};


void gerador(No *raiz, std::string outputfilename);
void processano(No *raiz, int level);
S_table geratabeladevariaveisefuncoes();
S_table geratabeladetipos();
void replace(std::string& str, const std::string& from, const std::string& to);

#endif //PROJETOU_GERADOR_H
