//
// Created by sutil on 16/12/16.
//


#include <gtest/gtest.h>

#include <fstream>
#include "../../lexico/AnalisadorLexico.h"
#include "abreArquivo.h"

using namespace std;


void assertToken(string valor, string nome, int linha, int coluna, Token* token){
    ASSERT_EQ(valor, token->valor);
    ASSERT_EQ(nome, token->nome);
    ASSERT_EQ(linha, token->linha);
    //ASSERT_EQ(coluna, token->coluna);
}

void assertProximoToken(string valor, string nome, int linha, int coluna){
    Token * token = getToken();
    ASSERT_EQ(valor, token->valor);
    ASSERT_EQ(nome, token->nome);
    ASSERT_EQ(linha, token->linha);
    //ASSERT_EQ(coluna, token->coluna);
}

void avancaTokens(int quantidade){
    for (int i = 0; i < quantidade; ++i) {
        getToken();
    }
}

TEST(Lexico, tipoVariavelValido){
    FILE * f = criaArquivo("integer");
    inicializaAnalizadorLexico(f);

    retornaPonteiroAtual();

    Token * token = getToken();
    assertToken("integer", "declarator", 1, 1, token);

    fclose(f);
    remove("test.txt");
}

TEST(Lexico, atribuicao){
    FILE * f = criaArquivo("integer saldo := 0;");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("integer", "declarator", 1, 1, token);

    token = getToken();
    assertToken("saldo", "identifier", 1, 9, token);

    token = getToken();
    assertToken(":=", "separator", 1, 15, token);

    token = getToken();
    assertToken("0", "NUM", 1, 18, token);

    token = getToken();
    assertToken(";", "separator", 1, 19, token);

    token = getToken();
    assertToken("EOF", "EOF", 2, 2, token);

    fclose(f);
    remove("test.txt");
}

TEST(Lexico, ignoraEspacosEmBranco){
    FILE * f = criaArquivo("a +  10  ");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("a", "identifier", 1, 1, token);

    token = getToken();
    assertToken("+", "arithmetic operator", 1, 3, token);

    token = getToken();
    assertToken("10", "NUM", 1, 6, token);

    fclose(f);
    remove("test.txt");
}

TEST(Lexico, declaracaoProcedure){
    FILE * f = criaArquivo("procedure multiMatriz(a, b)");
    inicializaAnalizadorLexico(f);

    Token * token = getToken();
    assertToken("procedure", "declarator", 1, 1, token);

    token = getToken();
    assertToken("multiMatriz", "identifier", 1, 11, token);

    token = getToken();
    assertToken("(", "bracket", 1, 22, token);

    token = getToken();
    assertToken("a", "identifier", 1, 23, token);

    token = getToken();
    assertToken(",", "separator", 1, 24, token);

    token = getToken();
    assertToken("b", "identifier", 1, 26, token);

    token = getToken();
    assertToken(")", "bracket", 1, 27, token);

    fclose(f);
    remove("test.txt");
}

TEST(Lexico, erroLexico){
    FILE * f = criaArquivo("1abc");
    inicializaAnalizadorLexico(f);

    try{
        getToken();
        ASSERT_EQ("Não deveria ter passado","");
    }
    catch (runtime_error){
        ASSERT_TRUE(true);
    }

    fclose(f);
    remove("test.txt");
}

/*
 * procedure multiMatriz(a, b, n, m)
    value n, m; array a, b, y; integer n, m;
begin
    integer i, j, k, somatorio, produto;
    i := k := j = 0;

    for i := 1 step 1 until n do
        for q := 1 step 1 until m do
        begin
            somatorio := 0;
            for k:= 1 step 1 until m
                begin
                    produto := a[i,k] * b[k, j];
                    somatorio := somatorio + produto;
                end
            r[i, j] := somatorio;
        end


end multiMatriz
 */

//criar um teste para fazer toda a análse deste programa.

TEST(Lexico, programaCompleto){
    FILE * f = criaArquivo("begin\n"
                                   "procedure multiMatriz(a, b, n, m)\n"
                                   "    value n, m; array a, b, r; integer n, m;\n"
                                   "begin\n"
                                   "    integer i, j, k, somatorio, produto;\n"
                                   "    i := k := j := 0;\n"
                                   "\n"
                                   "    for i := 1 step 1 until n do\n"
                                   "        for q := 1 step 1 until m do\n"
                                   "        begin\n"
                                   "            somatorio := 0;\n"
                                   "            for k:= 1 step 1 until m\n"
                                   "                begin\n"
                                   "                    produto := a[i,k] * b[k, j];\n"
                                   "                    somatorio := somatorio + produto;\n"
                                   "                end\n"
                                   "            r[i, j] := somatorio;\n"
                                   "        end\n"
                                   "\n"
                                   "\n"
                                   "end multiMatriz\n"
                                   "end");
    inicializaAnalizadorLexico(f);

    assertProximoToken("begin", "bracket", 1, 1);
    assertProximoToken("procedure", "declarator", 2, 1);
    assertProximoToken("multiMatriz", "identifier", 2, 11);
    assertProximoToken("(", "bracket", 2, 22);
    assertProximoToken("a", "identifier", 2, 23);
    assertProximoToken(",", "separator", 2, 24);
    assertProximoToken("b", "identifier", 2, 26);
    assertProximoToken(",", "separator", 2, 27);
    assertProximoToken("n", "identifier", 2, 29);
    assertProximoToken(",", "separator", 2, 30);
    assertProximoToken("m", "identifier", 2, 32);
    assertProximoToken(")", "bracket", 2, 33);
    assertProximoToken("value", "specificator", 3, 5);
    assertProximoToken("n", "identifier", 3, 11);
    assertProximoToken(",", "separator", 3, 12);
    assertProximoToken("m", "identifier", 3, 14);
    assertProximoToken(";", "separator", 3, 15);
    assertProximoToken("array", "declarator", 3, 17);
    assertProximoToken("a", "identifier", 3, 23);
    assertProximoToken(",", "separator", 3, 24);
    assertProximoToken("b", "identifier", 3, 26);
    assertProximoToken(",", "separator", 3, 27);
    assertProximoToken("r", "identifier", 3, 29);
    assertProximoToken(";", "separator", 3, 30);
    assertProximoToken("integer", "declarator", 3, 32);
    assertProximoToken("n", "identifier", 3, 40);
    assertProximoToken(",", "separator", 3, 41);
    assertProximoToken("m", "identifier", 3, 43);
    assertProximoToken(";", "separator", 3, 44);
    assertProximoToken("begin", "bracket", 4, 1);
    assertProximoToken("integer", "declarator", 5, 5);
    assertProximoToken("i", "identifier", 5, 13);
    assertProximoToken(",", "separator", 5, 14);
    assertProximoToken("j", "identifier", 5, 16);
    assertProximoToken(",", "separator", 5, 17);
    assertProximoToken("k", "identifier", 5, 19);
    assertProximoToken(",", "separator", 5, 20);
    assertProximoToken("somatorio", "identifier", 5, 22);
    assertProximoToken(",", "separator", 5, 31);
    assertProximoToken("produto", "identifier", 5, 33);
    assertProximoToken(";", "separator", 5, 40);
    assertProximoToken("i", "identifier", 6, 5);
    assertProximoToken(":=", "separator", 6, 7);
    assertProximoToken("k", "identifier", 6, 10);
    assertProximoToken(":=", "separator", 6, 12);
    assertProximoToken("j", "identifier", 6, 15);
    assertProximoToken(":=", "separator", 6, 17);
    assertProximoToken("0", "NUM", 6, 20);
    assertProximoToken(";", "separator", 6, 21);
    assertProximoToken("for", "sequential operator", 8, 5);
    assertProximoToken("i", "identifier", 8, 9);
    assertProximoToken(":=", "separator", 8, 11);
    assertProximoToken("1", "NUM", 8, 14);
    assertProximoToken("step", "separator", 8, 16);
    assertProximoToken("1", "NUM", 8, 21);
    assertProximoToken("until", "separator", 8, 23);
    assertProximoToken("n", "identifier", 8, 29);
    assertProximoToken("do", "sequential operator", 8, 31);


    fclose(f);
    remove("test.txt");
}

TEST(Lexico, declaracaoMatriz){
    FILE * f = criaArquivo("integer array a[1:2,1:2];");
    inicializaAnalizadorLexico(f);

    assertProximoToken("integer", "declarator", 1, 1);
    assertProximoToken("array", "declarator", 1, 9);
    assertProximoToken("a", "identifier", 1, 15);
    assertProximoToken("[", "bracket", 1, 16);
    assertProximoToken("1", "NUM", 1, 17);
    assertProximoToken(":", "separator", 1, 18);
    assertProximoToken("2", "NUM", 1, 19);
    assertProximoToken(",", "separator", 1, 20);
    assertProximoToken("1", "NUM", 1, 21);
    assertProximoToken(":", "separator", 1, 22);
    assertProximoToken("2", "NUM", 1, 23);
    assertProximoToken("]", "bracket", 1, 24);
    assertProximoToken(";", "separator", 1, 25);
    assertProximoToken("EOF", "EOF", 2, 2);

    fclose(f);
    remove("test.txt");

}

TEST(Lexico, multiplicacaoMatrizes){
    FILE * f = criaArquivo("begin\n"
                                   "procedure multiMatriz(a, b, n, m);\n"
                                   "    value n, m; integer array a, b, r; integer n, m;\n"
                                   "begin\n"
                                   "    integer i, j, k;\n"
                                   "    \n"
                                   "    i := k := j := 0;\n"
                                   "\n"
                                   "    for i := 1 step 1 until n do\n"
                                   "        for q := 1 step 1 until m do\n"
                                   "        begin\n"
                                   "            integer somatorio;\n"
                                   "            somatorio := 0;\n"
                                   "            for k:= 1 step 1 until m do\n"
                                   "                begin\n"
                                   "                    integer produto;\n"
                                   "                    produto := a[i,k] * b[k, j];\n"
                                   "                    somatorio := somatorio + produto\n"
                                   "                end;\n"
                                   "            r[i, j] := somatori\n"
                                   "         end\n"
                                   "end;\n"
                                   "integer array a[1:2,1:2], b[1:2,1:2];\n"
                                   "\n"
                                   "a[1,1] := 1;\n"
                                   "a[1,2] := 2;\n"
                                   "a[2,1] := 1;\n"
                                   "a[2,2] := 2;\n"
                                   "\n"
                                   "b[1,1] := 2;\n"
                                   "b[1,2] := 1;\n"
                                   "b[2,1] := 2;\n"
                                   "b[2,2] := 1;\n"
                                   "\n"
                                   "multiMatriz( a, b, 2, 2 )\n"
                                   "\n"
                                   "end");
    inicializaAnalizadorLexico(f);

    assertProximoToken("begin", "bracket", 1, 1);
    avancaTokens(30);
    assertProximoToken("begin", "bracket", 4, 1);
    avancaTokens(15);
    int ponteiro = retornaPonteiroAtual();
    assertProximoToken("for", "sequential operator", 9, 5);
    avancaTokens(96);
    assertProximoToken("a", "identifier", 25, 1);
    restauraPonteiro(ponteiro);

    assertProximoToken("for", "sequential operator", 9, 5);

    avancaTokens(17);
    ponteiro = retornaPonteiroAtual();
    assertProximoToken("begin", "bracket", 11, 9);
    avancaTokens(20);
    restauraPonteiro(ponteiro);
    assertProximoToken("begin", "bracket", 11, 9);

}


TEST(Lexico, strings){
    FILE * f = criaArquivo("string a := \"isso é uma string\";\nstring b := \" outra string !\"");
    inicializaAnalizadorLexico(f);

    avancaTokens(3);
    assertProximoToken("\"isso é uma string\"", "string", 1,30);

    avancaTokens(4);
    assertProximoToken("\" outra string !\"", "string", 2,57);


    fclose(f);
    remove("test.txt");
}