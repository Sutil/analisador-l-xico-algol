//
// Created by lucas on 11/01/17.
//

#include <fstream>
#include <sstream>
#include "Gerador.h"

S_table variaveis_functions_table = geratabeladevariaveisefuncoes();
S_table tipos_table = geratabeladetipos();

std::stringstream ir_global;
std::stringstream ir_body;
std::string int_format ("%d\\0A\\00");

int temporario = 0;
int temporario_global = 0;

void gerador(No *raiz, std::string outputfilename) {
    int level = 0;

    processano(raiz, level);

    std::ofstream file;
    file.open (outputfilename + ".ll");
    file << "target triple = \"x86_64-pc-linux-gnu\"" << std::endl;
    file << "declare i32 @printf(i8*, ...)" << std::endl;
    file << ir_global.str();
    file << ir_body.str();
    file.close();
    std::string command = "clang " + outputfilename + ".ll" + " -o " + outputfilename + ".exec";
    system(command.data());
}

S_table geratabeladevariaveisefuncoes() {
    S_table table = S_empty();

    return table;
}

S_table geratabeladetipos() {
    S_table table = S_empty();

    S_enter(table, S_Symbol(String("integer")), Ty_Int());

    return table;
}

void processano(No *raiz, int level) {
    level++;

    if (raiz->nome == "program") {
        ir_body << "define i32 @main() {" << std::endl;

        for (int i = 0; i < raiz->filhos.size(); ++i) {
            processano(raiz->filhos[i], level);
        }

        ir_body << "ret i32 0" << std::endl << "}" << std::endl;

    } else if (raiz->nome == "begin") {
        S_beginScope(variaveis_functions_table);
        S_beginScope(tipos_table);

    } else if (raiz->nome == "end") {
        S_endScope(variaveis_functions_table);
        S_endScope(tipos_table);

    } else if (raiz->nome == "procedure statement") {

        no * identifer = raiz->filhos[0];
        no * parameter_part = raiz->filhos[1];

        std::string call_func;
        if (identifer->nome == "procedure identifier") {
            if (identifer->filhos[0]->nome == "write"){
                call_func = " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([%1 x i8], [%1 x i8]* %2, i32 0, i32 0), i32 ";
            }
        }

        if (parameter_part->nome == "actual parameter part") {
            no * parameter_list = parameter_part->filhos[1];
            for (int i = 0; i < parameter_list->filhos.size(); ++i) {
                no * parameter = parameter_list->filhos[i]->filhos[0];
                if (parameter->nome == "expression") {
                    no * aritmetic_expression = parameter->filhos[0];
                    if (aritmetic_expression->nome == "arithmetc expression") {
                        no * simple_expression = aritmetic_expression->filhos[0];
                        if (simple_expression->nome == "simple arithmetc expression") {
                            no * expression_terms = simple_expression->filhos[0];
                            if (expression_terms->nome == "term"){
                                no * term = expression_terms->filhos[0];
                                if (term->nome == "primary") {
                                    if (term->filhos[0]->nome == "unsigned number") {
                                        std::string global_temp = getglobal();
                                        declare_global_string(int_format, global_temp, 4);
                                        replace(call_func, "%1", std::to_string(4));
                                        replace(call_func, "%2", global_temp);
                                        ir_body << gettemporario() << call_func << term->filhos[0]->filhos[0]->filhos[0]->nome << ")" << std::endl;
                                    } else if (term->filhos[0]->nome == "variable") {
                                        std::string temp (gettemporario());
                                        no * simpl_variable = term->filhos[0]->filhos[0];
                                        std::string global_temp = getglobal();
                                        prepareCallWrite(call_func, int_format, global_temp, 4);
                                        ir_body << temp << " = load i32, ";
                                        ir_body << recuperaValorSimboloNaTabela(simpl_variable->filhos[0]->nome.data()) << std::endl;
                                        ir_body << gettemporario() << call_func << temp << ")" << std::endl;
                                    }

                                }
                            }
                        }
                    }
                } else if (parameter->nome == "open string") {
                    std::string global_temp = getglobal();
                    std::string open_string (parameter->filhos[0]->nome);
                    retiraAspasOpenString(open_string);
                    prepareCallWrite(call_func, open_string + "\\00", global_temp, open_string.size() + 1);
                    ir_body << gettemporario() << call_func << 0 << ")" << std::endl;
                }
            }
        }


    } else if (raiz->nome == "assignment statement") {
        vector<no *> filhos = raiz->filhos;

        no *left_part_list = filhos[0];
        no *aritmetic_expression = filhos[1];
        vector<std::string> variaveis_para_atribuir;
        if (left_part_list->nome == "left part list"){
            for (int i = 0; i < left_part_list->filhos.size(); ++i) {
                no * atribuivel = left_part_list->filhos[0]->filhos[0];
                if (atribuivel->nome == "variable" && atribuivel->filhos[0]->nome == "simple variable") {
                    no * simpl_v = atribuivel->filhos[0];
                    variaveis_para_atribuir.push_back(recuperaValorSimboloNaTabela(simpl_v->filhos[0]->nome.data()));
                }
            }

        }

        for (int j = 0; j < variaveis_para_atribuir.size(); ++j) {
            if (aritmetic_expression->nome == "arithmetc expression") {
                no * expression = aritmetic_expression->filhos[0];
                if (expression->nome == "simple arithmetc expression") {
                    no * expression_terms = expression->filhos[0];
                    if (expression_terms->nome == "term"){
                        no * term = expression_terms->filhos[0];
                        if (term->nome == "primary") {
                            no * primary = term->filhos[0];
                            if (primary->filhos[0]->nome == "decimal number") {
                                ir_body << "store i32 ";
                                ir_body << primary->filhos[0]->filhos[0]->nome << ", ";
                                ir_body << variaveis_para_atribuir[j] << std::endl;
                            }
                        }
                    }
                }
            }
        }


    } else if (raiz->nome == "type declaration") {

        vector<no *> filhos = raiz->filhos;

        no *declaration = filhos[0];
        no *type_list = filhos[1];
        Ty_ty tipodasvariaveis = NULL;

        if (declaration->nome == "local or own type") {
            vector<no *> filhos = declaration->filhos;
            no *type = filhos[0];

            if (type->nome == "type") {
                tipodasvariaveis = recuperaValorDoTipoNaTabela(type->filhos[0]->nome);
            }
        }

        if (type_list->nome == "type list") {
            for (int i = 0; i < type_list->filhos.size(); ++i) {
                no * variavel = type_list->filhos[i];
                if (variavel->nome == "simple variable" && variavel->filhos.size() == 1 && tipodasvariaveis != NULL) {
                    std::string nomedavariavel = variavel->filhos[0]->nome;
                    if (tipodasvariaveis == Ty_Int()) {
                        incluiSimboloNaTabela(nomedavariavel, "i32* %" + recuperaNomeVariavel(nomedavariavel));
                        ir_body << "%";
                        ir_body << recuperaNomeVariavel(nomedavariavel) << " = alloca i32" << std::endl;
                    }
                }
            }
        }
    }
    else {
        for (int i = 0; i < raiz->filhos.size(); ++i) {
            processano(raiz->filhos[i], level);
        }
    }
}

void incluiSimboloNaTabela( std::string nomedosimbolo, std::string valor ) {
    S_enter(variaveis_functions_table,S_Symbol(String((char*) nomedosimbolo.data())), String((char*)valor.data()));
    return;
}

std::string recuperaNomeVariavel(std::string nomedavariavel) {
    return std::string((char*)(S_name(S_Symbol(String((char*) nomedavariavel.data())))));
}

std::string recuperaValorSimboloNaTabela(std::string nomeSimbolo) {
    return std::string ((char*)S_look(variaveis_functions_table, S_Symbol(String((char*)nomeSimbolo.data()))));
}

Ty_ty recuperaValorDoTipoNaTabela(std::string nomeSimbolo) {
    return (Ty_ty) S_look(tipos_table, S_Symbol(String((char*)nomeSimbolo.data())));
}

void replace(std::string& str, const std::string& from, const std::string& to) {
    std::size_t start_pos;
    while(((start_pos = str.find(from)) != std::string::npos)) {
        str.replace(start_pos, from.length(), to);
    }

    return;
}

std::string gettemporario() {
    temporario++;

    std::stringstream r;
    r << "%" << temporario;
    return r.str();
}

std::string getglobal() {

    std::stringstream r;
    r << "@" << temporario_global;

    temporario_global++;

    return r.str();
}

void declare_global_string(std::string string, std::string temp, int size) {

    std::string s (" = private unnamed_addr constant [%1 x i8] c\"%2\", align 1");

    replace(s, "%1", std::to_string(size));
    replace(s, "%2", string);

    ir_global << temp << s << std::endl;
}

void retiraAspasOpenString(std::string &open_string) {
    replace(open_string, "\"", "");
    return;
}

void prepareCallWrite(std::string &call_func, std::string value, std::string global_temp, int size) {
    declare_global_string( value, global_temp, size);
    replace(call_func, "%1", std::to_string(size));
    replace(call_func, "%2", global_temp);
    return;

}