//
// Created by sutil on 02/01/17.
//

#include <vector>
#include "contagem.h"
#include <stack>

using namespace std;

int linhaAtual;
int colunaAtual;

//stack<Estado> estados;
stack<Estado> historico;

Estado * atual;

void inicializaContagem(){
    linhaAtual = 1;
    colunaAtual = 0;
    atual = new Estado(0, linhaAtual, colunaAtual);
}

void avancaCaracter(char caracter, long posicao) {

    historico.push(*atual);
    if(caracter == '\n') {
        linhaAtual++;
        colunaAtual = 0;
    }
    else {
        colunaAtual++;
    }

    atual = new Estado(posicao, linhaAtual, colunaAtual);
}

//uso no analisador léxico
void retornaCaracter(){
    atual = &historico.top();
    historico.pop();

    linhaAtual = atual->linha;
    colunaAtual = atual->coluna;
}

//Estado * restauraContagem(long posicaoArquivo){
//    Estado * e = &estados.top();
//    while(e->posicao != posicaoArquivo){
//        estados.pop();
//        e = &estados.top();
//    }
//    atual = e;
//    linhaAtual = e->linha;
//    colunaAtual = e->coluna;
//    estados.pop();
//    return e;
//}

Estado * restauraContagem(long posicaoArquivo){
    Estado * e = &historico.top();
    while(e->posicao != posicaoArquivo){
        historico.pop();
        e = &historico.top();
    }
    atual = e;
    linhaAtual = e->linha;
    colunaAtual = e->coluna;
    historico.pop();
    return e;
}

//Estado *ultimoEstadoSalvo() {
//    return &estados.top();
//}

Estado *ultimoEstadoSalvo() {
    return &historico.top();
}

//Estado *salvaEstadoDaContagem(long ponteiro) {
//    Estado * estado = new Estado(ponteiro, linhaAtual, colunaAtual);
//    estados.push(*estado);
//    return estado;
//}

Estado *salvaEstadoDaContagem(long ponteiro) {
    Estado * estado = new Estado(ponteiro, linhaAtual, colunaAtual);
    historico.push(*estado);
    return estado;
}