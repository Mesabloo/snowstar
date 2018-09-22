#include <visitor.hpp>

namespace utils {
    bool str_startswith(std::string const& src, std::string const& prefix) {
        return src.size() >= prefix.size() && src.substr(0, prefix.size()) == prefix;
    }
}

Visitor::Visitor(llvm::Module& m) : module{m}, current_builder{m.getContext()} {
    llvm::FunctionType* type = llvm::FunctionType::get(current_builder.getInt32Ty(), false);
    llvm::Function* main = llvm::Function::Create(type, llvm::Function::ExternalLinkage, "main", &module);
}

antlrcpp::Any Visitor::visitStatement(SnowStarParser::StatementContext* ctx) {
    auto res = visitChildren(ctx);

}

