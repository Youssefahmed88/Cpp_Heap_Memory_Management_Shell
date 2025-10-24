#include "MemoryAllocator.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <stdexcept>

MemoryAllocator::~MemoryAllocator() {
    for (auto &kv : allocations) {
        ::free(kv.first);
    }
    allocations.clear();
}

void* MemoryAllocator::allocate(std::size_t size) {
    if (size == 0) {
        std::cout << "Allocation size must be > 0\n";
        return nullptr;
    }

    void* ptr = std::malloc(size);
    if (!ptr) {
        std::cout << "Allocation failed (" << size << " bytes)\n";
        return nullptr;
    }
    allocations[ptr] = size;
    std::cout << "Allocated " << size << " bytes at address " << ptrToHex(ptr) << "\n";

    // Show first few bytes to prove heap usage
    unsigned char* cptr = static_cast<unsigned char*>(ptr);
    std::cout << "Memory content (first " << std::min(size, size_t(16)) << " bytes): ";
    for (size_t i = 0; i < std::min(size, size_t(16)); ++i) {
        std::cout << std::hex << (int)cptr[i] << " ";
    }
    std::cout << std::dec << "\n";

    return ptr;
}

void MemoryAllocator::freeMemory(void* ptr) {
    if (!ptr) {
        std::cout << "Error: null pointer\n";
        return;
    }
    auto it = allocations.find(ptr);
    if (it == allocations.end()) {
        std::cout << "Error: Address not found or already freed!\n";
        return;
    }
    std::size_t size = it->second;
    ::free(ptr);
    allocations.erase(it);
    std::cout << "Freed " << size << " bytes at address " << ptrToHex(ptr) << "\n";
}

void MemoryAllocator::showMemory() const {
    if (allocations.empty()) {
        std::cout << "No allocations (heap map is empty)\n";
        return;
    }
    std::cout << "Currently allocated blocks:\n";
    std::cout << std::left << std::setw(20) << "Address" << std::setw(12) << "Size(bytes)" << "\n";
    for (const auto &kv : allocations) {
        std::cout << std::left << std::setw(20) << ptrToHex(kv.first)
                  << std::setw(12) << kv.second << "\n";
    }
}

std::string MemoryAllocator::ptrToHex(void* p) {
    std::ostringstream oss;
    oss << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(p);
    return oss.str();
}

void* MemoryAllocator::hexToPtr(const std::string& hex) {
    std::uintptr_t val = 0;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> val;
    if (ss.fail()) {
        throw std::invalid_argument("Invalid address: " + hex);
    }
    return reinterpret_cast<void*>(val);
}
