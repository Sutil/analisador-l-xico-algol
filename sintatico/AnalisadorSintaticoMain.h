//
// Created by Lucas on 12/31/2016.
//

#ifndef PROJETOU_ANALISADORSINTATICOMAIN_H
#define PROJETOU_ANALISADORSINTATICOMAIN_H

#include "../lexico/AnalisadorLexico.h"
#include "No.h"

void salvaEstado(int *j);
void restauraEstado(int j);

bool program();
bool block(No * pai);
bool compoundStatement(No * pai);
bool statement(No * pai);
bool unlabelledBlock(No * pai);
bool label(No * pai);
bool blockHead(No * pai);
bool declaration(No * pai);
bool compoundTail(No * pai);
bool blockHeadRecursao(No * pai);
bool unlabelledCompound(No * pai);
bool typeDeclaration(No * pai);
bool localOrOwnType(No * pai);
bool type(No * pai);
bool typeList(No * pai);
bool typeListRecursao(No * pai);
bool simpleVariable(No * pai);
bool arrayDeclaration(No * pai);
bool upperBound(No * pai);
bool boundPairList(No * pai);
bool arrayList(No * pai);
bool procedureDeclaration(No * pai);
bool procedureHeading(No * pai);
bool procedureBody(No * pai);
bool procedureIdentifier(No * pai);
bool parameterDelimiter(No * pai);
bool formalParameter(No * pai);
bool formalParameterList(No * pai);
bool formalParameterListRecursao(No * pai);
bool formalParameterPart(No * pai);
bool identifierList(No * pai);
bool identifierListRecursao(No * pai);
bool valuePart(No * pai);
bool specificationPart(No * pai);
bool unconditionalStatement(No * pai);
bool conditionalStatement(No * pai);
bool lowerBound(No * pai);
bool basicStatement(No * pai);
bool unlabelledBasicStatement(No * pai);
bool forStatement(No * pai);
bool assignmentStatement(No * pai);
bool procedureStatement(No * pai);
bool goToStatement(No * pai);
bool dummyStatement(No * pai);
bool leftPartList(No * pai);
bool booleanExpression(No * pai);
bool arithmeticExpression(No * pai);
bool leftPart(No * pai);
bool boundPairListRecursao(No * pai);
bool leftPartListRecursao(No * pai);
bool variable(No * pai);
bool subscriptedVariable(No * pai);
bool arrayIdentifier(No * pai);
bool subscriptExpression(No * pai);
bool subscriptListRecursao(No * pai);
bool subscriptList(No * pai);
bool multiplyingOperator(No * pai);
bool term(No * pai);
bool termRecursao(No * pai);
bool decimalNumber(No * pai);
bool primary(No * pai);
bool unsignedNumber(No * pai);
bool actualParameterPart(No * pai);
bool actualParameterList(No * pai);
bool actualParameterListRecursao(No * pai);
bool actualParameter(No * pai);
bool expression(No * pai);
bool designationalExpression(No * pai);
bool simpleArithmeticExpression(No * pai);
bool ifClause(No * pai);
bool simpleBoolean(No * pai);
bool implication(No * pai);
bool arrayListRecursao(No * pai);
bool implicationRecursao(No * pai);
bool booleanTerm(No * pai);
bool booleanTermRecursao(No * pai);
bool booleanFactor(No * pai);
bool booleanPrimary(No * pai);
bool booleanSecondary(No * pai);
bool booleanFactorRecursao(No * pai);
bool logicalValue(No * pai);
bool functionDesignator(No * pai);
bool relation(No * pai);
bool relationalOperator(No * pai);
bool simpleBooleanRecursao(No * pai);
bool addingOperator(No * pai);
bool simpleArithmeticExpressionRecursao(No * pai);
bool ifStatement(No * pai);
bool forClause(No * pai);
bool forList(No * pai);
bool forListElement(No * pai);
bool arraySegment(No * pai);
bool boundPair(No * pai);
bool unsignedInteger(No * pai);
bool specifier(No * pai);
bool token_isLetterString(std::string token, No * pai);
bool token_isNumber(Token *token, No *pai);
bool token_isString(Token *token, No *pai);
bool token_isIdentifier(Token *token, No *pai);

#endif //PROJETOU_ANALISADORSINTATICOMAIN_H
