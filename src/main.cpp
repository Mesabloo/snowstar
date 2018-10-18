#include <fstream>
#include <vector>
#include <string>

#include <antlr4-runtime.h>
#include <SnowStarLexer.h>
#include <SnowStarParser.h>

#include <visitor.hpp>
#include <error_listener.hpp>
#include <termcolor/termcolor.hpp>
#include <process.hpp>
#include <argh.h>

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

#if defined(_WIN32) || defined(_WIN64)
#   include <io.h>
#   include <fcntl.h>
#endif

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

    #if defined(_WIN32) || defined(_WIN64)
    _set_mode(_fileno(stdout), _O_U16TEXT);
    #endif

    std::string file_name_ll = "",
                file_name_o = "",
    #if defined(_WIN32) || defined(_WIN64)
                file_name_out = "a.exe";
    #else
                file_name_out = "a.out";
    #endif
    std::vector<std::string> input_files{};

    // check args here
    auto parsed_cmd = argh::parser(argc, argv);
    parsed_cmd.add_params({"-o","--output"});
    
    for (unsigned i{1};i < parsed_cmd.pos_args().size();++i) {
        input_files.push_back(parsed_cmd.pos_args()[i]);
    }
    for (auto& param : parsed_cmd.params()) {
        if (param.first == "o" || param.first == "output") {
            file_name_out = param.second;
        }
    }

    if (parsed_cmd[{"-v", "--version"}]) {
        std::cout << "ssc (Snow* Compiler) 0.0.1-Beta 20181010\n"
            << "Copyright (C) 2018 Mesabloo." << std::endl;
        return 0;
    }

    if (parsed_cmd[{"-h", "--help"}] || (input_files.empty() && parsed_cmd.flags().empty())) {

        #ifndef UNICODE
        std::cout << "─────< Snow* compiler, made by Mesabloo >──────" << "\n\n"
        #else
        std::wcout << L"─────< Snow* compiler, made by Mesabloo >──────" << "\n\n"
        #endif
            << "Usage:\n"
            << argv[0] << " [-h | --help] [-v | --version] [-o | --output=<PATH>] <file1.ss file2.ss ...>\n\n"
            << "Options:\n"
            << "  -v,--version       Display the version of the Snow* compiler\n"
            << "  -h,--help          Display this message\n"
            << "  -o,--output=PATH   Change the output executable name/path\n\n"
            << "      Licenced under the GNU Public Licence v3" << std::endl;
        return 0;
    }

    #ifndef NDEBUG
        std::clog << termcolor::yellow << "   /!\\   | Entering DEBUG mode..." << termcolor::reset << std::endl;

        std::clog << termcolor::magenta << "   ...   | Input files: " << [](std::vector<std::string> const& array) -> std::string { std::string s; for (auto file : array) { s += file + " ; "; } return s; }(input_files) << "\n"
            << "   ...   | Output file: " << file_name_out << " ;" << termcolor::reset << std::endl;
    #endif

    antlr4::ANTLRFileStream input(input_files[0]);
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

    #ifndef NDEBUG
        std::clog << tree->toStringTree(&parser) << std::endl;
    #endif

    file_name_ll = input_files[0]+".ll";

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

    Visitor v{input_files[0], mod};
    v.visit(tree);
    auto const& result = v.getErrorsAndWarnings();
    for (auto& e : result.errs) {
        #ifndef UNICODE
        std::cerr << e->getError() << std::endl;
        #else
        std::wcerr << e->getError() << std::endl;
        #endif
    }
    for (auto& w : result.warns) {
        #ifndef UNICODE
        std::cerr << w->getError() << std::endl;
        #else
        std::wcerr << w->getError() << std::endl;
        #endif
    }
    if (!result.errs.empty()) return 1;

    llvm::verifyModule(mod, &llvm::errs());

    #ifndef NDEBUG
        mod.print(llvm::outs(), nullptr, false, true);
    #endif

    file_name_o = input_files[0]+".o";

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

    TinyProcessLib::Process::string_type cmd;
    #ifdef UNICODE
    cmd = L"clang " + std::wstring(file_name_o.begin(), file_name_o.end()) + L" -o " + std::wstring(file_name_out.begin(), file_name_out.end());
    #else
    cmd = "clang " + file_name_o + " -o " + file_name_out;
    #endif
    TinyProcessLib::Process linker{cmd, TinyProcessLib::Process::string_type{}, [](char const* bytes, size_t n) {
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