//
// Created by sutil on 14/01/17.
//

#include "AnalisadorSemantico.h"
#include <stack>
#include <vector>
#include "../table/symbol.h"

stack<S_table*> pilha;

bool isInicioDeEscopo(No * no){
    return no->nome.compare("block") == 0;
}

bool isDeclaracaoVariavel(No * no){
    return no->nome.compare("type declaration") == 0;
}

vector<string> varrerVariaveis(No * no, vector<string> listaDeVars){
    if(no->isTerminal() && no->nome.compare(",") != 0) {
        cout << no->nome << " ";
        listaDeVars.push_back(no->nome);
    }

    for(No * filho : no->filhos)
        varrerVariaveis(filho, listaDeVars);

    return listaDeVars;
}

vector<string> varrerVariaveis(No * no){
    vector<string> listaDeVars;
    return varrerVariaveis(no, listaDeVars);
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
        cout << no->nome << " " << no->profundiade << endl;

        varrerBloco(no);

        cout << "fim do escopo" << endl << endl;

    }

    for(No * n : no->filhos)
        percorreArvore(n);


}


bool aliseSemantica(No * raiz){
    percorreArvore(raiz);
}

