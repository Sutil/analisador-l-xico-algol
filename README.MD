**ALGOL COMPILER**

Trablho executado para a disciplina de Implementação de Linguagens do curso de Informática da UEM em 2016/2017.

O Projeto tem como objetivo a implementação das fases de Análise Léxica, Sintática e Semantica, também a Geração de Código Intermediário, utilizando LLVM. 

Projeto executado utilizando a linguagem C++11 e CMake (Mínimo 3.5), portanto, para compilar, basta utilizar `cmake .` na pasta do projeto e `make`. Tem como requisito a instação do clang.

O projeto gera um executável com nome `AlgolCompiler` e tem como entrada arquivos com extensão `.alg` e gera como resultado o arquivo com extensão `.alg.exec`. Também gera o arquivo com extensão `.alg.ll` com o código intermediário gerado.


_`Desenvolvedores: Eduardo Stuil e Lucas Martioli`_