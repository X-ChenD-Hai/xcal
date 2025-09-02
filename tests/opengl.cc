#include <xcal/render/impl/opengl/utils/openglapiloadhelper.inc>
//
#include <GLFW/glfw3.h>
//
#ifdef GL_BACKEND_GLBINDING
#include <glbinding-aux/ContextInfo.h>
#include <glbinding/gl/functions.h>
#include <glbinding/glbinding.h>
using namespace gl;  // 把  前缀去掉，直接写 glClear 等
#endif

#include <cstdlib>
#include <iostream>

//----------------------------------------
// 回调：窗口大小变化
void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
}

//----------------------------------------
// 初始化 GLFW + 创建窗口
GLFWwindow* init_glfw() {
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow* win =
        glfwCreateWindow(800, 600, "glbinding + GLFW", nullptr, nullptr);
    if (!win) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
    return win;
}

//----------------------------------------
// 初始化 glbinding（只需一次）
void init_glbackend() {
#ifdef GL_BACKEND_GLBINDING
    glbinding::initialize(glfwGetProcAddress, false);
#elif defined(GL_BACKEND_GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
#else
#error "No OpenGL backend defined"
#endif
}

//----------------------------------------
// 编译着色器
GLuint make_shader(const char* vs_src, const char* fs_src) {
    auto compile = [](GLenum type, const char* src) -> GLuint {
        GLuint sh = glCreateShader(type);
        glShaderSource(sh, 1, &src, nullptr);
        glCompileShader(sh);

        GLint ok;
        glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            GLsizei len;
            glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &len);
            std::string log(len, '\0');
            glGetShaderInfoLog(sh, len, &len, log.data());
            std::cerr << "Shader compile error:\n" << log << '\n';
            std::exit(EXIT_FAILURE);
        }
        return sh;
    };

    GLuint prog = glCreateProgram();
    GLuint vs = compile(GL_VERTEX_SHADER, vs_src);
    GLuint fs = compile(GL_FRAGMENT_SHADER, fs_src);

    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    GLint ok;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLsizei len;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, '\0');
        glGetProgramInfoLog(prog, len, &len, log.data());
        std::cerr << "Program link error:\n" << log << '\n';
        std::exit(EXIT_FAILURE);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

//----------------------------------------
int main() {
    GLFWwindow* win = init_glfw();
    init_glbackend();

    // 顶点数据
    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                        0.0f,  0.0f,  0.5f, 0.0f};

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // 着色器
    const char* vs = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() { gl_Position = vec4(aPos, 1.0); }
    )";
    const char* fs = R"(
        #version 330 core
        out vec4 FragColor;
        void main() { FragColor = vec4(0.2, 0.5, 0.8, 1.0); }
    )";

    GLuint prog = make_shader(vs, fs);

    // 主循环
    while (!glfwWindowShouldClose(win)) {
        if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(win, true);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(prog);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(prog);

    glfwTerminate();
    return 0;
}