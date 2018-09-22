
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
    virtual antlrcpp::Any visitVariableDeclarators(SnowStarParser::VariableDeclaratorsContext *context) = 0;

    virtual antlrcpp::Any visitVariableDeclarator(SnowStarParser::VariableDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitVariableDeclaratorId(SnowStarParser::VariableDeclaratorIdContext *context) = 0;

    virtual antlrcpp::Any visitVariableInitializer(SnowStarParser::VariableInitializerContext *context) = 0;

    virtual antlrcpp::Any visitLiteral(SnowStarParser::LiteralContext *context) = 0;

    virtual antlrcpp::Any visitIntegerLiteral(SnowStarParser::IntegerLiteralContext *context) = 0;

    virtual antlrcpp::Any visitBlock(SnowStarParser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitBlockStatement(SnowStarParser::BlockStatementContext *context) = 0;

    virtual antlrcpp::Any visitLocalVariableDeclaration(SnowStarParser::LocalVariableDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPrimary(SnowStarParser::PrimaryContext *context) = 0;

    virtual antlrcpp::Any visitCreator(SnowStarParser::CreatorContext *context) = 0;

    virtual antlrcpp::Any visitCreatedName(SnowStarParser::CreatedNameContext *context) = 0;

    virtual antlrcpp::Any visitTypeGeneric(SnowStarParser::TypeGenericContext *context) = 0;

    virtual antlrcpp::Any visitTypeList(SnowStarParser::TypeListContext *context) = 0;

    virtual antlrcpp::Any visitTypeType(SnowStarParser::TypeTypeContext *context) = 0;

    virtual antlrcpp::Any visitPrimitiveType(SnowStarParser::PrimitiveTypeContext *context) = 0;


};

