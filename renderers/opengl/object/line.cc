#include <utils/openglapiloadhelper.inc>

//
#include XCAL_OPENGL_RENDERER_CONFIG_HEADER

#include <gl/shader.hpp>
#include <gl/shaderprogram.hpp>
#include <object/line.hpp>
#include <object/object.hpp>
#include <xcmath/xcmath.hpp>

#define ROLE OpenGLObject
#define LABEL Line
#include <utils/shaderinstence.hpp>
#include <xcal/utils/logmacrohelper.inc>
#include <xcmath/utils/show.hpp>
static constexpr auto SHADER_ID = 0;
static constexpr auto BUFFER_ID = 0;

XCAL_SHADER_INSTANCE(xcal::render::opengl::object::Line, SHADER_ID) {
    using namespace xcal::render::opengl;
    return GL::ShaderProgram::from_file(SHADER_FILE("line1.vs"),
                                        SHADER_FILE("line1.fs"));
}
XCAL_BUFFER_INSTANCE(xcal::render::opengl::object::Line, BUFFER_ID) {
    auto buffer =
        std::make_shared<xcal::render::opengl::GL::Buffer>(_gl GL_ARRAY_BUFFER);
    buffer->bind();
    buffer->buffer_data(
        std::array<_gl GLfloat, 6>{
            -0.5f, -0.5f,
            -0.5f,  //
            0.5f, 0.5f,
            0.5f,  //
        },
        _gl GL_STATIC_DRAW);
    buffer->unbind();
    return buffer;
}
using vao_sp = std::shared_ptr<xcal::render::opengl::GL::VertexArrayObject>;
using vbo_sp = std::shared_ptr<xcal::render::opengl::GL::Buffer>;
using shader_sp = std::shared_ptr<xcal::render::opengl::GL::ShaderProgram>;
struct StaticLine {
    vao_sp vao;
    vbo_sp vbo;
    shader_sp shader_program;
    StaticLine() {
        using namespace xcal::render::opengl;
        namespace utils = xcal::render::utils;
        vao = utils::VertexArrayObjectInstance<object::Line, 0>::instance();
        vao->bind();
        vbo = utils::BufferInstance<object::Line, BUFFER_ID>::instance();
        vbo->bind();
        _gl glEnableVertexAttribArray(0);
        _gl glVertexAttribPointer(0, 3, _gl GL_FLOAT, _gl GL_FALSE,
                                  3 * sizeof(float),  // stride
                                  (void*)nullptr);    // offset
        shader_program =
            utils::ShaderInstance<object::Line, SHADER_ID>::instance();
    }
};

XCAL_DEFINE_STATIC_GLOBJECT(StaticLine, xcal::render::opengl::object::Line, 0) {
    return std::make_shared<StaticLine>();
}

void xcal::render::opengl::object::Line::create() {
    static_line_ = XCAL_STATIC_GLOBJECT(StaticLine, Line, 0);
    _I("Create Line: " << this << " with mobject: " << mobject_.mobject());
};
void xcal::render::opengl::object::Line::destroy() {
    _I("Destroy Line: " << this);
    static_line_ = nullptr;
};
void xcal::render::opengl::object::Line::render() const {
    static_line_->vao->bind();
    static_line_->shader_program->use();
    update_ubo_data();
    _gl glBindBufferBase(_gl GL_UNIFORM_BUFFER, 0, ubo_.id());
    _gl glDrawArrays(_gl GL_LINES, 0, 2);
    static_line_->vao->unbind();
};
xcal::render::opengl::object::Line::Line(mobject::Line* mobject)
    : mobject_(mobject), ubo_(_gl GL_UNIFORM_BUFFER) {
    _I("Create Line: " << this << " from mobject: " << mobject_.mobject());
};

void xcal::render::opengl::object::Line::update_projection_view(
    const xcmath::mat4<float_t>& projection_view) {
    _D("Update view projection for Line: " << this << " with view_projection: "
                                           << projection_view);
    static_line_->shader_program->uniform("projection_view", projection_view);
};
XCAL_OPENGL_REGIST_OBJECT_IMPL(xcal::render::opengl::object::Line, Line)

void xcal::render::opengl::object::Line::update_ubo_data() const {
    if (mobject_->stroke_color().is_changed() ||
        mobject_->direct().is_changed() ||
        mobject_.model_matrix_should_update()) {
        ubo_.bind();
        ubo_data_.direction =
            xcmath::vec4<float_t>{mobject_->direct().value(), 0.f};
        ubo_data_.color = mobject_->stroke_color();
        ubo_data_.model = mobject_.model_matrix().T();
        ubo_.buffer_data(&ubo_data_, sizeof(ubo_data_), _gl GL_DYNAMIC_DRAW);
        ubo_.unbind();
        mobject_->stroke_color().reset_changed();
        mobject_->direct().reset_changed();
    }
};