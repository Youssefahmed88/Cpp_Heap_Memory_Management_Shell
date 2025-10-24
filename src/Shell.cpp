#include "MemoryAllocator.h"
#include <iostream>
#include <sstream>
#include <string>

class Shell {
private:
    MemoryAllocator allocator;

    void execute(const std::string& cmdLine) {
        std::stringstream ss(cmdLine);
        std::string cmd;
        ss >> cmd;
        if (cmd == "alloc") {
            std::size_t size;
            ss >> size;
            if (!ss.fail()) allocator.allocate(size);
            else std::cout << "Usage: alloc <size>\n";
        } else if (cmd == "free") {
            std::string hexAddr;
            ss >> hexAddr;
            if (!ss.fail()) {
                try {
                    void* ptr = MemoryAllocator::hexToPtr(hexAddr);
                    allocator.freeMemory(ptr);
                } catch (...) {
                    std::cout << "Invalid address format\n";
                }
            } else std::cout << "Usage: free <hex-address>\n";
        } else if (cmd == "show") {
            allocator.showMemory();
        } else if (cmd == "help") {
            std::cout << "Commands:\n"
                      << "  alloc <size>        allocate bytes from heap\n"
                      << "  free <hex-address>  free by address\n"
                      << "  show                show allocated blocks\n"
                      << "  exit                exit shell\n";
        } else if (cmd == "exit") {
            exit(0);
        } else if (!cmd.empty()) {
            std::cout << "Unknown command\n";
        }
    }

public:
    void run() {
        std::cout << "MiniShell (real-heap allocator). Type 'help'.\n";
        std::string line;
        while (true) {
            std::cout << ">> ";
            std::getline(std::cin, line);
            execute(line);
        }
    }
};
