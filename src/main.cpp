#include <fstream>
#include <vector>
#include <string>

#include <antlr4-runtime.h>
#include <SnowStarLexer.h>
#include <SnowStarParser.h>

#include <visitor.hpp>
#include <error_listener.hpp>
#include <termcolor/termcolor.hpp>
#include <args_parser.hpp>
#include <process.hpp>

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Verifier.h>
#include <llvm/MC/MCTargetOptions.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/Program.h>

namespace utils {
    std::vector<std::string> str_split(std::string const& str, char const separator) {
        std::vector<std::string> vect;
        std::istringstream f{str};
        std::string s;
        while (getline(f, s, separator)) {
            vect.push_back(s);
        }
        return vect;
    }
};

int main(int argc, char** argv) {

    // check args here
    {
        args_parser::CLI interface;
        std::vector<args_parser::Option> opts {
            args_parser::Option({"-h", "--help"}),
            args_parser::Option({"-v", "--version"})
        };
        interface.setOptions(opts);
    }

    #ifndef NDEBUG
        std::clog << termcolor::yellow << "   /!\\   | Entering DEBUG mode..." << termcolor::reset << std::endl;
    #endif

    antlr4::ANTLRFileStream input(argv[1]);
    SnowStarLexer lexer(&input);
    ErrorListener lexer_listener;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&lexer_listener);
    antlr4::CommonTokenStream tokens(&lexer);
    
    tokens.fill();

    if (lexer.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "Unexpected errors occured:\n" << lexer_listener << std::endl;
        return 1;
    }

    SnowStarParser parser(&tokens);
    ErrorListener parser_listener;
    parser.removeErrorListeners();
    parser.addErrorListener(&parser_listener);
    antlr4::tree::ParseTree* tree = parser.compilationUnit();

    if (parser.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "Unexpected errors occured:\n" << parser_listener << std::endl;
        return 1;
    }

    std::clog << tree->toStringTree(&parser) << std::endl;

    std::string arg{argv[1]};
    arg.erase(arg.begin(), arg.begin()+arg.find_last_of("/\\")+1);

    std::string file_name_ll = arg+".ll",
                file_name_o = arg+".o",
                file_name_out = arg+".out",
                file_name = arg;

    static llvm::LLVMContext ctx{};
    llvm::Module mod = llvm::Module(file_name_ll, ctx);
    std::string targetTriple = llvm::sys::getDefaultTargetTriple(),
                err;

    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    llvm::Target const* target = llvm::TargetRegistry::lookupTarget(targetTriple, err);
    if (!target) {
        std::cerr << termcolor::red << err << termcolor::reset << std::endl;
        return -1;
    }
    std::string cpu = "generic",
                features = "";
    llvm::TargetOptions opts;
    auto const model = llvm::Optional<llvm::Reloc::Model>();
    llvm::TargetMachine* machine = target->createTargetMachine(targetTriple, cpu, features, opts, model);

    mod.setDataLayout(machine->createDataLayout());
    mod.setTargetTriple(targetTriple);

    Visitor v{arg, mod};
    v.visit(tree);
    auto const& result = v.getErrorsAndWarnings();
    for (auto& e : result.errs) {
        std::cerr << e->getError() << std::endl;
    }
    for (auto& w : result.warns) {
        std::cerr << w->getError() << std::endl;
    }
    if (!result.errs.empty()) return 1;

    llvm::verifyModule(mod, &llvm::errs());

    #ifndef NDEBUG
        mod.print(llvm::outs(), nullptr, false, true);
    #endif

    std::error_code code;
    llvm::raw_fd_ostream destination{file_name_o, code, llvm::sys::fs::F_None};
    if (code) {
        std::cerr << termcolor::red << "Could not open file " << file_name_o << ": " << code.message() << termcolor::reset << std::endl;
        return -1;
    }

    llvm::legacy::PassManager pass;
    if (machine->addPassesToEmitFile(pass, destination, nullptr, llvm::TargetMachine::CGFT_ObjectFile)) {
       std::cerr << termcolor::red << "Machine can't emit a file of this type." << termcolor::reset << std::endl;
       return -1;
    }

    pass.run(mod);
    destination.flush();

    TinyProcessLib::Process linker{"clang " + file_name_o + " -o " + file_name_out, "", [](char const* bytes, size_t n) {
        std::cout << std::string{bytes, n} << std::endl;
    }};
    linker.get_exit_status();

    std::error_code deleted = llvm::sys::fs::remove(file_name_o);
    #ifndef NDEBUG
        if (deleted) {
            std::clog << termcolor::yellow << "   /!\\   | File '" << file_name_o << "' not deleted: " << deleted.message() << "." << termcolor::reset << std::endl;
        } else {
            std::clog << termcolor::yellow << "   /!\\   | File '" << file_name_o << "' deleted successfully." << termcolor::reset << std::endl;
        }
    #endif

    return 0;
}