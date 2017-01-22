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
    #include "../table/types.h"
};


void gerador(No *raiz, std::string outputfilename);
void processano(No *raiz, int level);
S_table geratabeladevariaveisefuncoes();
S_table geratabeladetipos();
void replace(std::string& str, const std::string& from, const std::string& to);
void incluiSimboloNaTabela( std::string nomedosimbolo, std::string valor );
std::string recuperaNomeVariavel(std::string nomedavariavel);
std::string recuperaValorSimboloNaTabela(std::string nomeSimbolo);
Ty_ty recuperaValorDoTipoNaTabela(std::string nomeSimbolo);
std::string getglobal();
std::string gettemporario();
void declare_global_string(std::string string, std::string temp, int size);
void retiraAspasOpenString(std::string &open_string);
void prepareCallWrite(std::string &call_func, std::string value, std::string global_temp, int size);

#endif //PROJETOU_GERADOR_H
