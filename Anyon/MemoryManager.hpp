#pragma once
#include <stddef.h>

namespace Anyon
{
    class MemoryManager
    {
        friend class Core;
        
    public:
        template<class T, typename ... Arguments>
        inline T* New(Arguments ... parameters)
        {
            return new (Allocate(sizeof(T))) T(parameters ...);
        }
        
        template<class T>
        inline void Delete(T *p)
        {
            p->~T();
            Free(p, sizeof(T));
        }
        
        void* Allocate(size_t size);
        void* Allocate(size_t size, size_t alignment);
        void Free(void* p, size_t size);
        
        MemoryManager(MemoryManager const &) = delete;
        MemoryManager& operator = (MemoryManager const &) = delete;
        MemoryManager& operator = (MemoryManager &&) = delete;
        
    private:
        class Allocator
        {
        public:
            Allocator();
            Allocator(size_t dataSize, size_t pageSize, size_t alignment);
            ~Allocator();
            
            void Reset(size_t dataSize, size_t pageSize, size_t alignment);
            
            void* Allocate();
            void Free(void *p);
            void FreeAll();
            
        private:
            struct BlockHeader
            {
                BlockHeader *next;
            };
            
            struct PageHeader
            {
                PageHeader *next;
                
                BlockHeader* Blocks()
                {
                    return reinterpret_cast<BlockHeader*>(this + 1);
                }
            };
            
            BlockHeader* NextBlock(BlockHeader* pBlock);
            PageHeader *pages;
            BlockHeader *freed;
            size_t dataSize, pageSize, alignmentSize, blockSize,
            blocksPerPage, pagesCount, blocksCount, freeBlocksCount;
        };
        
        static constexpr size_t defaultBlockSizes[] = {
            // 4-increments
            4,  8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
            52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96,
            // 32-increments
            128, 160, 192, 224, 256, 288, 320, 352, 384,
            416, 448, 480, 512, 544, 576, 608, 640,
            // 64-increments
            704, 768, 832, 896, 960, 1024
        };
        static constexpr size_t defaultPageSize = 8192,
        defaultAlignment = 4,
        defaultBlockSizesCount = sizeof(defaultBlockSizes) / sizeof(defaultBlockSizes[0]),
        maxBlockSize = defaultBlockSizes[defaultBlockSizesCount - 1];
        
        size_t *blockSizeLookup;
        Allocator *allocators;
        
        MemoryManager();
        ~MemoryManager();
        Allocator* LookUpAllocator(size_t size);
    };
}
