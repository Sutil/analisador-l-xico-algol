//
// Created by sutil on 14/01/17.
//

#include "AnalisadorSemantico.h"
#include <stack>
#include <vector>
#include "../table/symbol.h"

stack<Tabela*> pilha;

bool isInicioDeEscopo(No * no){
    return no->nome.compare("block") == 0;
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

void verifica(No * no){
    //cout << "verifica atribuição" << endl;

    No * direita = no->filhos[1];

    No * leftPartList = no->filhos[0];
    No * leftPart = leftPartList->filhos[0];
    No * variable = leftPart->filhos[0];
    No * simpleVariable = variable->filhos[0];
    // verificar se eh uma variavel simples ou um array!
    No * variavel = simpleVariable->filhos[0];


    cout << ">>>>>>>> " << variavel->nome << " <<<<<<<<<<<<<<<< " << endl;

}

void varrerVariaveis(No * no, string tipo){
    if(no->isTerminal() && no->nome.compare(",") != 0) {
        cout << tipo << " " << no->nome << endl;
        Registro * r = new Registro(tipo, no->nome);
        Tabela * tab = pilha.top();
        tab->addRegistro(r);


        return;
    }

    for(No * filho : no->filhos)
        varrerVariaveis(filho, tipo);
}


void percurso(No * no){

    if(isInicioDeEscopo(no)) {
        cout << "inicio escopo " << no->profundiade << endl;
        Tabela *t = new Tabela(no->profundiade);
        pilha.push(t);
    }

    if(isDeclaracaoVariavel(no)) {
        No* localOrOwnType = no->filhos[0];
        No * tipo = localOrOwnType->filhos[0];
        No * tipoVariavel = tipo->filhos[0];
        No * typeList = no->filhos[1];
        varrerVariaveis(typeList, tipoVariavel->nome);
    }

    if(isAtribuicaoDeVariavel(no)){
        verifica(no);
    }

    for(No * filho : no->filhos){
        percurso(filho);

        if(isFimDeEscopo(no)){
            pilha.pop();
            cout << "fim de escopo " << no->profundiade << endl << endl;
        }
    }
}




bool aliseSemantica(No * raiz){
    percurso(raiz);
}

