#include"BFinterpreter.h"
#include"BFcompiler.h"
#include<fstream>
#include<cstring>

#define VERSION "Brainfuck CI (Compiler and interpreter) v1.0.0 by mrybs for linux with gcc v12 and higher\n"
#define HELP "Brainfuck CI Help\n\nCommands:\n\tbfci [-version/-v] #Get current version\n\tbfci [-help,-h] #Get help\n\tbfci <file> #Interpret the Brainfuck code\n\tbfci -c <file-in> #Compile Brainfuck code into executable\n\tbfci -ccpp <file-in> #Compile Brainfuck code into C++ code\n\tbfci [-c/-ccpp] <file-in> -o <file-out> #Specifies the file name where to save the compiled code"

int main(int argc, const char**argv) {
    switch (argc) {
        case 2: {
            if(strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "-version") == 0){
                std::cout << VERSION;
            }else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0){
                std::cout << HELP;
            }else{
                std::ifstream file(argv[1]);
                std::string code = "";
                std::string buf;
                while (std::getline(file, buf)) code += buf + "\n";
                file.close();
                BFinterpreter interpreter;
                try {
                    code = interpreter.simplification(code);
                } catch (const std::exception e) { std::cout << e.what(); }
                try {
                    interpreter.interpretation(code);
                } catch (const std::overflow_error oe) { std::cout << oe.what(); } catch (const std::exception e) {
                    std::cout << e.what();
                }
                break;
            }
        }
        case 3:{
            if (strcmp(argv[1], "-ccpp") == 0) {
                std::ifstream file(argv[2]);
                std::string code = "";
                std::string buf;
                while (std::getline(file, buf)) code += buf + "\n";
                file.close();
                BFcompiler compiler;
                code = compiler.simplification(code);
                std::string compiled = compiler.compile(code);
                std::ofstream wfile((std::string(argv[2]) + ".cpp").c_str());
                wfile << compiled;
                wfile.close();
            }
            if (strcmp(argv[1], "-c") == 0) {
                std::ifstream file(argv[2]);
                std::string code = "";
                std::string buf;
                while (std::getline(file, buf)) code += buf + "\n";
                file.close();
                BFcompiler compiler;
                code = compiler.simplification(code);
                std::string compiled = compiler.compile(code);
                std::ofstream wfile((std::string(argv[2]) + ".cpp").c_str());
                wfile << compiled;
                wfile.close();
                system(("gcc -lstdc++ -O2 " + std::string(argv[2]) + ".cpp -o " + std::string(argv[2]) + ".elf").c_str());
                system(("rm " + std::string(argv[2]) + ".cpp").c_str());
            }
            break;
        }
        case 5: {
            if (strcmp(argv[1], "-ccpp") == 0) {
                if (strcmp(argv[3], "-o") == 0) {
                    std::ifstream file(argv[2]);
                    std::string code = "";
                    std::string buf;
                    while (std::getline(file, buf)) code += buf + "\n";
                    file.close();
                    BFcompiler compiler;
                    code = compiler.simplification(code);
                    std::string compiled = compiler.compile(code);
                    std::ofstream wfile(argv[4]);
                    wfile << compiled;
                    wfile.close();
                }
            }
            if (strcmp(argv[1], "-c") == 0) {
                if (strcmp(argv[3], "-o") == 0) {
                    std::ifstream file(argv[2]);
                    std::string code = "";
                    std::string buf;
                    while (std::getline(file, buf)) code += buf + "\n";
                    file.close();
                    BFcompiler compiler;
                    code = compiler.simplification(code);
                    std::string compiled = compiler.compile(code);
                    std::ofstream wfile((std::string(argv[2]) + ".cpp").c_str());
                    wfile << compiled;
                    wfile.close();
                    system(("gcc -lstdc++ -O2 " + std::string(argv[2]) + ".cpp -o " + std::string(argv[4])).c_str());
                    system(("rm " + std::string(argv[2]) + ".cpp").c_str());
                }
            }
            break;
        }
    }
    return 0;
}