#include "MemoryManager.hpp"
#include <cstdlib>
#include <assert.h>

using namespace Anyon;

MemoryManager::Allocator::Allocator():
pages(nullptr), freed(nullptr),
dataSize(0), pageSize(0), alignmentSize(0), blockSize(0), blocksPerPage(0)
{}

MemoryManager::Allocator::Allocator(size_t dataSize, size_t pageSize, size_t alignment):
pages(nullptr), freed(nullptr)
{
    Reset(dataSize, pageSize, alignment);
}

MemoryManager::Allocator::~Allocator()
{
    FreeAll();
}

void MemoryManager::Allocator::Reset(size_t dataSize, size_t pageSize, size_t alignment)
{
    FreeAll();
    
    this->dataSize = dataSize;
    this->pageSize = pageSize;
    
    size_t minimal_size = (sizeof(BlockHeader) > dataSize) ? sizeof(BlockHeader) : dataSize;
    // This magic only works when alignment is 2^n, which should general be the case
    // because most CPU/GPU also requires the aligment be in 2^n
    // but still we use a assert to guarantee it.
    assert(alignment > 0 && ((alignment & (alignment - 1))) == 0);
    
    blockSize = ((minimal_size + (alignment - 1)) & ~(alignment - 1));
    alignmentSize = blockSize - minimal_size;
    blocksPerPage = (pageSize - sizeof(PageHeader)) / blockSize;
}

void* MemoryManager::Allocator::Allocate()
{
    if (!freed)
    {
        PageHeader *page = reinterpret_cast<PageHeader*>(new uint8_t[pageSize]);
        ++pagesCount;
        blocksCount += blocksPerPage;
        freeBlocksCount += blocksPerPage;
        
        if (pages)
            page->next = pages;
        else
            page->next = nullptr;
        
        pages = page;
        
        BlockHeader *block = page->Blocks();
        
        for (size_t i = 0; i < blocksPerPage - 1; ++i)
        {
            block->next = NextBlock(block);
            block = NextBlock(block);
        }
        
        block->next = nullptr;
        freed = page->Blocks();
    }
    
    BlockHeader *freeBlock = freed;
    freed = freed->next;
    --freeBlocksCount;
    
    return reinterpret_cast<void*>(freeBlock);
}

void MemoryManager::Allocator::Free(void* p)
{
    BlockHeader *block = reinterpret_cast<BlockHeader*>(p);
    block->next = freed;
    freed = block;
    ++freeBlocksCount;
}

void MemoryManager::Allocator::FreeAll()
{
    PageHeader *page = pages;
    while (page)
    {
        PageHeader* _p = page;
        page = page->next;
        delete[] reinterpret_cast<uint8_t*>(_p);
    }
    
    pages = nullptr;
    freed = nullptr;
    pagesCount = 0;
    blocksCount = 0;
    freeBlocksCount = 0;
}

MemoryManager::Allocator::BlockHeader* MemoryManager::Allocator::NextBlock(BlockHeader *pBlock)
{
    return reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(pBlock) + blockSize);
}

MemoryManager::MemoryManager()
{
    blockSizeLookup = new size_t[maxBlockSize + 1];
    size_t j = 0;
    for (size_t i = 0; i <= maxBlockSize; ++i)
    {
        if (i > defaultBlockSizes[j])
            ++j;
        
        blockSizeLookup[i] = j;
    }
    
    allocators = new Allocator[defaultBlockSizesCount];
    for (int i = 0; i < defaultBlockSizesCount; ++i)
        allocators[i].Reset(defaultBlockSizes[i], defaultPageSize, defaultAlignment);
}

MemoryManager::~MemoryManager()
{
    delete[] allocators;
    delete[] blockSizeLookup;
}

MemoryManager::Allocator* MemoryManager::LookUpAllocator(size_t size)
{
    if (size <= maxBlockSize)
        return allocators + blockSizeLookup[size];
    else
        return nullptr;
}

void* MemoryManager::Allocate(size_t size)
{
    Allocator *alloc = LookUpAllocator(size);
    if (alloc)
        return alloc->Allocate();
    else
        return std::malloc(size);
}

void* MemoryManager::Allocate(size_t size, size_t alignment)
{
    uint8_t *p;
    size += alignment;
    
    Allocator *alloc = LookUpAllocator(size);
    if (alloc)
        p = reinterpret_cast<uint8_t*>(alloc->Allocate());
    else
        p = reinterpret_cast<uint8_t*>(std::malloc(size));
    
    p = reinterpret_cast<uint8_t*>(((reinterpret_cast<size_t>(p) + (alignment - 1)) & ~(alignment - 1)));
    
    return static_cast<void*>(p);
}

void MemoryManager::Free(void* p, size_t size)
{
        Allocator* alloc = LookUpAllocator(size);
        if (alloc)
            alloc->Free(p);
        else
            std::free(p);
}
