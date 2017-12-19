#pragma once

#include <string>
#include <unordered_map>

namespace Anyon
{
    class ResourceManager
    {
        friend class Core;
        
    public:
        class Resource
        {
            friend class ResourceManager;
            
        public:
            Resource(const std::string &name, ResourceManager *resMan);
            virtual ~Resource();
            
            virtual bool Valid() const = 0;
            
            const std::string& Name() const;
            void Acquire();
            void Release();
            unsigned References() const;
            
        private:
            ResourceManager *resMan;
            std::string name;
            unsigned refs = 1;
        };
        
        Resource* Find(const std::string &name) const;
        
        ResourceManager(ResourceManager const &) = delete;
        ResourceManager& operator = (ResourceManager const &) = delete;
        ResourceManager& operator = (ResourceManager &&) = delete;
        
    private:
        ResourceManager(){};
        ~ResourceManager(){};
        
        std::unordered_map<std::string, class ResourceManager::Resource*> resources;
        
        void AddResource(Resource *res);
        void RemoveResource(Resource *res);
        void ReleaseAll();
    };
}
