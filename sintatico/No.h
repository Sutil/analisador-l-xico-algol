//
// Created by sutil on 03/01/17.
//

#ifndef PROJETOU_NO_H
#define PROJETOU_NO_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct no {
    string nome;
    vector<no> filhos;

    no(string nome){
        this->nome = nome;
    }

    void addFilho(no * node){
        this->filhos.push_back(*node);
    }

    void removeFilho(no * filho){
       // std::remove(filhos.begin(), filhos.end(), filho);
    }

    void imprimir(){
        cout << this->nome << "{" <<endl;
        for(no &fi : this->filhos){
            cout << "\t";
            fi.imprimir();
            cout << ", ";
        }
        cout << endl << "}" << endl;
    }
};
typedef struct no No;

#endif //PROJETOU_NO_H
