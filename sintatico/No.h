//
// Created by sutil on 03/01/17.
//

#ifndef PROJETOU_NO_H
#define PROJETOU_NO_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

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

    void imprimir(){
        cout << "\"" << this->nome << "\"";
        if(!this->filhos.empty()) {
            cout << ":{";
            for (int i = 0; i < this->filhos.size(); ++i) {
                if(i != 0)
                    cout << ",";

                this->filhos[i]->imprimir();
            }
            cout << "}";
        } else
            cout << ": \"\" ";
    }
};
typedef struct no No;

#endif //PROJETOU_NO_H
