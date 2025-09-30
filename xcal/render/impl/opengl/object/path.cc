#include <xcal/mobject/objects/path.hpp>
#include <xcal/render/impl/opengl/gl/buffer.hpp>
#include <xcal/render/impl/opengl/object/path.hpp>
#include <xcal/render/impl/opengl/utils/openglapiloadhelper.inc>
//

#define ROLE OpenGLObject
#define LABEL Path
#include <xcal/render/impl/opengl/utils/shaderinstence.hpp>
#include <xcal/utils/logmacrohelper.inc>
#include <xcmath/utils/show.hpp>
constexpr static auto STROKE_SHADER_ID = 0;
constexpr static auto FILL_SHADER_ID = 1;
XCAL_SHADER_INSTANCE(xcal::render::opengl::object::Path, STROKE_SHADER_ID) {
    using namespace xcal::render::opengl;
    return GL::ShaderProgram::from_file(SHADER_FILE("path/stroke.vs"),
                                        SHADER_FILE("path/stroke.fs"));
}
XCAL_SHADER_INSTANCE(xcal::render::opengl::object::Path, FILL_SHADER_ID) {
    using namespace xcal::render::opengl;
    return GL::ShaderProgram::from_file(SHADER_FILE("path/fill.vs"),
                                        SHADER_FILE("path/fill.fs"));
}

xcal::render::opengl::object::Path::Path(mobject::Path *mobject)
    : mobject_(mobject),
      position_vbo_(_gl GL_ARRAY_BUFFER),
      stroke_vbo_(_gl GL_ARRAY_BUFFER),
      fill_vbo_(_gl GL_ARRAY_BUFFER) {
    _I("Create Path: " << this << " from mobject: " << mobject_.mobject());
}
void xcal::render::opengl::object::Path::create() {
    auto count = mobject_->points().count() + 1;
    std::vector<xcmath::vec3<_gl GLfloat>> vertices(count);
    std::vector<xcmath::vec4<_gl GLfloat>> strokes_colors(count);
    std::vector<xcmath::vec4<_gl GLfloat>> fill_colors(count);
    for (size_t i = 0; i < mobject_->points().count(); ++i) {
        vertices[i] = xcmath::vec3<_gl GLfloat>(
            mobject_->points()[i].x(), mobject_->points()[i].y(), 0.0f);
        strokes_colors[i] = xcmath::vec4<_gl GLfloat>(mobject_->stroke_color());
        fill_colors[i] = xcmath::vec4<_gl GLfloat>(mobject_->fill_color());
    }
    vertices[count - 1] = xcmath::vec3<_gl GLfloat>(
        mobject_->points()[0].x(), mobject_->points()[0].y(), 0.0f);
    strokes_colors[count - 1] =
        xcmath::vec4<_gl GLfloat>(mobject_->stroke_color());
    fill_colors[count - 1] = xcmath::vec4<_gl GLfloat>(mobject_->fill_color());
    vao().bind();
    position_vbo_ = GL::Buffer(_gl GL_ARRAY_BUFFER);
    position_vbo_.bind();
    position_vbo_.buffer_data(vertices, _gl GL_STATIC_DRAW);
    stroke_vbo_ = GL::Buffer(_gl GL_ARRAY_BUFFER);
    stroke_vbo_.bind();
    stroke_vbo_.buffer_data(strokes_colors, _gl GL_STATIC_DRAW);
    fill_vbo_ = GL::Buffer(_gl GL_ARRAY_BUFFER);
    fill_vbo_.bind();
    fill_vbo_.buffer_data(fill_colors, _gl GL_STATIC_DRAW);
    _gl glVertexAttribFormat(0, 3, _gl GL_FLOAT, _gl GL_FALSE, 0);
    _gl glVertexAttribFormat(1, 4, _gl GL_FLOAT, _gl GL_FALSE, 0);
    _gl glVertexAttribFormat(2, 4, _gl GL_FLOAT, _gl GL_FALSE, 0);
    _gl glVertexAttribBinding(0, 0);
    _gl glVertexAttribBinding(1, 1);
    _gl glVertexAttribBinding(2, 2);
    _gl glBindVertexBuffer(0, position_vbo_.id(), 0,
                           sizeof(xcmath::vec3<_gl GLfloat>));
    _gl glBindVertexBuffer(1, stroke_vbo_.id(), 0,
                           sizeof(xcmath::vec4<_gl GLfloat>));
    _gl glBindVertexBuffer(2, fill_vbo_.id(), 0,
                           sizeof(xcmath::vec4<_gl GLfloat>));
    _gl glEnableVertexAttribArray(0);
    _gl glEnableVertexAttribArray(1);
    _gl glEnableVertexAttribArray(2);
    namespace utils = xcal::render::utils;
    stroke_shader_program_ =
        utils::ShaderInstance<Path, STROKE_SHADER_ID>::instance();
    fill_shader_program_ =
        utils::ShaderInstance<Path, FILL_SHADER_ID>::instance();
}

void xcal::render::opengl::object::Path::destroy() {
    _I("Destroy Path: " _SELF);
    stroke_shader_program_.reset();
    fill_shader_program_.reset();
    stroke_vbo_.destroy();
    fill_vbo_.destroy();
    position_vbo_.destroy();
    vao().unbind();
}
void xcal::render::opengl::object::Path::render() const {
    vao().bind();
    if (mobject_->stroke_color().a() > 0.0f) {
        stroke_shader_program_->use();
        stroke_shader_program_->uniform("model", mobject_.model_matrix());
        _gl glDrawArrays(_gl GL_LINE_STRIP, 0,
                         mobject_->points().closed()
                             ? (mobject_->points().count() + 1)
                             : mobject_->points().count());
    }
    if (mobject_->fill_color().a() > 0.0f) {
        fill_shader_program_->use();
        fill_shader_program_->uniform("model", mobject_.model_matrix());
        _gl glDrawArrays(_gl GL_TRIANGLE_FAN, 0,
                         mobject_->points().count() + 1);
    }
};
void xcal::render::opengl::object::Path::update_projection_view(
    const xcmath::mat4<float_t> &projection_view) {
    stroke_shader_program_->uniform("projection_view", projection_view);
    fill_shader_program_->uniform("projection_view", projection_view);
}

XCAL_OPENGL_REGIST_OBJECT_IMPL(xcal::render::opengl::object::Path, Path)
