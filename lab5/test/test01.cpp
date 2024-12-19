#include <gtest/gtest.h>
#include "../include/memory_resource.h"
#include "../include/list.h"

struct ComplexType {
    int a;
    double b;
    std::string c;

    ComplexType(int x, double y, const std::string& z) : a(x), b(y), c(z) {}

    bool operator==(const ComplexType& other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};

TEST(MemoryResourceTest, AllocationDeallocation) {
    constexpr std::size_t memory_size = 1024;
    FixedBlockMemoryResource resource(memory_size);

    void* block1 = resource.allocate(64);
    EXPECT_NE(block1, nullptr);

    resource.deallocate(block1, 64);
    void* block2 = resource.allocate(64);
    EXPECT_EQ(block1, block2);
}

TEST(MemoryResourceTest, OutOfMemory) {
    constexpr std::size_t memory_size = 64;
    FixedBlockMemoryResource resource(memory_size);

    void* block1 = nullptr;
    EXPECT_NO_THROW(block1 = resource.allocate(64));
    EXPECT_NE(block1, nullptr);

    void* block2 = nullptr;  
    EXPECT_THROW(block2 = resource.allocate(128), std::bad_alloc);
}



TEST(ListTest, PushBackAndIteration) {
    constexpr std::size_t memory_size = 1024;
    FixedBlockMemoryResource resource(memory_size);

    {
        List<int> list(&resource);
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);

        std::vector<int> values;
        for (auto& val : list) {
            values.push_back(val);
        }

        EXPECT_EQ(values, (std::vector<int>{10, 20, 30}));
        list.clear_list();
    }
}

TEST(ListTest, PushFrontAndIteration) {
    constexpr std::size_t memory_size = 1024;
    FixedBlockMemoryResource resource(memory_size);

    {
        List<int> list(&resource);
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);

        std::vector<int> values;
        for (auto& val : list) {
            values.push_back(val);
        }

        EXPECT_EQ(values, (std::vector<int>{30, 20, 10}));
        list.clear_list(); 
    }
}

TEST(ListTest, ComplexTypeUsage) {
    constexpr std::size_t memory_size = 1024;
    FixedBlockMemoryResource resource(memory_size);

    {
        List<ComplexType> list(&resource);
        list.push_back({1, 2.5, "first"});
        list.push_back({2, 3.5, "second"});

        auto it = list.begin();
        EXPECT_EQ(*it, ComplexType(1, 2.5, "first"));
        ++it;
        EXPECT_EQ(*it, ComplexType(2, 3.5, "second"));
        list.clear_list();
    }
}


TEST(ListTest, EmptyList) {
    constexpr std::size_t memory_size = 1024;
    FixedBlockMemoryResource resource(memory_size);

    {
        List<int> list(&resource);
        EXPECT_EQ(list.begin(), list.end());
        list.clear_list(); 
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}