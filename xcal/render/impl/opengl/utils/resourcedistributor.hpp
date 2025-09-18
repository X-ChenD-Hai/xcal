#include <memory>
#include <unordered_map>
static constexpr size_t CLEAR_THRESHOLD = 100;

namespace xcal::render::opengl::utils {
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

template <typename T, typename Catgory = void, size_t Id = 0>
class DynamicResourceDistributor {
    static std::unordered_map<size_t, std::weak_ptr<T>> resources_;
    static size_t last_size_;

   public:
    static std::shared_ptr<T> instance(size_t id) {
        auto resource = resources_[id].lock();
        if (!resource) {
            resource = ResourceAllocator<T, Catgory, Id>::allocate();
            resources_[id] = resource;
        }
        if (resources_.size() > last_size_ + CLEAR_THRESHOLD) {
            resources_.erase(
                std::remove_if(
                    resources_.begin(), resources_.end(),
                    [](const std::pair<size_t, std::weak_ptr<T>>& p) {
                        return p.second.expired();
                    }),
                resources_.end());
            last_size_ = resources_.size();
        }
        return resource;
    }
};
template <typename T, typename Catgory, size_t Id>
std::unordered_map<size_t, std::weak_ptr<T>>
    DynamicResourceDistributor<T, Catgory, Id>::resources_;
template <typename T, typename Catgory, size_t Id>
size_t DynamicResourceDistributor<T, Catgory, Id>::last_size_ = 0;
}  // namespace xcal::render::opengl::utils
