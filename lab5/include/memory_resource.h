#ifndef MEMORY_RESOURCE_H
#define MEMORY_RESOURCE_H

#include <memory_resource>

class FixedBlockMemoryResource : public std::pmr::memory_resource {
private:
    void* memory_block;
    std::size_t block_size;
    std::vector<void*> free_blocks;
    std::size_t allocated_size;
    std::pmr::polymorphic_allocator<std::byte> allocator;

protected:

    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:

    explicit FixedBlockMemoryResource(std::size_t total_size);
    virtual ~FixedBlockMemoryResource();
    void release();

};

#endif