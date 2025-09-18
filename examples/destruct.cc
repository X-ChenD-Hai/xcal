
class Mobject {
   public:
    virtual ~Mobject() {}
};

template <typename T>
class PosMObject {
   private:
    size_t pos_;

   public:
    T *set_pos(size_t pos) {
        pos_ = pos;
        return static_cast<T *>(this);
    }

   public:
};
template <typename T>
class SizeMObject {
   private:
    size_t size_;

   public:
    T *set_size(size_t size) {
        size_ = size;
        return static_cast<T *>(this);
    }

   public:
    ~SizeMObject() {}
};

template <class _Derived, template <class> class... Args>
class ComposedMobject : public Mobject, public Args<_Derived>... {
   public:
    virtual ~ComposedMobject() {}
};

class MyObject : public ComposedMobject<MyObject, PosMObject, SizeMObject> {
   public:
};

int main() {
    auto myobject = new MyObject{};

    myobject->set_pos(11)->set_pos(11)->set_size(11)->set_size(11);

    Mobject *m = myobject;

    delete m;
    return 0;
}