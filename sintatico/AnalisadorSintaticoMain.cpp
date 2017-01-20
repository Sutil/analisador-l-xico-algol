#include "../lexico/AnalisadorLexico.h"
#include "../terminais.h"
#include "AnalisadorSintaticoMain.h"
#include <regex>
#include <fstream>
#include "No.h"
#include "../geradordecodigo/Gerador.h"
#include "../semantico/AnalisadorSemantico.h"

No * raiz;
int distanciaPercorridaNoArquivo = 0;
int maiorDistancia = 0;
Token * tokenAtual;
Token * tokenMaiorProfundidade;

bool isAtribuicao(No *pai);

bool isDoisPontos(No *pai);

bool isFor(No *pai);

bool isDo(No *pai);

bool isStep(No *pai);

bool isUntil(No *pai);

bool isWhile(No *pai);

bool isElse(No *pai);

bool isAbreColchete(No *pai);

bool isFechaColchete(No * pai);

bool isVirgula(No *pai);

bool isSuperIgual(No *pai);

bool isOr(No *pai);

bool isAnd(No *pai);

bool isTrue(No *pai);

bool isFalse(No *pai);

bool isIf(No *pai);

bool isThen(No *pai);

bool isAbreParenteses(No *pai);

bool isFechaParenteses(No *pai);

bool isProcedure(No *pai);

bool isSwitch(No *pai);

bool isLabel(No *pai);

bool isArray(No *pai);

bool isString(No *pai);

bool isPontoEVirgula(No *pai);

bool isValue(No *pai);

bool isOwn(No *pai);

bool isBegin(No *pai);

bool isEnd(No *pai);

Token * getNextToken(){
    Token * token = getToken();
    tokenAtual = token;
    return token;
}

int main(int argc, char* argv[]) {

    std::cout << "Iniciado, analisador sintatico!" << std::endl;

    if(argc != 2){
        std::cout << "Informe endereco do arquivo fonte por parametro." << std::endl;
        return false;
    }


    FILE * f = fopen(argv[1], "rt");
    if(!f){
        std::cout << "Erro ao abrir arquivo." << std::endl;
        return false;
    }

    inicializaAnalizadorLexico(f);

    bool ret = program(); // Verificar se chegou no final do arquivo!!
    if(ret && getNextToken()->valor.compare("EOF") == 0) {
        std::ofstream arvore;
        arvore.open("arvore_sintatica.ast");
        arvore << endl << "Árvore de análise sintática: " << endl;
        arvore << "{";
        raiz->imprimir(arvore);
        arvore << "}" << endl;
        arvore << "SUCESSO" << endl;
        arvore.close();

        aliseSemantica(raiz);

        gerador(raiz, argv[1]);
        return true;
    }
    cout << endl << "Falha de análise sintática" << endl;

    cout << "Próximo ao token: " << tokenMaiorProfundidade->valor << endl;
    cout << "token identificado como: " << tokenMaiorProfundidade->nome << endl;
    cout << "Na linha: " << tokenMaiorProfundidade->linha << endl;
    cout << "Na coluna: " << tokenMaiorProfundidade->coluna << endl;

    return false;
}


No * addNo(No * pai, string filho){
    No * f = new No(filho);
    pai->addFilho(f);

    return f;
}

void removeNo(No * pai, No * filho){
    pai->removeFilho(filho);
    if(distanciaPercorridaNoArquivo >= maiorDistancia){
        maiorDistancia = distanciaPercorridaNoArquivo;
        if(tokenAtual != NULL) {
            tokenMaiorProfundidade = new Token(
                    tokenAtual->valor,
                    tokenAtual->nome,
                    tokenAtual->linha,
                    tokenAtual->coluna);
        }
    }

    distanciaPercorridaNoArquivo--;
}

bool program() {
    raiz = new No("program");
    
    int j = 0;


    salvaEstado(&j);
    if (block(raiz))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (compoundStatement(raiz))
        return true;

    restauraEstado(j);

    return false;
}

bool block(No * pai) {
	No * self = addNo(pai, "block");
    
    int j = 0;

    salvaEstado(&j);
    if (unlabelledBlock(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (label(self) && isDoisPontos(self) && block(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool statement(No * pai) {
	No * self = addNo(pai, "statment");
    
    int j = 0;

    salvaEstado(&j);
    if (unconditionalStatement(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);

    self = addNo(pai, "statment");
    salvaEstado(&j);
    if (conditionalStatement(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);

    self = addNo(pai, "statment");
    salvaEstado(&j);
    if (forStatement(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool forStatement(No * pai) {
	No * self = addNo(pai, "for statement");

    int j = 0;
    salvaEstado(&j);
    if (forClause(self) &&  statement(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (label(self) && forStatement(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool forClause(No * pai) {
	No * self = addNo(pai, "for clause");

    int j = 0;

    salvaEstado(&j);
    if (isFor(self) &&
        variable(self)
        && isAtribuicao(self)
        && forList(self)
        && isDo(self))
        return true;

    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool forList(No * pai) {
	No * self = addNo(pai, "for list");

    
    
    int j = 0;

    salvaEstado(&j);
    if (forListElement(self))
        return true;

    restauraEstado(j);
    removeNo(pai, self);
    return false;
}

bool forListElement(No * pai) {
	No * self = addNo(pai, "forListElement");

    int j = 0;

    salvaEstado(&j);

    if (arithmeticExpression(self)
        && isStep(self)
        && arithmeticExpression(self)
        && isUntil(self)
        && arithmeticExpression(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (arithmeticExpression(self)
        && isWhile(self)
        && booleanExpression(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (arithmeticExpression(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool unconditionalStatement(No * pai){
    No * self = addNo(pai, "unconditional statment");
    
    int j = 0;

    salvaEstado(&j);
    if (basicStatement(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (conditionalStatement(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (block(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool conditionalStatement(No * pai) {
	No * self = addNo(pai, "conditinal statement");

    int j = 0;

    salvaEstado(&j);
    if (ifStatement(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (ifStatement(self) && isElse(self) && statement(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (ifClause(self) && forStatement(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (label(self) && isDoisPontos(self) && conditionalStatement(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool ifStatement(No * pai) {
	No * self = addNo(pai, "if statement");
    
    int j = 0;

    salvaEstado(&j);
    if (ifClause(self) && unconditionalStatement(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool basicStatement(No * pai) {
	No * self = addNo(pai, "basic statement");

    
    int j = 0;

    salvaEstado(&j);
    if (unlabelledBasicStatement(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (label(self) 
        && isDoisPontos(self)
        && basicStatement(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool unlabelledBasicStatement(No * pai) {
	No * self = addNo(pai, "unlabelled basic statement");
    
    int j = 0;

    salvaEstado(&j);
    if (assignmentStatement(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (goToStatement(self))
        return true;
    restauraEstado(j);

//    if (dummyStatement())
//        return true;
//    restauraEstado(j);

    salvaEstado(&j);
    if (procedureStatement(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool procedureStatement(No * pai){
    No * self = addNo(pai, "procedure statement");
    
    int j = 0;

    salvaEstado(&j);
    if (procedureIdentifier(self) && actualParameterPart(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool dummyStatement(No * pai) {

    return true;
}

bool goToStatement(No * pai) {
    // implementar
    return false;
}

bool assignmentStatement(No * pai) {
	No * self = addNo(pai, "assignment statement");

    int j = 0;

    salvaEstado(&j);
    if (leftPartList(self) && arithmeticExpression(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);

    self = addNo(pai, "assignment statement");
    salvaEstado(&j);
    if (leftPartList(self) && booleanExpression(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool leftPartList(No * pai) {
    No * self = addNo(pai, "left part list");

    int j = 0;

    salvaEstado(&j);
    if (leftPart(self) && leftPartListRecursao(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool leftPartListRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (leftPart(pai) && leftPartListRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool leftPart(No * pai) {
	No * self = addNo(pai, "left part");

    int j = 0;

    salvaEstado(&j);
    if (variable(self) && isAtribuicao(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);

    self = addNo(pai, "left part");
    salvaEstado(&j);
    if (procedureIdentifier(self) && isAtribuicao(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool variable(No * pai) {
	No * self = addNo(pai, "variable");

    int j = 0;

    salvaEstado(&j);

    if (subscriptedVariable(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (simpleVariable(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool subscriptedVariable(No * pai) {
	No * self = addNo(pai, "subscripted variable");

    int j = 0;

    salvaEstado(&j);
    if (arrayIdentifier(self) && isAbreColchete(self) && subscriptList(self) && isFechaColchete(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool subscriptList(No * pai) {
    No * self = addNo(pai, "subscript list");
    int j = 0;

    salvaEstado(&j);
    if (subscriptExpression(self) && subscriptListRecursao(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool subscriptExpression(No * pai) {
    No * self = addNo(pai, "subscript expression");
    int j = 0;

    salvaEstado(&j);
    if (arithmeticExpression(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool subscriptListRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (isVirgula(pai) && subscriptExpression(pai) && subscriptListRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool arrayIdentifier(No * pai) {
    No * self = addNo(pai, "array identifier");
    
    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getNextToken(), self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool booleanExpression(No * pai) {
    No * self = addNo(pai, "boolena expression");
    int j = 0;

    salvaEstado(&j);
    if (simpleBoolean(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (ifClause(self) && simpleBoolean(self) && isElse(self) && booleanExpression(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool simpleBoolean(No * pai) {
    No * self = addNo(pai, "simple boolean");
    int j = 0;

    salvaEstado(&j);
    if (implication(self) && simpleBooleanRecursao(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool simpleBooleanRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (isSuperIgual(pai) && implication(pai) && simpleBooleanRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool implication(No * pai) {
    No * self = addNo(pai, "implication");
    
    int j = 0;

    salvaEstado(&j);
    if (booleanTerm(self) && implicationRecursao(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return false;
}

bool implicationRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("naosei") && booleanTerm(pai) && implicationRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool booleanTerm(No * pai) {
    No * self = addNo(pai, "boolean term");
    int j = 0;

    salvaEstado(&j);
    if (booleanFactor(self) && booleanTermRecursao(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool booleanTermRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (isOr(pai) && booleanFactor(pai) && booleanTermRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool booleanFactor(No * pai) {
	No * self = addNo(pai, "boolean factor");

    int j = 0;

    salvaEstado(&j);
    if (booleanSecondary(self) && booleanFactorRecursao(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool booleanFactorRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (isAnd(pai) && booleanSecondary(pai) && booleanFactorRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool booleanSecondary(No * pai) {
	No * self = addNo(pai, "boolena secondary");

    int j = 0;

    salvaEstado(&j);
    if (booleanPrimary(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("¬") && booleanPrimary(self))
        return true;

    restauraEstado(j);
    removeNo (pai, self);
	return false;
}

bool booleanPrimary(No * pai) {
	No * self = addNo(pai, "boolena primary");

    int j = 0;

    salvaEstado(&j);
    if (logicalValue(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (variable(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (functionDesignator(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool logicalValue(No * pai) {
	No * self = addNo(pai, "logical value");

    int j = 0;

    salvaEstado(&j);

    if (isTrue(self) || isFalse(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (relation(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool relation(No * pai) {
	No * self = addNo(pai, "relation");

    int j = 0;

    salvaEstado(&j);
    if (simpleArithmeticExpression(self) && relationalOperator(self) && simpleArithmeticExpression(self))
        return true;
    restauraEstado(j);


    removeNo (pai, self);
	return false;
}

bool relationalOperator(No * pai) {
	No * self = addNo(pai, "relational operator");

    int j = 0;

    salvaEstado(&j);
    std::string token = getNextToken()->valor;

    No * n = addNo(self, token);
    if (0 == token.compare("<") || 0 == token.compare("<=") || 0 == token.compare("=") || 0 == token.compare("#") || 0 == token.compare(">") || 0 == token.compare(">="))
        return true;
    removeNo(self, n);

    restauraPonteiro(j);
    removeNo (pai, self);
	return false;
}

bool arithmeticExpression(No * pai) {
	No * self = addNo(pai, "arithmetc expression");

    int j = 0;

    salvaEstado(&j);
    if (simpleArithmeticExpression(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (ifClause(self) && simpleArithmeticExpression(self) && isElse(self) && arithmeticExpression(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool ifClause(No * pai) {
	No * self = addNo(pai, "if clausure");

    int j = 0;

    salvaEstado(&j);
    if (isIf(self) && booleanExpression(self) && isThen(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool simpleArithmeticExpression(No * pai) {
	No * self = addNo(pai, "simple arithmetc expression");

    int j = 0;

    salvaEstado(&j);
    if (term(self) && simpleArithmeticExpressionRecursao(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (addingOperator(self) && term(self) && simpleArithmeticExpressionRecursao(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool simpleArithmeticExpressionRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (addingOperator(pai) && term(pai) && simpleArithmeticExpressionRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool addingOperator(No * pai) {
	No * self = addNo(pai, "adding operator");

    int j = 0;

    salvaEstado(&j);
    std::string t = getNextToken()->valor;

    No * n = addNo(self, t);
    if (t.compare(ARITHMETIOPERATOR_MAIS) == 0 || t.compare(ARITHMETIOPERATOR_MENOS) == 0)
        return true;
    removeNo(self, n);
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool term(No * pai) {
	No * self = addNo(pai, "term");

    int j = 0;

    salvaEstado(&j);
    if (primary(self) && termRecursao(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool termRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (multiplyingOperator(pai) && primary(pai) && termRecursao(pai))
        return true;
    restauraEstado(j);
    removeNo(pai, pai);
    return true;
}

bool primary(No * pai) {
	No * self = addNo(pai, "primary");

    int j = 0;

    salvaEstado(&j);
    if (unsignedNumber(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (variable(self))
        return true;
    restauraEstado(j);

    //if (fu)
    // implementar

    salvaEstado(&j);
    if (isAbreParenteses(self) && arithmeticExpression(self) && isFechaParenteses(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool functionDesignator(No * pai) {
	No * self = addNo(pai, "function designator");

    int j = 0;

    salvaEstado(&j);
    if (procedureIdentifier(self) && actualParameterPart(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool actualParameterPart(No * pai) {
	No * self = addNo(pai, "actual parameter part");

    int j = 0;

    salvaEstado(&j);

    if (isAbreParenteses(self) && actualParameterList(self) && isFechaParenteses(self))
        return true;

    restauraEstado(j);
    removeNo (pai, self);
	return false;
}

bool actualParameterList(No * pai) {
	No * self = addNo(pai, "actual parameter list");

    int j = 0;

    salvaEstado(&j);

    if (actualParameter(self) && actualParameterListRecursao(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool actualParameterListRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (parameterDelimiter(pai) && actualParameter(pai) && actualParameterListRecursao(pai))
        return true;
    restauraEstado(j);
    return true;
}

bool actualParameter(No * pai) {
	No * self = addNo(pai, "actual parameter");

    int j = 0;

    salvaEstado(&j);
    if (expression(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (token_isString(getNextToken(), self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool expression(No * pai) {
	No * self = addNo(pai, "expression");

    int j = 0;

    salvaEstado(&j);
    if (arithmeticExpression(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (booleanExpression(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (designationalExpression(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool designationalExpression(No * pai) {
    int j = 0;

    //implementar
    return false;
}

bool unsignedNumber(No * pai) {
	No * self = addNo(pai, "unsigned number");

    int j = 0;

    salvaEstado(&j);

    if (decimalNumber(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool decimalNumber(No * pai) {
	No * self = addNo(pai, "decimal number");

    int j = 0;

    salvaEstado(&j);
    if (token_isNumber(getNextToken(), self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool multiplyingOperator(No * pai) {
	No * self = addNo(pai, "multiplying operator");

    int j = 0;

    salvaEstado(&j);
    std::string op = getNextToken()->valor;

    No * n = addNo(self, op);
    if (op.compare(ARITHMETIOPERATOR_VEZES) == 0 || op.compare(ARITHMETIOPERATOR_DIVIDIR) == 0)
        return true;
    removeNo(self, n);
    restauraEstado(j);


    removeNo (pai, self);
	return false;
}

bool unlabelledBlock(No * pai) {
	No * self = addNo(pai, "unlabelled block");

    int j = 0;

    salvaEstado(&j);
    if (blockHead(self) &&
            isPontoEVirgula(self) &&
            compoundTail(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool compoundTail(No * pai) {
	No * self = addNo(pai, "compund tail");

    int j = 0;

    salvaEstado(&j);
    if (statement(self)) {
        if (isEnd(self)) {
            return true;
        }
    }
    restauraEstado(j);
    removeNo(pai, self);

    self = addNo(pai, "compund tail");
    salvaEstado(&j);
    if (statement(self) && isPontoEVirgula(self) && compoundTail(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool compoundStatement(No * pai) {
	No * self = addNo(pai, "compaund statement");

    int j = 0;

    salvaEstado(&j);
    if (unlabelledCompound(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);

    self = addNo(pai, "compaund statement");
    salvaEstado(&j);
    if (label(self) && isDoisPontos(self) && compoundStatement(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}


bool blockHead(No * pai) {
	No * self = addNo(pai, "block head");

    int j = 0;

    salvaEstado(&j);
    if (isBegin(self) && declaration(self) && blockHeadRecursao(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool blockHeadRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (isPontoEVirgula(pai) && declaration(pai) && blockHeadRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool unlabelledCompound(No * pai) {
	No * self = addNo(pai, "unlabelled compound");

    int j = 0;

    salvaEstado(&j);
    if (isBegin(self) && compoundTail(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool declaration(No * pai) {
	No * self = addNo(pai, "declaration");


    int j = 0;

    salvaEstado(&j);
    if (typeDeclaration(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (arrayDeclaration(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (procedureDeclaration(self))
        return true;

    restauraEstado(j);
    removeNo (pai, self);
	return false;
}

bool typeDeclaration(No * pai) {
	No * self = addNo(pai, "type declaration");

    int j = 0;

    salvaEstado(&j);
    if (localOrOwnType(self) && typeList(self))
        return true;

    restauraEstado(j);
	removeNo (pai, self);
	return false;
}
bool localOrOwnType(No * pai) {
	No * self = addNo(pai, "local or own type");

    int j = 0;

    salvaEstado(&j);
    if (type(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);

    self = addNo(pai, "local or own type");
    salvaEstado(&j);
    if (isOwn(self) && type(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool type(No * pai) {
	No * self = addNo(pai, "type");

    int j = 0;

    salvaEstado(&j);
    std::string token = getNextToken()->valor;

    No * n = addNo(self, token);
    if (0 == token.compare("real") || 0 == token.compare("integer") || 0 == token.compare("boolean"))
        return true;
    removeNo(self, n);

    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool typeList(No * pai) {
	No * self = addNo(pai, "type list");

    int j = 0;

    salvaEstado(&j);

    if (simpleVariable(self) && typeListRecursao(self))
        return true;
    restauraEstado(j);

	removeNo (pai, self);
	return false;
}

bool typeListRecursao(No * pai){
    int j = 0;

    salvaEstado(&j);
    if (isVirgula(pai) && simpleVariable(pai) && typeListRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool simpleVariable(No * pai) {
	No * self = addNo(pai, "simple variable");

    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getNextToken(), self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool arrayDeclaration(No * pai) {
	No * self = addNo(pai, "array declaration");

    int j = 0;

    salvaEstado(&j);
    if (isArray(self) && arrayList(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);

    self = addNo(pai, "array declaration");
    salvaEstado(&j);
    if (localOrOwnType(self) && isArray(self) && arrayList(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool arrayList(No * pai) {
	No * self = addNo(pai, "array list");

    int j = 0;

    salvaEstado(&j);
    if (arraySegment(self) && arrayListRecursao(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool arrayListRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (isVirgula(pai) && arraySegment(pai) && arrayListRecursao(pai))
        return true;
    restauraEstado(j);
    return true;
}


bool arraySegment(No * pai) {
	No * self = addNo(pai, "array segment");

    int j = 0;

    salvaEstado(&j);

    if (arrayIdentifier(self) && isAbreColchete(self) && boundPairList(self) && isFechaColchete(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (arrayIdentifier(self) && isVirgula(self) && arraySegment(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool boundPairList(No * pai) {
	No * self = addNo(pai, "bound pair list");

    int j = 0;

    salvaEstado(&j);
    if (boundPair(self) && boundPairListRecursao(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool boundPairListRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (isVirgula(pai) && boundPair(pai) && boundPairListRecursao(pai))
        return true;

    restauraEstado(j);
    return true;
}

bool boundPair(No * pai) {
	No * self = addNo(pai, "bound pair");

    int j = 0;

    salvaEstado(&j);
    if (lowerBound(self) && isDoisPontos(self) && upperBound(self))
        return true;

    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool lowerBound(No * pai) {
	No * self = addNo(pai, "lower bound");

    int j = 0;

    salvaEstado(&j);
    if (arithmeticExpression(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool upperBound(No * pai) {
	No * self = addNo(pai, "upper bound");

    int j = 0;

    salvaEstado(&j);
    if (arithmeticExpression(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool procedureDeclaration(No * pai) {
	No * self = addNo(pai, "procedure declaratin");

    int j = 0;

    salvaEstado(&j);
    if (isProcedure(self) && procedureHeading(self) && procedureBody(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (type(self) && isProcedure(self) && procedureHeading(self) && procedureBody(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool procedureHeading(No * pai) {
	No * self = addNo(pai, "procedure headin");

    int j = 0;

    salvaEstado(&j);
    if (procedureIdentifier(self)) {
        if (formalParameterPart(self)) {
            if (isPontoEVirgula(self)) {
                if (valuePart(self) && specificationPart(self))
                    return true;
            }
        }
    }
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool valuePart(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (isValue(pai) && identifierList(pai) && isPontoEVirgula(pai))
        return true;
    restauraEstado(j);
    return true;
}

bool specificationPart(No * pai) {
	No * self = addNo(pai, "specification part");

    int j = 0;

    salvaEstado(&j);
    if (specifier(self) && identifierList(self) && isPontoEVirgula(self) && specificationPart(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (specifier(self) && identifierList(self) && specificationPart(self))
        return true;

    restauraEstado(j);
    removeNo(pai, self);
    return true;
}

bool specifier(No * pai) {
	No * self = addNo(pai, "specifier");

    int j = 0;

    salvaEstado(&j);
    if (isString(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (isArray(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (type(self) && isArray(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (isLabel(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (isSwitch(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (isProcedure(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (type(self) && isProcedure(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (type(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool identifierList(No * pai) {
	No * self = addNo(pai, "identifier list");

    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getNextToken(), self) && identifierListRecursao(self))
        return true;

    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool identifierListRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (isVirgula(pai) && token_isIdentifier(getNextToken(), pai) && identifierListRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool procedureIdentifier(No * pai) {
	No * self = addNo(pai, "procedure identifier");

    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getNextToken(), self))
        return true;

    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool formalParameterPart(No * pai) {
	No * self = addNo(pai, "formal parameter part");
    int j = 0;

    salvaEstado(&j);

    if (isAbreParenteses(self) && formalParameterList(self) && isFechaParenteses(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);
    return true;
}

bool formalParameterList(No * pai) {
	No * self = addNo(pai, "formal parameter list");

    int j = 0;

    salvaEstado(&j);
    if (formalParameter(self) && formalParameterListRecursao(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool formalParameterListRecursao(No * pai) {
    int j = 0;

    salvaEstado(&j);
    if (parameterDelimiter(pai) && formalParameter(pai) && formalParameterListRecursao(pai))
        return true;
    restauraEstado(j);

    return true;
}

bool parameterDelimiter(No * pai) {
	No * self = addNo(pai, "parameter delimiter");

    int j = 0;

    salvaEstado(&j);
    if (isVirgula(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (isFechaParenteses(self) && token_isLetterString(getNextToken()->valor, self) && isDoisPontos(self) && isAbreParenteses(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool token_isLetterString(std::string token, No * pai){
    regex regex_id("[a-zA-Z]");

    No * self = addNo(pai, token);

    if(regex_match(token, regex_id))
        return true;

    removeNo(pai, self);
    return false;
}

bool formalParameter(No * pai) {
	No * self = addNo(pai, "formal parameter");

    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getNextToken(), self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool procedureBody(No * pai) {
	No * self = addNo(pai, "procedure body");

    int j = 0;

    salvaEstado(&j);
    if (statement(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool label(No * pai) {
	No * self = addNo(pai, "label");

    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getNextToken(), self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (unsignedInteger(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool unsignedInteger(No * pai) {
	No * self = addNo(pai, "unsigned integer");

    int j = 0;

    salvaEstado(&j);
    if (token_isNumber(getNextToken(), self))
        return true;

    restauraEstado(j);
    removeNo (pai, self);
    return false;
}

void salvaEstado(int *j) {
    *j = retornaPonteiroAtual();
    distanciaPercorridaNoArquivo = *j;
    return;
}

void restauraEstado(int j) {
    restauraPonteiro(j);
    return;
}

// terminais

bool isTerminal(No * pai, string esperado, Token * atual){
    No * self = addNo(pai, atual->valor);
    if(esperado.compare(atual->nome) == 0)
        return true;

    removeNo(pai, self);
    return false;
}

bool isTerminal(No * pai, string esperado, string atual){
    No * self = addNo(pai, atual);
    if(esperado.compare(atual) == 0)
        return true;

    removeNo(pai, self);
    return false;
}

bool token_isIdentifier(Token *token, No *pai) {
    return isTerminal(pai, "identifier", token);
}

bool token_isNumber(Token *token, No *pai) {
    return isTerminal(pai, "NUM", token);
}

bool token_isString(Token *token, No *pai) {
    No * self = addNo(pai, "open string");
    return isTerminal(self, "string", token);
}

bool isAtribuicao(No *pai) {
    return isTerminal(pai, ":=", getNextToken()->valor);
}

bool isDoisPontos(No *pai) {
    return  isTerminal(pai, ":", getNextToken()->valor);
}

bool isFor(No *pai) {
    return isTerminal(pai, "for", getNextToken()->valor);
}

bool isDo(No *pai) { 
    return isTerminal(pai, "do", getNextToken()->valor);
}

bool isWhile(No *pai) {
	return isTerminal(pai, "while", getNextToken()->valor);
}

bool isUntil(No *pai) {
	return isTerminal(pai, "until", getNextToken()->valor);
}

bool isStep(No *pai) {
	return isTerminal(pai, "step", getNextToken()->valor);
}

bool isElse(No *pai) {
	return isTerminal(pai, "else", getNextToken()->valor);
}

bool isFechaColchete(No * pai) {
    return isTerminal(pai, "]", getNextToken()->valor);
}

bool isAbreColchete(No *pai) {
	return isTerminal(pai, "[", getNextToken()->valor);
}

bool isVirgula(No *pai) {
    return getToken()->valor.compare(",") == 0;
}

bool isSuperIgual(No *pai) {
	return isTerminal(pai, "===", getNextToken()->valor);
}

bool isOr(No *pai) {
	return isTerminal(pai, "or", getNextToken()->valor);
}

bool isAnd(No *pai) {
	return isTerminal(pai, "and", getNextToken()->valor);
}

bool isFalse(No *pai) {
    return isTerminal(pai, "false", getNextToken()->valor);
}

bool isTrue(No *pai) {
    return isTerminal(pai, "true", getNextToken()->valor);
}

bool isThen(No *pai) {
	return isTerminal(pai, "then", getNextToken()->valor);
}

bool isIf(No *pai) {
	return isTerminal(pai, "if", getNextToken()->valor);
}

bool isFechaParenteses(No *pai) {
	return isTerminal(pai, ")", getNextToken()->valor);
}

bool isAbreParenteses(No *pai) {
	return isTerminal(pai, "(", getNextToken()->valor);
}

bool isString(No *pai) {
	return isTerminal(pai, "string", getNextToken()->valor);
}

bool isArray(No *pai) {
	return isTerminal(pai, "array", getNextToken()->valor);
}

bool isLabel(No *pai) {
	return isTerminal(pai, "label", getNextToken()->valor);
}

bool isSwitch(No *pai) {
	return isTerminal(pai, "switch", getNextToken()->valor);
}

bool isProcedure(No *pai) {
	return isTerminal(pai, "procedure", getNextToken()->valor);
}

bool isValue(No *pai) {
	return isTerminal(pai, "value", getNextToken()->valor);
}

bool isPontoEVirgula(No *pai) {
	return isTerminal(pai, ";", getNextToken()->valor);
}

bool isOwn(No *pai) {
	return isTerminal(pai, "own", getNextToken()->valor);
}

bool isBegin(No *pai) {
	return isTerminal(pai, "begin", getNextToken()->valor);
}

bool isEnd(No *pai) {
	return isTerminal(pai, "end", getNextToken()->valor);
}

