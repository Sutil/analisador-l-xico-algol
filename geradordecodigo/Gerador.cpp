//
// Created by lucas on 11/01/17.
//

#include <fstream>
#include "Gerador.h"
#include "../table/types.h"
//#include "../table/symbol.h"

std::ofstream ir_file;
void gerador(No *raiz, std::string outputfilename) {
    int level = 0;

    ir_file.open (outputfilename + ".ll");

    S_table variaveis_functions_table = geratabeladevariaveisefuncoes();
    S_table tipos_table = geratabeladetipos();

    processano(raiz, variaveis_functions_table, tipos_table, level);

    ir_file.close();
    std::string command = "clang " + outputfilename + ".ll" + " -o " + outputfilename + ".exec";
    system(command.data());
}

S_table geratabeladevariaveisefuncoes() {
    S_table table = S_empty();

    return table;
}

S_table geratabeladetipos() {
    S_table table = S_empty();

    std::string s = "integer";

    S_enter(table, S_Symbol((_string) s.data()), Ty_Int());

    return table;
}

void processano(No *raiz, S_table variaveis_functions_table, S_table tipos_table, int level) {
    level++;


    if (raiz->nome == "program") {
        ir_file << "@.str = private unnamed_addr constant [3 x i8] c\"%d\\00\", align 1" << std::endl;

        ir_file << "define i32 @main() #0 {" << std::endl;

        for (int i = 0; i < raiz->filhos.size(); ++i) {
            processano(raiz->filhos[i], variaveis_functions_table, tipos_table, level);
        }

        ir_file << "call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i32* %a)" << std::endl;
        ir_file << "ret i32 0" << std::endl << "}" << std::endl;
        ir_file << "declare i32 @printf(i8*, ...) #1" << std::endl;
    } else if (raiz->nome == "assignment statement") {
        vector<no *> filhos = raiz->filhos;

        no *left_part_list = filhos[0];
        no *aritmetic_expression = filhos[1];
        vector<std::string> variaveis_para_atribuir;
        if (left_part_list->nome == "left part list"){
            for (int i = 0; i < left_part_list->filhos.size(); ++i) {
                no * atribuivel = left_part_list->filhos[i]->filhos[0];
                if (atribuivel->nome == "variable" && atribuivel->filhos[0]->nome == "simple variable") {
                    no * simpl_v = atribuivel->filhos[0];
                    std::string code ((char*) S_look(variaveis_functions_table, S_Symbol((_string)simpl_v->filhos[0]->nome.data())));
                    variaveis_para_atribuir.push_back(code);
                }
            }

        }


        for (int j = 0; j < variaveis_para_atribuir.size(); ++j) {
            std::cout << variaveis_para_atribuir[j] << std::endl;
            if (aritmetic_expression->nome == "arithmetc expression") {
                no * expression = aritmetic_expression->filhos[0];

                if (expression->nome == "simple arithmetc expression") {
                    no * expression_terms = expression->filhos[0];
                    if (expression_terms->nome == "term"){
                        no * term = expression_terms->filhos[0];
                        if (term->nome == "primary") {
                            no * primary = term->filhos[0];
                            if (primary->filhos[0]->nome == "decimal number") {
                                ir_file << "store i32 ";
                                ir_file << primary->filhos[0]->filhos[0]->nome << ", ";
                                ir_file << variaveis_para_atribuir[j]  << std::endl;
                            }
                        }
                    }



                }
            }
        }


    } else if (raiz->nome == "type definition") {

        vector<no *> filhos = raiz->filhos;

        no *declaration = filhos[0];
        no *type_list = filhos[1];
        void * tipodasvariaveis = NULL;

        if (declaration->nome == "local or own type") {
            vector<no *> filhos = declaration->filhos;
            no *type = filhos[0];

            if (type->nome == "type") {
                std::string t = type->filhos[0]->nome;
                tipodasvariaveis = S_look(tipos_table, S_Symbol((_string) t.data()));
            }
        }

        if (type_list->nome == "type list") {
            for (int i = 0; i < type_list->filhos.size(); ++i) {
                no * variavel = type_list->filhos[i];
                if (variavel->nome == "simple variable" && variavel->filhos.size() == 1 && tipodasvariaveis != NULL) {
                    std::string nomedavariavel = variavel->filhos[0]->nome;
                    if (tipodasvariaveis == Ty_Int()) {
                        std::string vv = "i32* ";
                        std::string v = "%" + std::string((char*)S_name(S_Symbol((_string) nomedavariavel.data())));
                        vv += v;

                        S_enter(variaveis_functions_table,S_Symbol((_string) nomedavariavel.data()), (void*)vv.data());
                        ir_file << v << " = alloca i32" << std::endl;
                    }
                }
            }
        }


    }
    else {
        for (int i = 0; i < raiz->filhos.size(); ++i) {
            processano(raiz->filhos[i], variaveis_functions_table, tipos_table, level);
        }
    }




}
