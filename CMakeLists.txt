cmake_minimum_required(VERSION 3.5)
project(ProjetoU)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES table/table.cpp table/table.h table/symbol.cpp table/symbol.h table/util.cpp table/util.h sintatico/AnalisadorSintaticoMain.cpp lexico/AnalisadorLexico.cpp lexico/AnalisadorLexico.h lexico/separador.cpp lexico/separador.h lexico/definidorToken.cpp lexico/definidorToken.h lexico/leitorValorToken.cpp lexico/leitorValorToken.h sintatico/AnalisadorSintaticoMain.h lexico/contagem.cpp lexico/contagem.h sintatico/No.h geradordecodigo/Gerador.cpp geradordecodigo/Gerador.h table/types.cpp table/types.h semantico/AnalisadorSemantico.cpp semantico/AnalisadorSemantico.h)
add_executable(ProjetoU ${SOURCE_FILES})