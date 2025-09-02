#include <xcal/render/impl/opengl/utils/openglapiloadhelper.inc>
//
#include <xcal/public.h>

#include <xcal/render/impl/opengl/gl/shader.hpp>
#include <xcal/render/impl/opengl/gl/shaderprogram.hpp>
#include <xcal/render/impl/opengl/object/circle.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>
#include <xcmath/xcmath.hpp>

#define XCAL_OUT_TO_STDERR
#define ROLE OpenGLObject
#define LABEL Circle
#include <xcal/render/impl/opengl/utils/shaderinstence.hpp>
#include <xcal/utils/logmacrohelper.inc>
#include <xcmath/utils/show.hpp>
#define SHADER_ID 0
XCAL_SHADER_INSTANCE(xcal::render::opengl::object::Circle, SHADER_ID) {
    return GL::ShaderProgram::from_file("res/line.vs", "res/line.fs");
}

void xcal::render::opengl::object::Circle::create() {
    vao().bind();
    vbo_.bind();

    const float_t radius = mobject_->radius();
    _D("Create Circle: " << mobject_.mobject() << " with radius: " << radius);

    // Generate vertices for circle using triangle fan
    // Center vertex first, then circumference points
    std::vector<_gl GLfloat> vertices;
    vertices.reserve((segments_ + 2) *
                     6);  // (center + segments + duplicate first point) * 6
                          // floats per vertex

    // Center vertex
    vertices.insert(vertices.end(), {0.0f, 0.0f, 0.0f});
    vertices.insert(vertices.end(),
                    {mobject_->stroke_color().r(), mobject_->stroke_color().g(),
                     mobject_->stroke_color().b()});

    // Circumference vertices
    for (int i = 0; i <= segments_; ++i) {
        float_t angle = 2.0f * xcmath::PI * i / segments_;
        float_t x = radius * cos(angle);
        float_t y = radius * sin(angle);
        vertices.insert(vertices.end(), {x, y, 0.0f});
        vertices.insert(vertices.end(), {mobject_->stroke_color().r(),
                                         mobject_->stroke_color().g(),
                                         mobject_->stroke_color().b()});
    }

    vbo_.buffer_data(vertices.data(), vertices.size() * sizeof(float),
                     _gl GL_STATIC_DRAW);

    _gl glEnableVertexAttribArray(0);
    _gl glVertexAttribPointer(0, 3, _gl GL_FLOAT, _gl GL_FALSE,
                              6 * sizeof(float),            // stride
                              (void*)(0 * sizeof(float)));  // offset

    // Color attribute: location 1, each vertex 3 floats, offset 3*float
    _gl glEnableVertexAttribArray(1);
    _gl glVertexAttribPointer(1, 3, _gl GL_FLOAT, _gl GL_FALSE,
                              6 * sizeof(float),            // stride
                              (void*)(3 * sizeof(float)));  // offset

    shader_program_ = utils::ShaderInstance<Circle, SHADER_ID>::instance();
};

void xcal::render::opengl::object::Circle::destroy() {
    _I("Destroy Circle: " << this);
    shader_program_.reset();
    vbo_.destroy();
};

void xcal::render::opengl::object::Circle::render() const {
    vao().bind();
    shader_program_->use();
    shader_program_->uniform("model", mobject_.model_materix());
    _gl glDrawArrays(_gl GL_TRIANGLE_FAN, 0,
                     segments_ + 2);  // +2 for center and duplicate first point
};

xcal::render::opengl::object::Circle::Circle(mobject::Circle* mobject)
    : mobject_(mobject), vbo_(_gl GL_ARRAY_BUFFER) {
    _I("Create Circle: " << this << " from mobject: " << mobject_.mobject());
};

XCAL_OPENGL_REGIST_OBJECT_IMPL(xcal::render::opengl::object::Circle, Circle)
