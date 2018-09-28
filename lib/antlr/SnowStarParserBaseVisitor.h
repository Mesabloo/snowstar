
// Generated from SnowStarParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "SnowStarParserVisitor.h"


/**
 * This class provides an empty implementation of SnowStarParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SnowStarParserBaseVisitor : public SnowStarParserVisitor {
public:

  virtual antlrcpp::Any visitCompilationUnit(SnowStarParser::CompilationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclare(SnowStarParser::DeclareContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLiteral(SnowStarParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimitiveType(SnowStarParser::PrimitiveTypeContext *ctx) override {
    return visitChildren(ctx);
  }


};

