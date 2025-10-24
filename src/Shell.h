#pragma once
#include "MemoryAllocator.h"
#include <string>

class Shell {
public:
    Shell();
    void run();

private:
    MemoryAllocator allocator;
    void parseCommand(const std::string& line);
    void cmdAlloc(const std::string& arg);
    void cmdFree(const std::string& arg);
};
