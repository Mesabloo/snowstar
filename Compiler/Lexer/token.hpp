#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <vector>

/* 

  What is a Token ?
  A Token is simply one of the operands in the language synta. For example, `45` is a Token of type number.

  To make things easier, I decided to store every value as `std::string`s for the Tokens.
  The value will in the parsing process be interpreted as a specific value following its Token::Type.

    */
class Token {
    public:
        enum class Type {
            KEYWORD,               // Instruction names and memory segments names
            SEPARATOR,             // Most likely to only be either `[` or `]` or `,`.
            LITERAL_STRING,        // Tokens following the formatting: '\*' (with escape codes)
            LITERAL_NUMBER_FLOAT,  // Tokens following the scheme: ^[0-9]+(\\.{1}[0-9]*){1}$
            LITERAL_NUMBER_INT,    // Tokens floowing the scheme: ^[0-9]+$
            LITERAL_MEMORY,        // Special tokens used for direct access of memory
            EOL,                   // For end of line
            INLINE_COMMENT,        // % comment
            MULTILINE_COMMENT,     // #* comment *#
            INVALID                // When none of these types are good enough, the Token is marked invalid.
        };
        static std::string getTypeSignification(Token::Type);

        Token();
        Token(Token::Type, std::string);
        ~Token();

        Token::Type getType() const;
        std::string getValue() const;

    protected:
        Token::Type m_type;
        std::string m_value;
};

class Consumer {
    public:
        class Store {
            public:
                Store();
                Store(Token const&, Token const&);
                ~Store();

                Token getMemseg() const;
                Token getIndex() const;

            protected:
                Token m_memseg, m_index; 
        };

        Consumer(Token const&, Consumer::Store const&, std::vector<Token> const&);

        Token getInstruction() const;
        Consumer::Store getStorage() const;
        std::vector<Token> getArgs() const;

        std::string toString() const;

    protected:
        Token m_instruction;
        Consumer::Store m_storage;
        std::vector<Token> m_args;
};

bool operator==(Token const&, Token const&);
bool operator==(Consumer const&, Consumer const&);

#endif