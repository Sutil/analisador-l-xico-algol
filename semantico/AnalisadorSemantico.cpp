//
// Created by sutil on 14/01/17.
//

#include "AnalisadorSemantico.h"
#include <stack>
#include <vector>
#include <iostream>
#include "../table/symbol.h"

stack<Tabela*> pilha;


void iniciarEscopo(No * no){
    Tabela *t;
    if(pilha.empty()) {
        t = new Tabela(no->profundiade);
        pilha.push(t);
        return ;
    }

    Tabela * tabAnterior = pilha.top();
    t = tabAnterior->copy(no->profundiade);
    pilha.push(t);
}

bool isInicioDeEscopo(No * no){
    return no->nome.compare("block") == 0;
}

bool isDeclaracao(No * no){
    return no->nome.compare("declaration") == 0
            || no->nome.compare("specification part") == 0;
}

bool isDeclaracaoVariavel(No * no){
    return no->nome.compare("type declaration") == 0;
}

bool isAtribuicaoDeVariavel(No * no){
    return no->nome.compare("assignment statement") == 0;
}

bool isFimDeEscopo(No * no){
    return isInicioDeEscopo(no);
}

bool variavelFoiDeclarada(string nomeVariavel){
    Tabela * t = pilha.top();
    return t->variavelEstaNaTabela(nomeVariavel);
}

bool verificaInteger(No * direita){
    if(direita->nome.compare("arithmetc expression") == 0)
        return true;

    for(No * f : direita->filhos){
        bool ret = verificaInteger(f);
        if(ret)
            return true;
    }

    return false;
}

void verificaAtribuicaoPorTipo(string tipo, No * direita){
    if(tipo.compare("integer") == 0)
        verificaInteger(direita);
}

string getTipoVariavel(string nomeVariavel){
    return pilha.top()->getTipoVariavel(nomeVariavel);
}

void verifica(No * no){

    No * direita = no->filhos[1];

    No * leftPartList = no->filhos[0];
    No * leftPart = leftPartList->filhos[0];
    No * variable = leftPart->filhos[0];
    No * simpleVariableOuArray = variable->filhos[0];
    if(simpleVariableOuArray->nome.compare("simple variable"))
        return;

    No * variavel = simpleVariableOuArray->filhos[0];

    string nomeVariavel = variavel->nome;
    if(!variavelFoiDeclarada(nomeVariavel)){
        std::cout << endl << "Variável '" << nomeVariavel << "' não foi declarada" << endl;
        throw runtime_error("Variável não foi declarada.");
    }

    string tipo = getTipoVariavel(nomeVariavel);

    verificaAtribuicaoPorTipo(tipo, direita);

    No * n = direita->filhos[0];
}

void varrerVariaveis(No * no, string tipo){
    if(no->isTerminal() && no->nome.compare(",") != 0) {
        //cout << tipo << " " << no->nome << endl;
        string nomeVariavel = no->nome;
        Registro * r = new Registro(tipo, nomeVariavel);
        Tabela * tab = pilha.top();
        tab->addRegistro(r);

        return;
    }

    for(No * filho : no->filhos)
        varrerVariaveis(filho, tipo);
}

string getTipoVariavel(No * declaracao){
    No *localOrOwnType = declaracao->filhos[0];
    No *tipo = localOrOwnType->filhos[0];
    No *tipoVariavel = tipo->filhos[0];
    return tipoVariavel->nome;
}


void percurso(No * no){

    if(isInicioDeEscopo(no)) {
        iniciarEscopo(no);
    }

    if(isDeclaracao(no)) {
        No * declaracao = no->filhos[0];
        if(isDeclaracaoVariavel(declaracao)) {
            string tipo = getTipoVariavel(declaracao);

            No *typeList = declaracao->filhos[1];
            varrerVariaveis(typeList, tipo);
        }
    }

    if(isAtribuicaoDeVariavel(no)){
        verifica(no);
    }

    for(No * filho : no->filhos){
        percurso(filho);

        if(isFimDeEscopo(no)){
            pilha.pop();
        }
    }
}

bool aliseSemantica(No * raiz){
    percurso(raiz);
}

