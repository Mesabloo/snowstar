
// Generated from SnowStar.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "SnowStarVisitor.h"


/**
 * This class provides an empty implementation of SnowStarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SnowStarBaseVisitor : public SnowStarVisitor {
public:

  virtual antlrcpp::Any visitProgram(SnowStarParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValue(SnowStarParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclare(SnowStarParser::DeclareContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrint(SnowStarParser::PrintContext *ctx) override {
    return visitChildren(ctx);
  }


};

