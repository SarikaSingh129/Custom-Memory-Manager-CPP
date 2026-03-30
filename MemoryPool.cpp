#include <iostream>
#include <vector>
#include <cassert>

/**
 * @brief Custom Memory Pool Manager for High Performance
 * This project demonstrates low-level memory management by pre-allocating 
 * a large chunk of memory and managing it in fixed-size blocks.
 */

class MemoryPool {
private:
    struct Block {
        Block* next;
    };

    char* poolStart;      // Start of the allocated memory pool
    Block* freeList;      // Pointer to the first free block
    size_t blockSize;     // Size of each individual block
    size_t totalBlocks;   // Total number of blocks in the pool

public:
    /**
     * @brief Constructor to initialize the pool
     * @param bSize Size of each block in bytes
     * @param tBlocks Number of blocks to pre-allocate
     */
    MemoryPool(size_t bSize, size_t tBlocks) 
        : blockSize(bSize), totalBlocks(tBlocks) {
        
        // Step 1: Allocate a large contiguous chunk of memory
        poolStart = new char[blockSize * totalBlocks];
        freeList = reinterpret_cast<Block*>(poolStart);

        // Step 2: Initialize the free list by linking all blocks
        Block* current = freeList;
        for (size_t i = 0; i < totalBlocks - 1; ++i) {
            current->next = reinterpret_cast<Block*>(reinterpret_cast<char*>(current) + blockSize);
            current = current->next;
        }
        current->next = nullptr; // Last block points to null
        
        std::cout << "[SUCCESS] Memory Pool Created: " << totalBlocks 
                  << " blocks of size " << blockSize << " bytes.\n";
    }

    /**
     * @brief Allocate a block from the pool (O(1) complexity)
     * @return Pointer to the allocated memory
     */
    void* allocate() {
        if (!freeList) {
            std::cerr << "[ERROR] Memory Pool Exhausted!\n";
            return nullptr;
        }
        
        // Take the first block from the free list
        void* addr = freeList;
        freeList = freeList->next;
        return addr;
    }

    /**
     * @brief Deallocate a block and return it to the pool (O(1) complexity)
     * @param ptr Pointer to the block being freed
     */
    void deallocate(void* ptr) {
        if (!ptr) return;
        
        // Add the block back to the front of the free list
        Block* block = reinterpret_cast<Block*>(ptr);
        block->next = freeList;
        freeList = block;
    }

    /**
     * @brief Destructor to clean up the entire pool
     */
    ~MemoryPool() {
        delete[] poolStart;
        std::cout << "[INFO] Memory Pool Destroyed and Memory Freed.\n";
    }
};

int main() {
    // Testing the Memory Pool
    MemoryPool pool(64, 3); // Create pool with 3 blocks of 64 bytes each

    // Test Allocation
    void* p1 = pool.allocate();
    void* p2 = pool.allocate();
    
    std::cout << "Allocated block 1 at: " << p1 << "\n";
    std::cout << "Allocated block 2 at: " << p2 << "\n";

    // Test Deallocation and Reuse
    pool.deallocate(p1);
    void* p3 = pool.allocate(); // This should reuse the address of p1
    std::cout << "Allocated block 3 (reused) at: " << p3 << "\n";

    return 0;
}
