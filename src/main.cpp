// main.cpp

#include <glad/glad.h>
#include <GL/freeglut.h>

#include <iostream>

GLuint VAO;
GLuint VBO;
GLuint shaderProgram;


// fica praticamente igual ao arquivo GLSL original (OpenGL Shading Language).
const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fragColor;

void main()
{
    gl_Position = vec4(position, 1.0);
    fragColor = color;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

in vec3 fragColor;

out vec4 outColor;

void main()
{
    outColor = vec4(fragColor, 1.0);
}
)";

/*********************************
        Vértices
           ↓
        Vertex Shader
           ↓
        Rasterização
           ↓
        Fragment Shader
           ↓
        Tela
*********************************/

void createShaders()
{

    GLuint vertexShader =
        glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        NULL
    );

    glCompileShader(vertexShader);

    // Fragment Shader: define a cor final dos pixels que serão desenhados na tela.
    GLuint fragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderSource,
        NULL
    );

    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void createTriangle()
{
    float vertices[] =
    {
        // posição        // cor

         0.0f,  0.5f, 0.0f,
         1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f, 0.0f,
         0.0f,  1.0f, 0.0f,

         0.5f, -0.5f, 0.0f,
         0.0f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    // posição
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    // cor
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(1);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);

    // Rasterização acontece aqui
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glutSwapBuffers();
}

void init()
{
    // Inicializa GLAD
    if (!gladLoadGL())
    {
        std::cout << "Erro ao inicializar GLAD\n";
        exit(-1);
    }

    std::cout << "OpenGL: "
              << glGetString(GL_VERSION)
              << std::endl;

    createShaders();

    createTriangle();

    glClearColor(
        0.1f,
        0.1f,
        0.1f,
        1.0f
    );
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE | GLUT_RGBA
    );

    // OpenGL 3.3 Core
    glutInitContextVersion(3, 3);
    glutInitContextProfile(
        GLUT_CORE_PROFILE
    );

    glutInitWindowSize(800, 600);

    glutCreateWindow("OpenGL + GLAD");

    init();

    glutDisplayFunc(render);

    glutMainLoop();

    return 0;
}