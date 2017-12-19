#include "ResourceManager.hpp"
#include <cassert>

using namespace Anyon;

ResourceManager::Resource::Resource(const std::string &name, ResourceManager *resMan):
resMan(resMan)
{
    assert(resMan != nullptr); // Can not be null!
    
    this->name = name;
    resMan->AddResource(this);
}

ResourceManager::Resource::~Resource()
{
    assert(refs < 2); // Trying to delete resource that is still acquired!
    resMan->RemoveResource(this);
}

const std::string& ResourceManager::Resource::Name() const
{
    return name;
}

void ResourceManager::Resource::Acquire()
{
    ++refs;
}

void ResourceManager::Resource::Release()
{
    if (--refs == 0)
        delete this;
}

unsigned ResourceManager::Resource::References() const
{
    return refs;
}

ResourceManager::Resource* ResourceManager::Find(const std::string &name) const
{
    auto res = resources.find(name);
    
    if (res == resources.end())
        return nullptr;
    else
        return res->second;
}

void ResourceManager::AddResource(ResourceManager::Resource *res)
{
    assert(res != nullptr);
    
    auto r = resources.emplace(res->Name(), res);
    assert(r.second == false); // Every resouces must be unique!
}

void ResourceManager::RemoveResource(ResourceManager::Resource *res)
{
    assert(res != nullptr);
    
    resources.erase(res->Name());
}

void ResourceManager::ReleaseAll()
{
    assert(resources.size() == 0); // There are leaked resources!
    
    std::for_each(resources.begin(), resources.end(), [](auto item)
    {
        delete item.second;
    });
    
    resources.clear();
}
