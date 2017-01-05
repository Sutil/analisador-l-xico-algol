#include <iostream>
#include "../lexico/AnalisadorLexico.h"
#include "../terminais.h"
#include "AnalisadorSintaticoMain.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <regex>
#include "No.h"

No * raiz;
int profundidade = 0;
int maiorProfundidade = 0;
Token * tokenAtual;
Token * tokenMaiorProfundidade;

Token * getNextToken(){
    Token * token = getToken();
    tokenAtual = token;
    return token;
}

int main(int argc, char* argv[]) {
//    testing::InitGoogleTest(&argc, argv);
//    int resultTests = RUN_ALL_TESTS();
//    if(resultTests)
//        std::cout << "Testes falharam" << std::endl;

    std::cout << "Iniciado, analisador sintatico!" << std::endl;

    if(argc != 2){
        std::cout << "Informe endereço do arquivo fonte por parâmetro." << std::endl;
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
        cout << endl << "Árvore de análise sintática: " << endl;
        cout << "{";
        raiz->imprimir();
        cout << "}" << endl;
        cout << "SUCESSO" << endl;
        return true;
    }
    cout << endl << "Falha de análise sintática" << endl;

    cout << "Próximo ao token: " << tokenMaiorProfundidade->valor << endl;
    cout << "Na linha: " << tokenMaiorProfundidade->linha << endl;
    cout << "Na coluna: " << tokenMaiorProfundidade->coluna << endl;

    return false;
}


No * addNo(No * pai, string filho){
    No * f = new No(filho);
    pai->addFilho(f);

    profundidade++;
    return f;
}

void removeNo(No * pai, No * filho){
    pai->removeFilho(filho);
    if(profundidade >= maiorProfundidade){
        maiorProfundidade = profundidade;
        if(tokenAtual != NULL) {
            tokenMaiorProfundidade = new Token(
                    tokenAtual->valor,
                    tokenAtual->nome,
                    tokenAtual->linha,
                    tokenAtual->coluna);
        }
    }

    profundidade--;
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
    if (label(self) && 0 == getNextToken()->valor.compare(":") && block(self))
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

    salvaEstado(&j);
    if (conditionalStatement(self))
        return true;
    restauraEstado(j);

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
    if (0 == getNextToken()->valor.compare("for") &&
            variable(self)
            && 0 == getNextToken()->valor.compare(":=")
            && forList(self)
            && 0 == getNextToken()->valor.compare("do"))
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
        && 0 == getNextToken()->valor.compare("step")
        && arithmeticExpression(self)
        && 0 == getNextToken()->valor.compare("until")
        && arithmeticExpression(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (arithmeticExpression(self)
        && 0 == getNextToken()->valor.compare("while")
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
    if (ifStatement(self) && 0 == getNextToken()->valor.compare("else") && statement(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (ifClause(self) && forStatement(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (label(self) && 0 == getNextToken()->valor.compare(":") && conditionalStatement(self))
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
        && 0 == getNextToken()->valor.compare(":") 
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
	No * self = addNo(pai, "left part list recursao");

    int j = 0;

    salvaEstado(&j);
    if (leftPart(self) && leftPartListRecursao(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return true;
}

bool leftPart(No * pai) {
	No * self = addNo(pai, "left part");

    int j = 0;

    salvaEstado(&j);
    if (variable(self) && 0 == getNextToken()->valor.compare(":="))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (procedureIdentifier(self) && 0 == getNextToken()->valor.compare(":="))
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
    if (arrayIdentifier(self) && 0 == getNextToken()->valor.compare("[") && subscriptList(self) && 0 == getNextToken()->valor.compare("]"))
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
    No * self = addNo(pai, "subscript list recursao");
    
    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare(",") && subscriptExpression(self) && subscriptListRecursao(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return true;
}

bool arrayIdentifier(No * pai) {
    No * self = addNo(pai, "array identifier");
    
    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getNextToken()))
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
    if (ifClause(self) && simpleBoolean(self) && 0 == getNextToken()->valor.compare("else") && booleanExpression(self))
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
    No * self = addNo(pai, "simple boolean recursão");
    
    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("===") && implication(self) && simpleBooleanRecursao(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
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
    No * self = addNo(pai, "implication recursao");
    
    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("naosei") && booleanTerm(self) && implicationRecursao(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
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
	No * self = addNo(pai, "boolean term recursao");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("or") && booleanFactor(self) && booleanTermRecursao(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
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
	No * self = addNo(pai, "boolean factor recursao");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("and") && booleanSecondary(self) && booleanFactorRecursao(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);
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
    std::string t = getNextToken()->valor;

    if (t.compare(LOGICALVALUE_TRUE) == 0 || t.compare(LOGICALVALUE_FALSE) == 0)
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

    if (0 == token.compare("<") || 0 == token.compare("<=") || 0 == token.compare("=") || 0 == token.compare("#") || 0 == token.compare(">") || 0 == token.compare(">="))
        return true;

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
    if (ifClause(self) && simpleArithmeticExpression(self) && 0 == getNextToken()->valor.compare("else") && arithmeticExpression(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool ifClause(No * pai) {
	No * self = addNo(pai, "if clausure");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("if") && booleanExpression(self) && 0 == getNextToken()->valor.compare("then"))
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
	No * self = addNo(pai, "simple arithmetic expression recursao");

    int j = 0;

    salvaEstado(&j);
    if (addingOperator(self) && term(self) && simpleArithmeticExpressionRecursao(self))
        return true;
    restauraEstado(j);

    return true;
}

bool addingOperator(No * pai) {
	No * self = addNo(pai, "adding operator");

    int j = 0;

    salvaEstado(&j);
    std::string t = getNextToken()->valor;

    if (t.compare(ARITHMETIOPERATOR_MAIS) == 0 || t.compare(ARITHMETIOPERATOR_MENOS) == 0)
        return true;
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
	No * self = addNo(pai, "term recursao");

    int j = 0;

    salvaEstado(&j);
    if (multiplyingOperator(self) && primary(self) && termRecursao(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);
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
    if (0 == getNextToken()->valor.compare("(") && arithmeticExpression(self) && 0 == getNextToken()->valor.compare(")"))
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

    if (0 == getNextToken()->valor.compare("(") && actualParameterList(self) && 0 == getNextToken()->valor.compare(")"))
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
	No * self = addNo(pai, "actual parameter list recursao");

    int j = 0;

    salvaEstado(&j);
    if (parameterDelimiter(self) && actualParameter(self) && actualParameterListRecursao(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);
    return true;
}

bool actualParameter(No * pai) {
	No * self = addNo(pai, "actual parameter");

    int j = 0;

    salvaEstado(&j);
    if (token_isString(getNextToken()))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (expression(self))
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
    if (token_isNumber(getNextToken()))
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

    if (op.compare(ARITHMETIOPERATOR_VEZES) == 0 || op.compare(ARITHMETIOPERATOR_DIVIDIR) == 0)
        return true;
    restauraEstado(j);


    removeNo (pai, self);
	return false;
}

bool unlabelledBlock(No * pai) {
	No * self = addNo(pai, "unlabelled block");

    int j = 0;

    salvaEstado(&j);
    if (blockHead(self) &&
            0 == getNextToken()->valor.compare(";") &&
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
        if (0 == getNextToken()->valor.compare("end")) {
            return true;
        }
    }
    restauraEstado(j);

    salvaEstado(&j);
    if (statement(self) && 0 == getNextToken()->valor.compare(";") && compoundTail(self))
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

    salvaEstado(&j);
    if (label(self) && 0 == getNextToken()->valor.compare(":") && compoundStatement(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}


bool blockHead(No * pai) {
	No * self = addNo(pai, "block head");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("begin") && declaration(self) && blockHeadRecursao(self))
        return true;
    restauraEstado(j);

    removeNo (pai, self);
	return false;
}

bool blockHeadRecursao(No * pai) {
	No * self = addNo(pai, "block head  recursao");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare(";") && declaration(self) && blockHeadRecursao(self))
        return true;
    restauraEstado(j);

    removeNo(pai, self);
    return true;
}

bool unlabelledCompound(No * pai) {
	No * self = addNo(pai, "unlabelled compound");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("begin") && compoundTail(self))
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
	No * self = addNo(pai, "type definition");

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

    salvaEstado(&j);
    if (getNextToken()->valor.compare("own") == 0 && type(self))
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

    if (0 == token.compare("real") || 0 == token.compare("integer") || 0 == token.compare("boolean"))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool typeList(No * pai) {
	No * self = addNo(pai, "type list");

    int j = 0;

    salvaEstado(&j);
    if (simpleVariable(self) && 0 == getNextToken()->valor.compare(",") && typeList(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (simpleVariable(self))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool simpleVariable(No * pai) {
	No * self = addNo(pai, "simple variable");

    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getNextToken()))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool arrayDeclaration(No * pai) {
	No * self = addNo(pai, "array declaration");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("array") && arrayList(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (localOrOwnType(self) && 0 == getNextToken()->valor.compare("array") && arrayList(self))
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
	No * self = addNo(pai, "array list recursao");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare(",") && arraySegment(self) && arrayListRecursao(self))
        return true;
    restauraEstado(j);
    removeNo(pai, self);
    return true;
}


bool arraySegment(No * pai) {
	No * self = addNo(pai, "array segment");

    int j = 0;

    salvaEstado(&j);

    if (arrayIdentifier(self) && 0 == getNextToken()->valor.compare("[") && boundPairList(self) && 0 == getNextToken()->valor.compare("]"))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (arrayIdentifier(self) && 0 == getNextToken()->valor.compare(",") && arraySegment(self))
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
	No * self = addNo(pai, "bound pair list recursao");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare(",") && boundPair(self) && boundPairListRecursao(self))
        return true;

    restauraEstado(j);
    removeNo(pai, self);
    return true;
}

bool boundPair(No * pai) {
	No * self = addNo(pai, "bound pair");

    int j = 0;

    salvaEstado(&j);
    if (lowerBound(self) && 0 == getNextToken()->valor.compare(":") && upperBound(self))
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
    if (0 == getNextToken()->valor.compare("procedure") && procedureHeading(self) && procedureBody(self))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (type(self) && 0 == getNextToken()->valor.compare("procedure") && procedureHeading(self) && procedureBody(self))
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
            if (0 == getNextToken()->valor.compare(";")) {
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
	No * self = addNo(pai, "value part");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("value") && identifierList(self) && 0 == getNextToken()->valor.compare(";"))
        return true;
    restauraEstado(j);
    removeNo(pai, self);
    return true;
}

bool specificationPart(No * pai) {
	No * self = addNo(pai, "specification part");

    int j = 0;

    salvaEstado(&j);
    if (specifier(self) && identifierList(self) && 0 == getNextToken()->valor.compare(";") && specificationPart(self))
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
    if (0 == getNextToken()->valor.compare("string"))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("array"))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (type(self) && 0 == getNextToken()->valor.compare("array"))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("label"))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("switch"))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare("procedure"))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (type(self) && 0 == getNextToken()->valor.compare("procedure"))
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
    if (token_isIdentifier(getNextToken()) && identifierListRecursao(self))
        return true;

    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool identifierListRecursao(No * pai) {
	No * self = addNo(pai, "identifier list recursao");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare(",") && token_isIdentifier(getNextToken()) && identifierListRecursao(self))
        return true;
    restauraEstado(j);

    return true;
}

bool procedureIdentifier(No * pai) {
	No * self = addNo(pai, "procedure identifier");

    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getNextToken()))
        return true;

    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool formalParameterPart(No * pai) {
	No * self = addNo(pai, "formal parameter part");

    int j = 0;

    salvaEstado(&j);

    if (0 == getNextToken()->valor.compare("(") && formalParameterList(self) && 0 == getNextToken()->valor.compare(")"))
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
	No * self = addNo(pai, "forma parameter list recursao");

    int j = 0;

    salvaEstado(&j);
    if (parameterDelimiter(self) && formalParameter(self) && formalParameterListRecursao(self))
        return true;
    restauraEstado(j);

    return true;
}

bool parameterDelimiter(No * pai) {
	No * self = addNo(pai, "parameter delimiter");

    int j = 0;

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare(","))
        return true;
    restauraEstado(j);

    salvaEstado(&j);
    if (0 == getNextToken()->valor.compare(")") && token_isLetterString(getNextToken()->valor) && 0 == getNextToken()->valor.compare(":") && 0 == getNextToken()->valor.compare("("))
        return true;
    restauraEstado(j);
	removeNo (pai, self);
	return false;
}

bool token_isLetterString(std::string token){
    regex regex_id("[a-zA-Z]");

    return regex_match(token, regex_id);
}

bool formalParameter(No * pai) {
	No * self = addNo(pai, "formal parameter");

    int j = 0;

    salvaEstado(&j);
    if (token_isIdentifier(getNextToken()))
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
    if (token_isIdentifier(getNextToken()))
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
    if (token_isNumber(getNextToken()))
        return true;

    restauraEstado(j);
    removeNo (pai, self);
    return false;
}

void salvaEstado(int *j) {
    *j = retornaPonteiroAtual();
    return;
}

void restauraEstado(int j) {
    restauraPonteiro(j);
    return;
}

bool token_isIdentifier(Token * token) {
    return token->nome.compare("identifier") == 0;
}

bool token_isNumber(Token * token) {
    return token->nome.compare("NUM") == 0;
}

bool token_isString(Token * token) {
    return token->valor.compare("string") == 0;
}
