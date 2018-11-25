
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

  virtual antlrcpp::Any visitDeclarationSeq(SnowStarParser::DeclarationSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableDeclaration(SnowStarParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableName(SnowStarParser::VariableNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableInitializer(SnowStarParser::VariableInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnitDeclaration(SnowStarParser::UnitDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnitName(SnowStarParser::UnitNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBasicBlockDeclaration(SnowStarParser::BasicBlockDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDtypeDeclaration(SnowStarParser::DtypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDtypeName(SnowStarParser::DtypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDtypeBlockDeclaration(SnowStarParser::DtypeBlockDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionDeclaration(SnowStarParser::FunctionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionHeader(SnowStarParser::FunctionHeaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionParamsTypes(SnowStarParser::FunctionParamsTypesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionName(SnowStarParser::FunctionNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionParams(SnowStarParser::FunctionParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameterDeclaration(SnowStarParser::ParameterDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWithDeclaration(SnowStarParser::WithDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWithName(SnowStarParser::WithNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImportDeclaration(SnowStarParser::ImportDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImportName(SnowStarParser::ImportNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturnDeclaration(SnowStarParser::ReturnDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEmptyDeclaration(SnowStarParser::EmptyDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatementSeq(SnowStarParser::StatementSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimaryExpression(SnowStarParser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTheType(SnowStarParser::TheTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBuiltinTypes(SnowStarParser::BuiltinTypesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValue(SnowStarParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }


};

