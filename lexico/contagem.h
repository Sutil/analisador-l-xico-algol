//
// Created by sutil on 02/01/17.
//

#ifndef PROJETOU_CONTAGEM_H
#define PROJETOU_CONTAGEM_H

struct estado {
    int posicao;
    int linha;
    int coluna;

    estado(int posicao, int linha, int coluna){
        this->posicao = posicao;
        this->linha = linha;
        this->coluna = coluna;
    }
};
typedef struct estado Estado;

void inicializaContagem();

void avancaCaracter(char caracter, long posicaoArquivo);

void retornaCaracter();

Estado * salvaEstadoDaContagem(long ponteiro);

Estado * restauraContagem(long posicaoArquivo);

Estado * ultimoEstadoSalvo();

#endif //PROJETOU_CONTAGEM_H
