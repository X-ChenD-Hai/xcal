#include <utils/openglapiloadhelper.inc>
//
#include XCAL_OPENGL_RENDERER_CONFIG_HEADER

#include <gl/shader.hpp>
#include <gl/shaderprogram.hpp>
#include <object/circle.hpp>
#include <object/object.hpp>
#include <xcmath/xcmath.hpp>

#define ROLE OpenGLObject
#define LABEL Circle
#include <utils/shaderinstence.hpp>
#include <xcal/utils/logmacrohelper.inc>
#include <xcmath/utils/show.hpp>
#define SHADER_ID 0
XCAL_SHADER_INSTANCE(xcal::render::opengl::object::Circle, SHADER_ID) {
    using namespace xcal::render::opengl;
    return GL::ShaderProgram::from_file(SHADER_FILE("line.vs"),
                                        SHADER_FILE("line.fs"));
}

void xcal::render::opengl::object::Circle::create() {
    vao().bind();
    vbo_ = GL::Buffer(_gl GL_ARRAY_BUFFER);
    vbo_.bind();
    const float_t radius = mobject_->radius();
    _D("Create Circle: " << mobject_.mobject() << " with radius: " << radius
                         << " and depth: " << mobject_->pos().value().z());

    // Generate vertices for circle using triangle fan
    // Center vertex first, then circumference points
    std::vector<_gl GLfloat> vertices;
    vertices.reserve((segments_ + 2) *
                     6);  // (center + segments + duplicate first
                          // point) * 6 floats per vertex

    // Center vertex
    vertices.insert(vertices.end(), {0.0f, 0.0f, mobject_->pos().value().z()});
    vertices.insert(vertices.end(),
                    {mobject_->stroke_color().r(), mobject_->stroke_color().g(),
                     mobject_->stroke_color().b()});

    // Circumference vertices
    for (int i = 0; i <= segments_; ++i) {
        float_t angle = 2.0f * xcmath::PI * i / segments_;
        float_t x = radius * cos(angle);
        float_t y = radius * sin(angle);
        vertices.insert(vertices.end(), {x, y, mobject_->pos().value().z()});
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

    shader_program_ =
        render::utils::ShaderInstance<Circle, SHADER_ID>::instance();
    vao().unbind();
};

void xcal::render::opengl::object::Circle::destroy() {
    _I("Destroy Circle: " << this);
    shader_program_.reset();
    vbo_.destroy();
};

void xcal::render::opengl::object::Circle::render() const {
    vao().bind();
    shader_program_->use();
    shader_program_->uniform("model", mobject_.model_matrix());
    _gl glDrawArrays(_gl GL_TRIANGLE_FAN, 0,
                     segments_ + 2);  // +2 for center and duplicate first point
    vao().unbind();
};

xcal::render::opengl::object::Circle::Circle(mobject::Circle* mobject)
    : mobject_(mobject), vbo_(_gl GL_ARRAY_BUFFER) {
    _I("Create Circle: " << this << " from mobject: " << mobject_.mobject());
};

XCAL_OPENGL_REGIST_OBJECT_IMPL(xcal::render::opengl::object::Circle, Circle)
void xcal::render::opengl::object::Circle::update_projection_view(
    const xcmath::mat4<float_t>& projection_view) {
    _D("Update view projection for Circle: "
       << this << " with view_projection: " << projection_view);
    shader_program_->uniform("projection_view", projection_view);
}
