#include <array>
#include <xcal/mobject/objects/axis.hpp>
#include <xcal/render/impl/opengl/utils/openglapiloadhelper.inc>

//
#include <xcal/public.h>

#include <xcal/render/impl/opengl/core/typedef.hpp>
#include <xcal/render/impl/opengl/gl/shader.hpp>
#include <xcal/render/impl/opengl/gl/shaderprogram.hpp>
#include <xcal/render/impl/opengl/object/axis.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>
#include <xcmath/xcmath.hpp>

#define ROLE OpenGLObject
#define LABEL Axis
#include <xcal/render/impl/opengl/utils/shaderinstence.hpp>
#include <xcal/utils/logmacrohelper.inc>
#include <xcmath/utils/show.hpp>
#define SHADER_ID 0
XCAL_SHADER_INSTANCE(xcal::render::opengl::object::Axis3D, SHADER_ID) {
    using namespace xcal::render::opengl;
    return GL::ShaderProgram::from_file(SHADER_FILE("line.vs"),
                                        SHADER_FILE("line.fs"));
}

void xcal::render::opengl::object::Axis3D::create() {
    vao().bind();
    vbo_ = GL::Buffer(_gl GL_ARRAY_BUFFER);
    auto vertices = std::array<_gl GLfloat, 6 * 7>{0};
    // {-1.0f,
    //                                0.0f,
    //                                0.0f,
    //                                mobject_->stroke_color().r(),
    //                                mobject_->stroke_color().g(),
    //                                mobject_->stroke_color().b(),
    //                                mobject_->stroke_color().a(),
    //                                1.0f,
    //                                0.0f,
    //                                0.0f,
    //                                mobject_->stroke_color().r(),
    //                                mobject_->stroke_color().g(),
    //                                mobject_->stroke_color().b(),
    //                                mobject_->stroke_color().a(),
    //                                0.0f,
    //                                -1.0f,
    //                                0.0f,
    //                                mobject_->stroke_color().r(),
    //                                mobject_->stroke_color().g(),
    //                                mobject_->stroke_color().b(),
    //                                mobject_->stroke_color().a(),
    //                                0.0f,
    //                                1.0f,
    //                                0.0f,
    //                                mobject_->stroke_color().r(),
    //                                mobject_->stroke_color().g(),
    //                                mobject_->stroke_color().b(),
    //                                mobject_->stroke_color().a(),
    //                                0.0f,
    //                                0.0f,
    //                                -1.0f,
    //                                mobject_->stroke_color().r(),
    //                                mobject_->stroke_color().g(),
    //                                mobject_->stroke_color().b(),
    //                                mobject_->stroke_color().a(),
    //                                0.0f,
    //                                0.0f,
    //                                1.0f,
    //                                mobject_->stroke_color().r(),
    //                                mobject_->stroke_color().g(),
    //                                mobject_->stroke_color().b(),
    //                                mobject_->stroke_color().a()};
    vbo_.bind();
    vbo_.buffer_data(vertices, _gl GL_STATIC_DRAW);

    _gl glVertexAttribFormat(0, 3, _gl GL_FLOAT, _gl GL_FALSE, 0);
    _gl glVertexAttribFormat(1, 4, _gl GL_FLOAT, _gl GL_FALSE,
                             3 * sizeof(_gl GLfloat));
    _gl glVertexAttribBinding(0, 0);
    _gl glVertexAttribBinding(1, 0);

    _gl glBindVertexBuffer(0, vbo_.id(), 0, 7 * sizeof(_gl GLfloat));

    _gl glEnableVertexAttribArray(0);
    _gl glEnableVertexAttribArray(1);
    vao().unbind();

    shader_program_ =
        render::utils::ShaderInstance<xcal::render::opengl::object::Axis3D,
                                      SHADER_ID>::instance();
    vao().unbind();
}

void xcal::render::opengl::object::Axis3D::destroy() {
    _I("Destroy Axis: " << this);
    shader_program_.reset();
    vbo_.destroy();
};

void xcal::render::opengl::object::Axis3D::render() const {
    vao().bind();
    shader_program_->use();
    shader_program_->uniform("model", mobject_.model_matrix());
    _gl glDrawArrays(_gl GL_LINES, 0, 6);
    vao().unbind();
};

xcal::render::opengl::object::Axis3D::Axis3D(mobject::Axis3D* mobject)
    : mobject_(mobject), vbo_(_gl GL_ARRAY_BUFFER) {
    _I("Create Axis: " << this << " from mobject: " << mobject_.mobject());
};

void xcal::render::opengl::object::Axis3D::update_projection_view(
    const xcmath::mat4<float_t>& projection_view) {
    _D("Update view projection for Axis: " << this << " with view_projection: "
                                           << projection_view);
    shader_program_->uniform("projection_view", projection_view);
}

XCAL_OPENGL_REGIST_OBJECT_IMPL(xcal::render::opengl::object::Axis3D, Axis3D)