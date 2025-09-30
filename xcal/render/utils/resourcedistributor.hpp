#pragma once
#include <memory>
#include <unordered_map>
namespace xcal::render::utils {
template <typename T, typename Catgory = void, size_t Id = 0>
struct ResourceAllocator {
    static std::shared_ptr<T> allocate();
};
template <typename T, typename Catgory, size_t Id>
std::shared_ptr<T> ResourceAllocator<T, Catgory, Id>::allocate() {
    return std::make_shared<T>();
}
template <typename T, typename Catgory = void, size_t Id = 0>
class StaticResourceDistributor {
    static std::weak_ptr<T> resource_;

   public:
    static std::shared_ptr<T> instance() {
        auto resource = resource_.lock();
        if (!resource) {
            resource = ResourceAllocator<T, Catgory, Id>::allocate();
            resource_ = resource;
        }
        return resource;
    }
};
template <typename T, typename Catgory, size_t Id>
std::weak_ptr<T> StaticResourceDistributor<T, Catgory, Id>::resource_;

template <class T, class KeyType, class Catgory = void, size_t Id = 0>
struct DynamicResourceAllocator {
    template <typename... Args>
    static std::shared_ptr<T> allocate(Args&&... args) {
        static_assert(false,
                      "DynamicResourceAllocator::allocate not implemented");
    }
};
template <class K, class V>
struct DynamicResources {
    static std::unordered_map<K, std::weak_ptr<V>> resources;
    static size_t last_size;
    static void gc() {
        std::vector<K> to_erase;
        for (auto& pair : resources) {
            if (pair.second.expired()) {
                to_erase.push_back(pair.first);
            }
        }
        for (const auto& id : to_erase) {
            resources.erase(id);
        }
        last_size = resources.size();
    }
};
template <class K, class V>
std::unordered_map<K, std::weak_ptr<V>> DynamicResources<K, V>::resources;
template <class K, class V>
size_t DynamicResources<K, V>::last_size = 0;

template <typename T, class ResourceId, size_t ClearedThreshold = 100>
class DynamicResourceDistributor {
   public:
    using KeyType = typename ResourceId::type;
    using Resources = DynamicResources<KeyType, T>;
    template <class Catgory = void, size_t Id = 0, typename... Args>
    static std::shared_ptr<T> instance(Args&&... args) {
        using Allocator = DynamicResourceAllocator<T, KeyType, Catgory, Id>;
        auto& resources_ = Resources::resources;
        auto last_size_ = Resources::last_size;
        auto id = ResourceId::template allocate<Catgory, Id, Args...>(
            std::forward<Args>(args)...);
        std::shared_ptr<T> resource;
        if (auto it = resources_.find(id); it == resources_.end()) {
            resource = Allocator::allocate(std::forward<Args>(args)...);
            resources_[id] = resource;
        } else {
            resource = it->second.lock();
            if (!resource) {
                resource = Allocator::allocate(std::forward<Args>(args)...);
                it->second = resource;
            }
        }
        if (resources_.size() > last_size_ + ClearedThreshold) {
            Resources::gc();
        }
        return resource;
    }
};
}  // namespace xcal::render::opengl::utils
