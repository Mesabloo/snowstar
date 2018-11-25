
// Generated from SnowStarParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "SnowStarParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by SnowStarParser.
 */
class  SnowStarParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by SnowStarParser.
   */
    virtual antlrcpp::Any visitCompilationUnit(SnowStarParser::CompilationUnitContext *context) = 0;

    virtual antlrcpp::Any visitDeclarationSeq(SnowStarParser::DeclarationSeqContext *context) = 0;

    virtual antlrcpp::Any visitVariableDeclaration(SnowStarParser::VariableDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitVariableName(SnowStarParser::VariableNameContext *context) = 0;

    virtual antlrcpp::Any visitVariableInitializer(SnowStarParser::VariableInitializerContext *context) = 0;

    virtual antlrcpp::Any visitUnitDeclaration(SnowStarParser::UnitDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitUnitName(SnowStarParser::UnitNameContext *context) = 0;

    virtual antlrcpp::Any visitBasicBlockDeclaration(SnowStarParser::BasicBlockDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitDtypeDeclaration(SnowStarParser::DtypeDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitDtypeName(SnowStarParser::DtypeNameContext *context) = 0;

    virtual antlrcpp::Any visitDtypeBlockDeclaration(SnowStarParser::DtypeBlockDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDeclaration(SnowStarParser::FunctionDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitFunctionHeader(SnowStarParser::FunctionHeaderContext *context) = 0;

    virtual antlrcpp::Any visitFunctionParamsTypes(SnowStarParser::FunctionParamsTypesContext *context) = 0;

    virtual antlrcpp::Any visitFunctionName(SnowStarParser::FunctionNameContext *context) = 0;

    virtual antlrcpp::Any visitFunctionParams(SnowStarParser::FunctionParamsContext *context) = 0;

    virtual antlrcpp::Any visitParameterDeclaration(SnowStarParser::ParameterDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitWithDeclaration(SnowStarParser::WithDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitWithName(SnowStarParser::WithNameContext *context) = 0;

    virtual antlrcpp::Any visitImportDeclaration(SnowStarParser::ImportDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitImportName(SnowStarParser::ImportNameContext *context) = 0;

    virtual antlrcpp::Any visitReturnDeclaration(SnowStarParser::ReturnDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitEmptyDeclaration(SnowStarParser::EmptyDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitStatementSeq(SnowStarParser::StatementSeqContext *context) = 0;

    virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExpression(SnowStarParser::PrimaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitTheType(SnowStarParser::TheTypeContext *context) = 0;

    virtual antlrcpp::Any visitBuiltinTypes(SnowStarParser::BuiltinTypesContext *context) = 0;

    virtual antlrcpp::Any visitValue(SnowStarParser::ValueContext *context) = 0;


};

