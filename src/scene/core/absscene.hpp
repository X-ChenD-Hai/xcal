#pragma once
#include <public.h>

#include <mobject/core/absmobject.hpp>
#include <type_traits>
#include <vector>

namespace xcal::scene {

template <typename ObjectPtr = mobject::AbsMObject_ptr>
class AbsScene {
   private:
    using object_t = ObjectPtr::element_type;
    std::vector<ObjectPtr> mobjects_;

   public:
    // 添加unique_ptr对象
    virtual typename ObjectPtr::element_type* add(ObjectPtr obj) {
        return mobjects_.emplace_back(std::move(obj)).get();
    }

    // 添加裸指针对象（转换为unique_ptr）
    virtual typename ObjectPtr::element_type* add(
        typename ObjectPtr::element_type* obj) {
        return mobjects_.emplace_back(obj).get();
    }
    template <typename T>
        requires std::is_base_of_v<object_t, T>
    T* add(T&& obj) {
        return (T*)mobjects_.emplace_back((object_t*)new T{std::move(obj)})
            .get();
    }

    // 添加对象并构造
    template <class T, typename... Args>
        requires std::constructible_from<T, Args...> &&
                 std::is_base_of_v<typename ObjectPtr::element_type, T>
    T* add(Args&&... args) {
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T* result = ptr.get();
        mobjects_.emplace_back(std::move(ptr));
        return result;
    }

    // 获取对象列表
    std::vector<ObjectPtr>& mobjects() { return mobjects_; }
    const std::vector<ObjectPtr>& mobjects() const { return mobjects_; }

    virtual ~AbsScene() = default;
};

}  // namespace xcal::scene
