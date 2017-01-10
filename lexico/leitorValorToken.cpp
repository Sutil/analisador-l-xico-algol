//
// Created by sutil on 20/12/16.
//

#include <vector>
#include "leitorValorToken.h"
#include "contagem.h"

vector<char> SEQUENCIA_DOIS_PONTOS = {'='};

char caracter;

void inicializaLeitorToken() {
    inicializaContagem();
}

char leCaracter(FILE* file){
    caracter  = getc(file);
    avancaCaracter(caracter, file->_offset);

    return caracter;
}

bool isSequenciaValida(char caracter, char sequencia){
    if(caracter == ':')
        for (int i = 0; i < SEQUENCIA_DOIS_PONTOS.size() ; ++i) {
            if(SEQUENCIA_DOIS_PONTOS[i] == sequencia)
                return true;
        }

    return false;
}

void voltaPonteiro(FILE * file){
    //fseek(file, 0, file->_offset);
    fseek(file, -1, SEEK_CUR);
    retornaCaracter();
}

void descartarCaracteresEmBranco(FILE  * file){
    char caracter = leCaracter(file);
    if(isSeparadorDescartavel(caracter))
        while(isSeparadorDescartavel(caracter))
            caracter = leCaracter(file);

    if(EOF != caracter)
        voltaPonteiro(file);
}

string tokenEOF(FILE * file){
    char caracter = leCaracter(file);
    if(caracter == EOF)
        return "EOF";

    voltaPonteiro(file);
    return "";
}

string tokenQueContemSeparador(FILE * file){
    char caracter = leCaracter(file);
    if(isSeparadorComSequencia(caracter)) {
        char sequencia[3];
        sequencia[0] = caracter;
        char seguinte = leCaracter(file);
        if(isSequenciaValida(caracter, seguinte)){
            sequencia[1] = seguinte;
            sequencia[2] = '\0';
            string valor(sequencia);
            return valor;
        }
        voltaPonteiro(file);
        voltaPonteiro(file);
    } else{
        voltaPonteiro(file);
    }
    return "";
}

string tokenSimbolo(FILE * file){
    char caracter = leCaracter(file);
    if(isSeparadorNaoDescartavel(caracter)){
        char sequencia[2];
        sequencia[0] = caracter;
        sequencia[1] = '\0';
        string valor(sequencia);
        return valor;
    }
    voltaPonteiro(file);
    return "";
}

string tokenString(FILE * file){
    char caracter = leCaracter(file);
    if(caracter == '"'){
        char sequencia[50];
        int i = 0;
        sequencia[i] = caracter;
        i++;
        caracter = leCaracter(file);
        while (caracter != '"' && caracter != EOF){
            sequencia[i] = caracter;
            i++;
            caracter = leCaracter(file);
        }
        sequencia[i] = caracter;
        sequencia[i+1] = '\0';
        string valor(sequencia);
        return valor;
    }

    voltaPonteiro(file);
    return "";
}

string tokenSemSimbolo(FILE * file){
    char caracter = leCaracter(file);
    char sequencia[50];
    int i = 0;
    while (!isSeparador(caracter)){
        sequencia[i] = caracter;
        i++;
        caracter = leCaracter(file);
    }
    sequencia[i] = '\0';
    voltaPonteiro(file);
    string valor(sequencia);
    return valor;
}

ValorToken* getValorToken(FILE * file){
    descartarCaracteresEmBranco(file);

    string valor = tokenEOF(file);

    if(valor.empty())
        valor = tokenQueContemSeparador(file);

    if(valor.empty())
        valor = tokenSimbolo(file);

    if(valor.empty())
        valor = tokenString(file);

    if(valor.empty())
        valor = tokenSemSimbolo(file);

    Estado * estado = ultimoEstadoSalvo();

    return new ValorToken(valor, estado->linha, estado->coluna);
}

void salvarContagem(long ponteiro){
    salvaEstadoDaContagem(ponteiro);
}

void restaurarContagem(long ponteiroArquivo) {
    restauraContagem(ponteiroArquivo);
}
