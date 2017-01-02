//
// Created by sutil on 02/01/17.
//

#include <vector>
#include "contagem.h"
#include <stack>

using namespace std;

int linhaAtual;
int colunaAtual;

vector<Estado> estados = {};
stack<Estado> historico;

Estado * anterior;
Estado * atual;

void inicializaContagem(){
    linhaAtual = 1;
    colunaAtual = 0;
    atual = new Estado(0, linhaAtual, colunaAtual);
}

void avancaCaracter(char caracter, long posicao) {

    anterior = atual;
    if(caracter == '\n') {
        linhaAtual++;
        colunaAtual = 0;
    }
    else
        colunaAtual++;

    atual = new Estado(posicao, linhaAtual, colunaAtual);
    historico.push(*anterior);

}

void retornaCaracter(){
    atual = anterior;
    anterior = &historico.top();
    historico.pop();

    linhaAtual = atual->linha;
    colunaAtual = atual->coluna;
}

Estado * salvaEstadoDaContagem(){
    estados.push_back(*atual);
    return atual;
}

Estado * restauraContagem(long posicaoArquivo){
    for (int i = 0; i < estados.size(); ++i) {
        Estado * e = &estados[i];
        if(e->posicao == posicaoArquivo) {
            linhaAtual = e->linha;
            colunaAtual = e->coluna;
            return e;
        }
    }
    return nullptr;
}

void restauraContagem(Estado * estado){
    atual = estado;
    linhaAtual = estado->linha;
    colunaAtual = estado->coluna;
}

Estado *ultimoEstadoSalvo() {
    return &estados[estados.size()-1];
}

Estado *salvaEstadoDaContagem(long ponteiro) {
    Estado * estado = new Estado(ponteiro, linhaAtual, colunaAtual);
    estados.push_back(*estado);
    return estado;
}
