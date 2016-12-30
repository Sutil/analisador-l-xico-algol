//
// Created by sutil on 16/12/16.
//

#ifndef PROJETOU_ANALISADORLEXICO_H
#define PROJETOU_ANALISADORLEXICO_H

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

struct token {
    string valor;
    string nome;
    int linha;
    int coluna;

    token(string valor, string nome, int linha, int coluna){
        this->valor = valor;
        this->nome = nome;
        this->linha = linha;
        this->coluna = coluna;
    }
};
typedef struct token Token;

void inicializaAnalizadorLexico(FILE * pFile);

Token * getToken();

long retornaPonteiroAtual();

void restauraPonteiro(int posicao);

#endif //PROJETOU_ANALISADORLEXICO_H
