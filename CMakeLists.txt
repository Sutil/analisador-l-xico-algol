cmake_minimum_required(VERSION 3.5)
project(AlgolCompiler)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fpermissive")

set(SOURCE_FILES table/table.c table/table.h table/symbol.c table/symbol.h table/util.c table/util.h sintatico/AnalisadorSintaticoMain.cpp lexico/AnalisadorLexico.cpp lexico/AnalisadorLexico.h lexico/separador.cpp lexico/separador.h lexico/definidorToken.cpp lexico/definidorToken.h lexico/leitorValorToken.cpp lexico/leitorValorToken.h sintatico/AnalisadorSintaticoMain.h lexico/contagem.cpp lexico/contagem.h sintatico/No.h geradordecodigo/Gerador.cpp geradordecodigo/Gerador.h table/types.c table/types.h semantico/AnalisadorSemantico.cpp semantico/AnalisadorSemantico.h)
add_executable(AlgolCompiler ${SOURCE_FILES})