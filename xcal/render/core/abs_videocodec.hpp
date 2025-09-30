#include <xcal/public.h>

#include <vector>
namespace xcal::render::codec {
class XCAL_API AbsVideoCodec {
   private:
    std::string filename_;
    int width_ = 0;
    int height_ = 0;
    int frame_rate_ = 0;

   public:
    AbsVideoCodec(std::string_view filename, int width, int height,
                  int frame_rate)
        : filename_(filename),
          width_(width),
          height_(height),
          frame_rate_(frame_rate) {}
    virtual ~AbsVideoCodec() = default;
    virtual bool_t open() = 0;
    virtual bool_t append_frame(const std::vector<char>&) = 0;
    virtual bool_t finish() = 0;
    const std::string& filename() const { return filename_; }
    int width() const { return width_; }
    int height() const { return height_; }
    int frame_rate() const { return frame_rate_; }
    virtual std::string name() { return ""; }
};
}  // namespace xcal::render::codec