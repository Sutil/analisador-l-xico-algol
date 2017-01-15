//
// Created by lucas on 11/01/17.
//

#ifndef PROJETOU_GERADOR_H
#define PROJETOU_GERADOR_H

#include "../sintatico/AnalisadorSintaticoMain.h"
#include "../table/table.h"
#include "../table/util.h"
#include "../table/symbol.h"

void gerador(No *raiz, std::string outputfilename);
void processano(No *raiz, S_table variaveis_functions_table, S_table tipos_table, int level);
S_table geratabeladevariaveisefuncoes();
S_table geratabeladetipos();

#endif //PROJETOU_GERADOR_H
