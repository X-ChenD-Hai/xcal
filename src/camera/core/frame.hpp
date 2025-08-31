#include <public.h>

#include <cstddef>

namespace xcal::camera {
enum class ColorFormat { BGR, RGB, RGBA, Gray, YUV420, YUV422, YUV444 };

class Frame {
   public:
    Frame() = default;
    virtual ~Frame() = default;

   public:
    virtual size_t width() = 0;
    virtual size_t height() = 0;
    virtual ColorFormat color_format() = 0;
    virtual void* data() = 0;
    virtual size_t size() = 0;
};
}  // namespace xcal::camera