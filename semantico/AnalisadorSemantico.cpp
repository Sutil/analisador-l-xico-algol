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

void varrerBloco(No * bloco){


    for(No * filho : bloco->filhos){

        if(isDeclaracaoVariavel(filho)){
            No* localOrOwnType = filho->filhos[0];
            No * tipo = localOrOwnType->filhos[0];
            No * tipoVariavel = tipo->filhos[0];
            No * typeList = filho->filhos[1];

            varrerVariaveis(typeList, tipoVariavel->nome);

            continue;
        }

        if(isInicioDeEscopo(filho)) {
            cout << endl << filho->nome << " " << filho->profundiade << endl;
            Tabela * topo = pilha.top();
            Tabela * t = topo->copy(filho->profundiade);
            pilha.push(t);

            varrerBloco(filho);

            cout << "fim do escopo" << filho->profundiade << endl << endl;
            pilha.pop();
        }

        varrerBloco(filho);
    }
}

void percorreArvore(No * no){


    if(isInicioDeEscopo(no)){
        cout << no->nome << " " << no->profundiade << endl;
        Tabela * t = new Tabela(no->profundiade);
        pilha.push(t);

        varrerBloco(no);
        cout << "fim do escopo" << no->profundiade << endl << endl;
        pilha.pop();
    }

    for(No * n : no->filhos)
        percorreArvore(n);


}


bool aliseSemantica(No * raiz){
    percorreArvore(raiz);
}

