//
// Created by sutil on 16/12/16.
//

#include <sstream>
#include <stdexcept>
#include "AnalisadorLexico.h"
#include "separador.h"
#include "definidorToken.h"
#include "leitorValorToken.h"
#include "contagem.h"

FILE *file;

string definineTipoToken(string basic_string);

bool naoEhSeparador(char caracter);

void inicializaAnalizadorLexico(FILE *pFile) {
    file = pFile;
    inicializaLeitorToken();
}

ValorToken* leValorToken(){
    ValorToken * valorToken = getValorToken(file);
    return valorToken;
}

string definineTipoToken(string valorToken) {
    string tipoToken = getTipoToken(valorToken);
    return tipoToken;
}

Token * getToken() {

    ValorToken* valorToken = leValorToken();
    string tipoToken = definineTipoToken(valorToken->valor);

    if(tipoToken.compare("NADA") == 0){
        cout << "Erro léxico no token " << valorToken->valor << endl;
        cout << "Linha " << valorToken->linha << endl;
        cout << "Coluna " << valorToken->coluna << endl;
        throw runtime_error("Erro léxico");
    }

    Token * token = new Token(valorToken->valor, tipoToken, valorToken->linha, valorToken->coluna);

    return token;
}

long retornaPonteiroAtual(){
    long ponteiro = ftell(file);
    salvarContagem(ftell(file));
    return ponteiro;
}

void restauraPonteiro(int posicao){
    fseek(file, posicao, SEEK_SET);
    restaurarContagem(posicao);
}
