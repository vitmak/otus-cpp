#include "Command.h"
#include "CommandPackage.h"
#include <iostream>
#include <string>
#include <exception>


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    CommandPackage commandPackage{ atoi(argv[1]) };

    try {
        std::string line;
        while (std::getline(std::cin, line)) {

            Command cmd{ line };
            commandPackage.ParseCommand(cmd);

            if (cmd.IsEOF())
                break;
        }

        commandPackage.Print(std::cout);
        commandPackage.Save();
    }
    catch (const char* error) {
        std::cerr << error << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
    
    return 0;
}