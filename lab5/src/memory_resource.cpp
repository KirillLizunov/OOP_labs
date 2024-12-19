#include <iostream>
#include "../include/memory_resource.h"

FixedBlockMemoryResource::FixedBlockMemoryResource(std::size_t total_size)
    : memory_block(nullptr), block_size(total_size), allocated_size(0) {

    memory_block = std::malloc(total_size);

    if (!memory_block) {

        throw std::bad_alloc();
    }
}

FixedBlockMemoryResource::~FixedBlockMemoryResource() {
    if (memory_block) {
        std::free(memory_block);
    }
}

void FixedBlockMemoryResource::release() {

    for (void* block : free_blocks) {

        allocator.deallocate(reinterpret_cast<std::byte*>(block), 1);
    }
    free_blocks.clear();

    if (memory_block) {
        allocator.deallocate(reinterpret_cast<std::byte*>(memory_block), block_size / sizeof(std::byte));
    }

    if (allocated_size > 0 || !free_blocks.empty()) {
        std::cerr << "Warning: Not all memory was deallocated before destruction." << std::endl;
    }
}

void* FixedBlockMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {

    if (allocated_size + bytes > block_size) {
        throw std::bad_alloc();
    }

    void* ptr = std::aligned_alloc(alignment, bytes);
    if (!ptr) {
        throw std::bad_alloc();
    }

    allocated_size += bytes;
    return ptr;

}

void FixedBlockMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    std::free(p);
}

bool FixedBlockMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}