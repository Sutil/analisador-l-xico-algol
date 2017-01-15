//
// Created by sutil on 14/01/17.
//

#include "AnalisadorSemantico.h"
#include <stack>
#include "../table/symbol.h"

stack<S_table*> pilha;

bool isInicioDeEscopo(No * no){
    return no->nome.compare("block") == 0;
}

bool isDeclaracaoVariavel(No * no){
    return no->nome.compare("type declaration") == 0;
}

void varrerVariaveis(No * no){
    if(no->isTerminal())
        cout << no->nome << " ";

    for(No * filho : no->filhos)
        varrerVariaveis(filho);
}

void varrerBloco(No * bloco){
    for(No * filho : bloco->filhos){

        if(isDeclaracaoVariavel(filho)){
            cout << filho->nome << endl;

            No* localOrOwnType = filho->filhos[0];
            No * tipo = localOrOwnType->filhos[0];
            No * tipoVariavel = tipo->filhos[0];

            cout << tipoVariavel->nome << " ";

            No * typeList = filho->filhos[1];

            varrerVariaveis(typeList);

            cout << endl;
            continue;
        }

        if(!isInicioDeEscopo(filho))
            varrerBloco(filho);
    }
}

void percorreArvore(No * no){


    if(isInicioDeEscopo(no)){
        cout << no->nome << endl;

        varrerBloco(no);

        cout << "fim do escopo" << endl << endl;

        //percorre filhos

        //fim do escopo

    }

    for(No * n : no->filhos)
        percorreArvore(n);


}


bool aliseSemantica(No * raiz){
    percorreArvore(raiz);
}

