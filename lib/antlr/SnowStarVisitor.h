
// Generated from SnowStar.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "SnowStarParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by SnowStarParser.
 */
class  SnowStarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by SnowStarParser.
   */
    virtual antlrcpp::Any visitProgram(SnowStarParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitValue(SnowStarParser::ValueContext *context) = 0;

    virtual antlrcpp::Any visitDeclare(SnowStarParser::DeclareContext *context) = 0;

    virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext *context) = 0;

    virtual antlrcpp::Any visitCast(SnowStarParser::CastContext *context) = 0;

    virtual antlrcpp::Any visitMaths_expr(SnowStarParser::Maths_exprContext *context) = 0;


};

