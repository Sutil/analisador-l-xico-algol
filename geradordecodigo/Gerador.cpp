//
// Created by lucas on 11/01/17.
//

#include <fstream>
#include "Gerador.h"
//#include "../table/symbol.h"

std::ofstream ir_file;
void gerador(No *raiz, std::string outputfilename) {

    ir_file.open (outputfilename + ".ll");

    S_table variaveis_functions_table = geratabeladevariaveisefuncoes();

    processano(raiz, variaveis_functions_table);

    ir_file.close();
    std::string command = "clang " + outputfilename + ".ll" + " -o " + outputfilename + ".exec";
    system(command.data());
}

S_table geratabeladevariaveisefuncoes() {
    S_table table = S_empty();

    return table;
}


void processano(No *raiz, S_table variaveis_functions_table) {


    if (raiz->nome == "program") {
        ir_file << "define i32 @main() #0 {" << std::endl;

        for (int i = 0; i < raiz->filhos.size(); ++i) {
            processano(raiz->filhos[i], variaveis_functions_table);
        }

        ir_file << "ret i32 0 }" << std::endl;

    } else if (raiz->nome == "type definition") {

    }
    else {
        for (int i = 0; i < raiz->filhos.size(); ++i) {
            processano(raiz->filhos[i], variaveis_functions_table);
        }
    }




}
