#include <cstddef>
#include <cstdio>
#include <string>
#include <xcal/render/impl/opengl/utils/openglapiloadhelper.inc>
//
#include <xcal/public.h>

#include <xcal/render/impl/opengl/opengl_render.hpp>
#include <xcal/render/impl/opengl/utils/glfwdarkheadersupport.inc>
#include <xcmath/utils/show.hpp>

#include "core/typedef.hpp"
#include "xcal/mobject/core/mobject_types.hpp"

//
#ifdef GL_BACKEND_GLBINDING
#    include <glbinding-aux/ContextInfo.h>
#    include <glbinding/gl/functions.h>
#    include <glbinding/glbinding.h>
#endif

//
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#undef OUT  // undefine OUT macro to avoid conflict with xcal::OUT
#define ROLE OpenGL
#define LABEL OpenGLRender
#include <xcal/utils/logmacrohelper.inc>

#define CONST_MOBJECT_PTR(mobj) static_cast<const xcal::mobject::MObject*>(mobj)
namespace xcal::render::opengl {
struct UIState {
    struct ObjectHandle {
        using mobject_t = xcal::mobject::MObject;
        bool_t changed = false;
        mobject_t* obj;
        std::string name;
        std::string type;
        float_t x, y;
        float_t depth;
        ObjectHandle(mobject_t* obj)
            : obj(obj),
              name(std::string(xcal::to_string(obj->type())) + ": " +
                   std::to_string((size_t)obj)),
              type(xcal::to_string(obj->type())),
              x(CONST_MOBJECT_PTR(obj)->pos().x()),
              y(CONST_MOBJECT_PTR(obj)->pos().y()),
              depth(CONST_MOBJECT_PTR(obj)->depth()) {}
    };

    bool show = true;
    std::vector<ObjectHandle> object_handles;
    OpenGLRender* renderer = nullptr;
    UIState(OpenGLRender* renderer) : renderer(renderer) {}
    float_t tmp;
    void flush() {
        object_handles.clear();
        if (renderer && renderer->scene()) {
            for (auto& obj : renderer->scene()->mobjects()) {
                object_handles.emplace_back(obj.get());
            }
        }
    }
    void render_obj(ObjectHandle& obj, int id) {
        namespace I = ImGui;
        I::PushID(id);
        if (I::CollapsingHeader(obj.name.c_str())) {
            I::Text("pos: ");
            tmp = CONST_MOBJECT_PTR(obj.obj)->pos().x();
            if (I::InputFloat("X", &tmp)) {
                obj.obj->pos().x() = tmp;
                _D("updating x of object: " << obj.obj << " to: " << tmp
                                            << " change state: "
                                            << obj.obj->pos().is_changed());
            }
            tmp = CONST_MOBJECT_PTR(obj.obj)->pos().y();
            if (I::InputFloat("Y", &tmp)) obj.obj->pos().y() = tmp;
            I::Text("depth: ");
            tmp = CONST_MOBJECT_PTR(obj.obj)->depth();
            if (I::InputFloat("Depth", &tmp)) obj.obj->depth() = tmp;
        }
        I::PopID();
    }
    void render() {
        namespace I = ImGui;
        if (!show) return;
        I::Begin("Hello, world!", &show);
        I::SetWindowFontScale(2);
        for (size_t i = 0; i < object_handles.size(); ++i) {
            render_obj(object_handles[i], (int)i);
        }
        I::End();
    }
};
}  // namespace xcal::render::opengl

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    static_cast<xcal::render::opengl::OpenGLRender*>(
        glfwGetWindowUserPointer(window))
        ->framebuffer_size_callback(window, w, h);
}

void init_glbackend() {
#ifdef GL_BACKEND_GLBINDING
    glbinding::initialize(glfwGetProcAddress, false);
#elif defined(GL_BACKEND_GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
#else
#    error "No OpenGL backend defined"
#endif
}

xcal::render::opengl::OpenGLRender::OpenGLRender(Scene* scene)
    : xcal::render::Render(scene), ui_state_(std::make_unique<UIState>(this)) {
    _I("OpenGLRender created: " _SELF);
    setup_glfw();
    setup_gl();
    setup_imgui();
    setup_scene();
}
xcal::render::opengl::OpenGLRender::~OpenGLRender() {
    objects_.clear();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (window_) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    glfwTerminate();
    _I("OpenGLRender destroyed: " _SELF);
};
void xcal::render::opengl::OpenGLRender::show(size_t width, size_t height) {
    if (!window_) {
        _E("GLFW window is not created");
        return;
    }
    glfwSetWindowSize(window_, width, height);
    glfwMakeContextCurrent(window_);
    _gl glClearColor(background_color_.r(), background_color_.g(),
                     background_color_.b(), background_color_.a());
    for (auto& obj : objects_) {
        obj.second->create();
    }
    ::framebuffer_size_callback(window_, width, height);
    _I("show loop started");
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        render_ui();

        ImGui::Render();
        _gl glClear(_gl GL_COLOR_BUFFER_BIT | _gl GL_DEPTH_BUFFER_BIT);
        render_frame();
        // pixels = read_pixels_char();
        // ofs.write(pixels.data(), pixels.size());
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window_);
    }
    _I("show loop ended");
    _I("destroying objects");
    for (auto& obj : objects_) obj.second->destroy();
    _I("objects destroyed ");
}
void xcal::render::opengl::OpenGLRender::render_frame() {
    if (!scene()->cameras().empty()) {
        const auto& cam = scene()->cameras().front();
        if (cam->should_update()) {
            for (auto& obj : objects_) {
                _D("updating object: " << obj.first
                                       << " with camera: " << cam.get());
                _D("pv_matrix: " << cam->pv_matrix());
                obj.second->update_projection_view(cam->pv_matrix());
            }
        }
    }
    for (const auto& obj : objects_) {
        auto& obj_ptr = obj.second;
        if (obj_ptr) {
            obj_ptr->render();
        }
    }
};
void xcal::render::opengl::OpenGLRender::set_scene(Scene* scene) {
    Render::set_scene(scene);
    setup_scene();
};
void xcal::render::opengl::OpenGLRender::setup_scene() {
    _I("setup_scene" << scene());
    objects_.clear();
    if (!scene()) {
        _W("scene is null");
        return;
    }
    _D("Number of mobjects in scene: " << scene()->mobjects().size());
    for (auto& obj : scene()->mobjects()) {
        _D("Processing mobject: " << obj.get());
        auto obj_ptr = object::create(obj.get());
        if (!obj_ptr) {
            _E("Failed to create object for " << obj.get());
            continue;
        }
        objects_.insert({obj.get(), std::move(obj_ptr)});
    }
    ui_state_->flush();
};
void xcal::render::opengl::OpenGLRender::framebuffer_size_callback(
    GLFWwindow* window, int w, int h) {
    // _D("framebuffer_size_callback: " << w << "x" << h);

    // 计算保持宽高比的视口尺寸
    float target_aspect = aspect_;
    int viewport_width = w;
    int viewport_height = h;
    int viewport_x = 0;
    int viewport_y = 0;

    // 计算实际宽高比
    float actual_aspect = static_cast<float>(w) / static_cast<float>(h);

    if (actual_aspect > target_aspect) {
        // 窗口太宽，上下加黑边
        viewport_width = static_cast<int>(h * target_aspect);
        viewport_height = h;
        viewport_x = (w - viewport_width) / 2;
        viewport_y = 0;
    } else {
        // 窗口太高，左右加黑边
        viewport_width = w;
        viewport_height = static_cast<int>(w / target_aspect);
        viewport_x = 0;
        viewport_y = (h - viewport_height) / 2;
    }

    // 设置视口
    _gl glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
    _gl glClearColor(background_color_.r(), background_color_.g(),
                     background_color_.b(), background_color_.a());

    // _D("Viewport set to: " << viewport_x << ", " << viewport_y << ", "
    //                        << viewport_width << ", " << viewport_height);
}
std::vector<char> xcal::render::opengl::OpenGLRender::read_pixels_char() const {
    _gl GLint width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    std::vector<char> pixels(width * height * 4);  // RGBA
    _gl glReadPixels(0, 0, width, height, _gl GL_RGBA, _gl GL_UNSIGNED_BYTE,
                     pixels.data());
    std::cerr << "Read: " << width << "x" << height << " pixels\n";
    return pixels;
}
void xcal::render::opengl::OpenGLRender::setup_glfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window_ = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (window_ == nullptr) {
        glfwTerminate();
        _D("Failed to create GLFW window");
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window_);
    if (!enable_window_dark_titlebar(window_)) {
        _D("Failed to enable dark titlebar");
    }
    glfwSetWindowUserPointer(window_, this);
};
void xcal::render::opengl::OpenGLRender::setup_gl() {
    init_glbackend();
    _gl glEnable(_gl GL_DEPTH_TEST);
    _gl glDepthFunc(_gl GL_LESS);
    _gl glEnable(_gl GL_BLEND);
    _gl glBlendFunc(_gl GL_SRC_ALPHA, _gl GL_ONE_MINUS_SRC_ALPHA);
    glfwSetFramebufferSizeCallback(window_, ::framebuffer_size_callback);
};
void xcal::render::opengl::OpenGLRender::setup_imgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
};

void xcal::render::opengl::OpenGLRender::render_ui() { ui_state_->render(); };