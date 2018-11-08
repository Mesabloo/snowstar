#ifndef PARSER_ERROR_HANDLER_HPP
#define PARSER_ERROR_HANDLER_HPP

#include <DefaultErrorStrategy.h>
#include <antlr4-runtime.h>

#include <string>

class ParserErrorHandler : public antlr4::DefaultErrorStrategy {
protected:
    void notifyErrorListeners(antlr4::Parser*, std::string const&, antlr4::RecognitionException const&);

    virtual void reportNoViableAlternative(antlr4::Parser*, antlr4::NoViableAltException const&) override;
    virtual void reportInputMismatch(antlr4::Parser*, antlr4::InputMismatchException const&) override;
    virtual void reportFailedPredicate(antlr4::Parser*, antlr4::FailedPredicateException const&) override;
    virtual void reportUnwantedToken(antlr4::Parser*) override;
    virtual void reportMissingToken(antlr4::Parser*) override;
};

#endif