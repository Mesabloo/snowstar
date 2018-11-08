#include <parser_error_handler.hpp>

void ParserErrorHandler::notifyErrorListeners(antlr4::Parser* parser, std::string const& msg, antlr4::RecognitionException const& re) {
    parser->notifyErrorListeners(re.getOffendingToken(), msg, std::make_exception_ptr(re));
}

void ParserErrorHandler::reportNoViableAlternative(antlr4::Parser* parser, antlr4::NoViableAltException const& nvae) {
    std::string msg{"Invalid statement"};
    antlr4::TokenStream* tk_stream = dynamic_cast<antlr4::TokenStream*>(parser->getInputStream());
    if (tk_stream != nullptr) {
        msg += " `" + tk_stream->getText(nvae.getStartToken(), nvae.getOffendingToken()) + "`";
    }
    msg += ".";
    if (tk_stream != nullptr) {
        msg += "\n";
        antlr4::Token* line_begin = nvae.getStartToken();
        int index = line_begin->getTokenIndex(), first_char = line_begin->getCharPositionInLine()+1;
        while (index != 0 && first_char > line_begin->getCharPositionInLine()) {
            first_char = line_begin->getCharPositionInLine();
            line_begin = tk_stream->get(--index);
        }
        line_begin = tk_stream->get(++index);
        antlr4::Token* line_end = nvae.getOffendingToken();
        int end_index = line_end->getTokenIndex(), last_char = line_end->getCharPositionInLine()-1;
        while (end_index != tk_stream->size()-1 && last_char < line_end->getCharPositionInLine()) {
            last_char = line_end->getCharPositionInLine();
            line_end = tk_stream->get(++end_index);
        }
        line_end = tk_stream->get(--end_index);
        std::string code_line = tk_stream->getText(line_begin, line_end);
        std::replace(code_line.begin(), code_line.end(), '\n', ' ');
        msg += code_line + "\n";
        msg += tk_stream->getText(nvae.getStartToken(), nvae.getOffendingToken()) + "\n" + std::to_string(nvae.getStartToken()->getCharPositionInLine()+1);
        msg += "\n" + std::to_string(line_begin->getCharPositionInLine());
    }
    notifyErrorListeners(parser, msg, nvae);
}

void ParserErrorHandler::reportInputMismatch(antlr4::Parser* parser, antlr4::InputMismatchException const& ime) {
    std::string msg{"Ambiguous token"};
    antlr4::TokenStream* tk_stream = dynamic_cast<antlr4::TokenStream*>(parser->getInputStream());
    if (tk_stream != nullptr) {
        msg += " `" + tk_stream->getText(antlr4::misc::Interval{ime.getOffendingToken()->getStartIndex(), ime.getOffendingToken()->getStopIndex()}) + "`";
    }
    msg += ".";
    if (tk_stream != nullptr) {
        msg += "\n";
        antlr4::Token* line_begin = ime.getOffendingToken();
        int index = line_begin->getTokenIndex(), first_char = line_begin->getCharPositionInLine()+1;
        while (index != 0 && first_char > line_begin->getCharPositionInLine()) {
            first_char = line_begin->getCharPositionInLine();
            line_begin = tk_stream->get(--index);
        }
        line_begin = tk_stream->get(++index);
        antlr4::Token* line_end = ime.getOffendingToken();
        int end_index = line_end->getTokenIndex(), last_char = line_end->getCharPositionInLine()-1;
        while (end_index != tk_stream->size()-1 && last_char < line_end->getCharPositionInLine()) {
            last_char = line_end->getCharPositionInLine();
            line_end = tk_stream->get(++end_index);
        }
        line_end = tk_stream->get(--end_index);
        std::string code_line = tk_stream->getText(line_begin, line_end);
        std::replace(code_line.begin(), code_line.end(), '\n', ' ');
        msg += code_line + "\n";
        msg += tk_stream->getText(ime.getOffendingToken(), ime.getOffendingToken()) + "\n" + std::to_string(ime.getOffendingToken()->getCharPositionInLine()+1);
        msg += "\n" + std::to_string(line_begin->getCharPositionInLine());
    }
    notifyErrorListeners(parser, msg, ime);
}

void ParserErrorHandler::reportFailedPredicate(antlr4::Parser* parser, antlr4::FailedPredicateException const& fpe) {
    std::string msg(fpe.what());
    antlr4::TokenStream* tk_stream = dynamic_cast<antlr4::TokenStream*>(parser->getInputStream());
    if (tk_stream != nullptr) {
        msg += "\n";
        antlr4::Token* line_begin = fpe.getOffendingToken();
        int index = line_begin->getTokenIndex(), first_char = line_begin->getCharPositionInLine()+1;
        while (index != 0 && first_char > line_begin->getCharPositionInLine()) {
            first_char = line_begin->getCharPositionInLine();
            line_begin = tk_stream->get(--index);
        }
        line_begin = tk_stream->get(++index);
        antlr4::Token* line_end = fpe.getOffendingToken();
        int end_index = line_end->getTokenIndex(), last_char = line_end->getCharPositionInLine()-1;
        while (end_index != tk_stream->size()-1 && last_char < line_end->getCharPositionInLine()) {
            last_char = line_end->getCharPositionInLine();
            line_end = tk_stream->get(++end_index);
        }
        line_end = tk_stream->get(--end_index);
        std::string code_line = tk_stream->getText(line_begin, line_end);
        std::replace(code_line.begin(), code_line.end(), '\n', ' ');
        msg += code_line + "\n";
        msg += tk_stream->getText(fpe.getOffendingToken(), fpe.getOffendingToken()) + "\n" + std::to_string(fpe.getOffendingToken()->getCharPositionInLine()+1);
        msg += "\n" + std::to_string(line_begin->getCharPositionInLine());
    }
    notifyErrorListeners(parser, msg, fpe);
}

void ParserErrorHandler::reportUnwantedToken(antlr4::Parser* parser) {
    std::string msg{"Unexpected token"};
    antlr4::Token* tk = parser->getCurrentToken();
    msg += " `" + tk->getText() + "`";
    msg += ".";
    antlr4::TokenStream* tk_stream = dynamic_cast<antlr4::TokenStream*>(parser->getInputStream());
    if (tk_stream != nullptr) {
        msg += "\n";
        antlr4::Token* line_begin = parser->getCurrentToken();
        int index = line_begin->getTokenIndex(), first_char = line_begin->getCharPositionInLine()+1;
        while (index != 0 && first_char > line_begin->getCharPositionInLine()) {
            first_char = line_begin->getCharPositionInLine();
            line_begin = tk_stream->get(--index);
        }
        line_begin = tk_stream->get(++index);
        antlr4::Token* line_end = parser->getCurrentToken();
        int end_index = line_end->getTokenIndex(), last_char = line_end->getCharPositionInLine()-1;
        while (end_index != tk_stream->size()-1 && last_char < line_end->getCharPositionInLine()) {
            last_char = line_end->getCharPositionInLine();
            line_end = tk_stream->get(++end_index);
        }
        line_end = tk_stream->get(--end_index);
        std::string code_line = tk_stream->getText(line_begin, line_end);
        std::replace(code_line.begin(), code_line.end(), '\n', ' ');
        msg += code_line + "\n";
        msg += tk_stream->getText(parser->getCurrentToken(), parser->getCurrentToken()) + "\n" + std::to_string(parser->getCurrentToken()->getCharPositionInLine()+1);
        msg += "\n" + std::to_string(line_begin->getCharPositionInLine());
    }
    parser->notifyErrorListeners(tk, msg, nullptr);
}

void ParserErrorHandler::reportMissingToken(antlr4::Parser* parser) {
    std::string msg{"Expected token."};
    antlr4::Token* tk = parser->getCurrentToken();
    antlr4::TokenStream* tk_stream = dynamic_cast<antlr4::TokenStream*>(parser->getInputStream());
    if (tk_stream != nullptr) {
        msg += "\n";
        antlr4::Token* line_begin = parser->getCurrentToken();
        int index = line_begin->getTokenIndex(), first_char = line_begin->getCharPositionInLine()+1;
        while (index != 0 && first_char > line_begin->getCharPositionInLine()) {
            first_char = line_begin->getCharPositionInLine();
            line_begin = tk_stream->get(--index);
        }
        line_begin = tk_stream->get(++index);
        antlr4::Token* line_end = parser->getCurrentToken();
        int end_index = line_end->getTokenIndex(), last_char = line_end->getCharPositionInLine()-1;
        while (end_index != tk_stream->size()-1 && last_char < line_end->getCharPositionInLine()) {
            last_char = line_end->getCharPositionInLine();
            line_end = tk_stream->get(++end_index);
        }
        line_end = tk_stream->get(--end_index);
        std::string code_line = tk_stream->getText(line_begin, line_end);
        std::replace(code_line.begin(), code_line.end(), '\n', ' ');
        msg += code_line + "\n";
        msg += tk_stream->getText(parser->getCurrentToken(), parser->getCurrentToken()) + "\n" + std::to_string(parser->getCurrentToken()->getCharPositionInLine()+1);
        msg += "\n" + std::to_string(line_begin->getCharPositionInLine());
    }
    parser->notifyErrorListeners(tk, msg, nullptr);
}