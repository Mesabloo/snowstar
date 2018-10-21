
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

    virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext *context) = 0;

    virtual antlrcpp::Any visitDeclare(SnowStarParser::DeclareContext *context) = 0;

    virtual antlrcpp::Any visitDeclareNoID(SnowStarParser::DeclareNoIDContext *context) = 0;

    virtual antlrcpp::Any visitLiteral(SnowStarParser::LiteralContext *context) = 0;

    virtual antlrcpp::Any visitType(SnowStarParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitError(SnowStarParser::ErrorContext *context) = 0;


};

