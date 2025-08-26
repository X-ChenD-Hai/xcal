#pragma once
#include <public.h>

#include <mobject/mobject.hpp>
#include <type_traits>
#include <vector>

namespace xcal::scene {
class AbsScene {
   private:
    std::vector<mobject::AbsMObject_ptr> mobjects_;

   public:
    virtual mobject::AbsMObject* add(mobject::mobject_ptr obj) {
        return mobjects_.emplace_back(std::move(obj)).get();
    }
    virtual mobject::AbsMObject* add(mobject::MObject* obj) {
        return mobjects_.emplace_back(obj).get();
    }
    template <class T>
        requires std::is_base_of_v<mobject::MObject, T>
    T* add(T&& obj) {
        return mobjects_.emplace_back(std::make_unique<T>(std::move(obj)))
            .get();
    }
    template <class T, typename... Args>
        requires std::constructible_from<T, Args...> &&
                 std::is_base_of_v<mobject::MObject, T>
    T* add(Args&&... args) {
        return static_cast<T*>(
            add(std::make_unique<T>(std::forward<Args>(args)...)));
    }
    std::vector<mobject::AbsMObject_ptr>& mobjects() { return mobjects_; }
};
}  // namespace xcal::scene