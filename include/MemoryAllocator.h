#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <unordered_map>
#include <string>
#include <cstddef>

class MemoryAllocator {
private:
    std::unordered_map<void*, std::size_t> allocations;

public:
    ~MemoryAllocator();

    void* allocate(std::size_t size);
    void freeMemory(void* ptr);
    void showMemory() const;

    static std::string ptrToHex(void* p);
    static void* hexToPtr(const std::string& hex);
};

#endif
