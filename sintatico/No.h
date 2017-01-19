//
// Created by sutil on 03/01/17.
//

#ifndef PROJETOU_NO_H
#define PROJETOU_NO_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct no {
    string nome;
    vector<no*> filhos;
    int profundiade = 0;

    no(string nome){
        this->nome = nome;
    }

    void addFilho(no * node){
        this->filhos.push_back(node);
        node->profundiade = this->profundiade + 1;
    }

    void removeFilho(no * filho){
        this->filhos.erase(std::remove(filhos.begin(), filhos.end(), filho), filhos.end());
    }

    bool isTerminal(){
        return this->filhos.empty();
    }

    void imprimir(std::ofstream& arvore){
        arvore << "\"" << this->nome << "\"";
        if(!this->filhos.empty()) {
            arvore << ":{";
            for (int i = 0; i < this->filhos.size(); ++i) {
                if(i != 0)
                    arvore << ",";

                this->filhos[i]->imprimir(arvore);
            }
            arvore << "}";
        } else
            arvore << ": \"\" ";
    }
};
typedef struct no No;

#endif //PROJETOU_NO_H
