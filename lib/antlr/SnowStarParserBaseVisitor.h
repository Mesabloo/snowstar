
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

  virtual antlrcpp::Any visitVariableDeclarators(SnowStarParser::VariableDeclaratorsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableDeclarator(SnowStarParser::VariableDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableDeclaratorId(SnowStarParser::VariableDeclaratorIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableInitializer(SnowStarParser::VariableInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLiteral(SnowStarParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntegerLiteral(SnowStarParser::IntegerLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlock(SnowStarParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlockStatement(SnowStarParser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocalVariableDeclaration(SnowStarParser::LocalVariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimary(SnowStarParser::PrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCreator(SnowStarParser::CreatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCreatedName(SnowStarParser::CreatedNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeGeneric(SnowStarParser::TypeGenericContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeList(SnowStarParser::TypeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeType(SnowStarParser::TypeTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimitiveType(SnowStarParser::PrimitiveTypeContext *ctx) override {
    return visitChildren(ctx);
  }


};

