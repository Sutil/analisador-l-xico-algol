//
// Created by sutil on 16/12/16.
//


#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include "../../lexico/AnalisadorLexico.h"

using namespace std;

FILE * criaEAbreArquivo(string conteudo){
    ofstream outfile ("test.txt");
    outfile << conteudo << endl;
    outfile.close();

    return fopen("test.txt", "rt");
}

void assertToken(string valor, string nome, int linha, int coluna, Token* token){
    ASSERT_EQ(valor, token->valor);
    ASSERT_EQ(nome, token->nome);
    ASSERT_EQ(linha, token->linha);
    ASSERT_EQ(coluna, token->coluna);
}

TEST(Lexico, tipoVariavelValido){
    FILE * f = criaEAbreArquivo("int");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("int", "TIPO", 1, 1, token);

    fclose(f);
    remove("test.txt");
}

TEST(Lexico, atribuicao){
    FILE * f = criaEAbreArquivo("int saldo := 0;");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("int", "TIPO", 1, 1, token);

    token = getToken();
    assertToken("saldo", "ID", 1, 5, token);

    token = getToken();
    assertToken(":=", "SIMBOLO", 1, 11, token);

    fclose(f);
    remove("test.txt");
}
