#include "openglexercise.h"


static GLfloat vertexsfirst[] = {
    -0.5f,0.0f,0.0f,
    0.0f,0.0f,0.0f,
    -0.25f,0.25f,0.0f };

static GLfloat vertexssecond[] =  {0.0f,0.0f,0.0f,
                            0.5f,0.0f,0.0f,
                            0.25f,0.25f,0.0f};
static GLfloat vertexs1[] = {
    -0.5f,0.0f,0.0f,
    0.0f,0.0f,0.0f,
    -0.25f,0.25f,0.0f,
    0.0f,0.0f,0.0f,
    0.5f,0.0f,0.0f,
    0.25f,0.25f,0.0f
};

OpenGLExercise::OpenGLExercise(QWidget *parent):
    QOpenGLWidget(parent)
{

}

void OpenGLExercise::initializeGL()
{
     initializeOpenGLFunctions();

     init_1_1();

}

void OpenGLExercise::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    exercise_1_1();
}

void OpenGLExercise::resizeGL(int w, int h)
{

}

void OpenGLExercise::initShaderProGram()
{
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "	gl_PointSize = 20.0f;\n"
        "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    GLuint vertexxShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexxShader, 1, &vertexShaderSource, 0);
    glCompileShader(vertexxShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentShaderSource, 0);
    glCompileShader(fragShader);

    shaderProgram =  glCreateProgram();
    glAttachShader(shaderProgram, vertexxShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
}

void OpenGLExercise::init_1_1()
{


    glGenVertexArrays(1, &VAO1_1);
    glGenBuffers(1, &VBO1_1);

    glBindVertexArray(VAO1_1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1_1);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs1), vertexs1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    initShaderProGram();
}

void OpenGLExercise::exercise_1_1()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO1_1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void OpenGLExercise::init_1_2()
{


    glGenVertexArrays(2, VAO1_2);
    glGenBuffers(2, VBO1_2);

    glBindVertexArray(VAO1_2[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1_2[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexsfirst), vertexsfirst, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

 //   glBindVertexArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(VAO1_2[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1_2[1]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexssecond), vertexssecond, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    initShaderProGram();

}

void OpenGLExercise::exercise_1_2()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO1_2[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(VAO1_2[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
