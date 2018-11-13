/*
 *  Snow* Compiler, a compiler made with ANTLR and LLVM for compiling Snow* source code
 *  Copyright (C) 2018  Mesabloo
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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