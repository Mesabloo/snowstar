#ifndef BYTE_CONSUMER_HPP
#define BYTE_CONSUMER_HPP

#include <iostream>
#include <vector>

#include "byte_token.hpp"

class ByteConsumer {
    public:
        class Store {
            public:
                Store();
                Store(ByteToken const&);
                ~Store();

                ByteToken getMemory() const;

                friend std::ostream& operator<<(std::ostream&, Store const&);
                friend bool operator==(Store const&, Store const&);

            protected:
                ByteToken m_memory;
        };

        ByteConsumer(ByteToken const&, ByteConsumer::Store const&, std::vector<ByteToken> const&);
        ~ByteConsumer();

        ByteToken getInstruction() const;
        ByteConsumer::Store getStorage() const;
        std::vector<ByteToken> getArgs() const;

        friend std::ostream& operator<<(std::ostream&, ByteConsumer const&);
        friend bool operator==(ByteConsumer const&, ByteConsumer const&);

    protected:
        ByteToken m_instruction;
        ByteConsumer::Store m_storage;
        std::vector<ByteToken> m_args;
};

#endif