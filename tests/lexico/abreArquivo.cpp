//
// Created by sutil on 20/12/16.
//

#include <fstream>
using namespace  std;


FILE *criaArquivo(string conteudo) {
    ofstream outfile ("test.txt");
    outfile << conteudo << endl;
    outfile.close();

    return fopen("test.txt", "rt");
}

void fechaERemove(FILE * f){
    fclose(f);
    remove("test.txt");
}